#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

const int DATA_NUM = 500;

template<typename T>
class Resource
{
public:
    const int MAX_DATA_NUM = 100;
    std::deque<T> data;
    std::mutex mut;
    std::condition_variable not_empty;
    std::condition_variable not_full;
};

template<typename T>
void Producer(Resource<T>& resource)
{
    static int d = 0;
    while(1)
    {
        std::unique_lock<std::mutex> lk(resource.mut);
        if(d >= DATA_NUM)
            break;
        resource.not_full.wait(lk, [&resource](){return resource.data.size() < resource.MAX_DATA_NUM;});
        resource.data.push_back(d++);
        std::cout << "Produced " << d << std::endl;
        resource.not_empty.notify_one();

    }
}

template<typename T>
void Consumer(Resource<T>& resource)
{
    static int count = 0;
    while (1)
    {
        std::unique_lock<std::mutex> lk(resource.mut);
        if(count >= DATA_NUM)
            break;
        resource.not_empty.wait(lk, [&resource](){return !resource.data.empty();});
        T d = resource.data.front();
        resource.data.pop_front();
        std::cout << "Consumed " << d << std::endl;
        ++count;
        resource.not_full.notify_one();
    }
}

class Tester
{
public:
    void Test()
    {
        Resource<int> resource;
        std::thread pro1(Producer<int>, std::ref(resource));
        std::thread pro2(Producer<int>, std::ref(resource));
        std::thread con1(Consumer<int>, std::ref(resource));
        std::thread con2(Consumer<int>, std::ref(resource));
        pro1.join();
        pro2.join();
        con1.join();
        con2.join();
    }
};

