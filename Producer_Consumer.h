#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
#include <atomic>

#define TOXIC -1
const int MAX_DATA_NUM = 100;
const int TASK_NUM = 200;

template<typename T>
struct Resource
{
    std::mutex mut;
    std::condition_variable not_full;
    std::condition_variable not_empty;
    std::deque<T> data;
};

template<typename T>
void Produce(Resource<T>& resource)
{
    for(int i = 0; i < TASK_NUM; ++i)
    {
        std::unique_lock<std::mutex> ulk(resource.mut);
        resource.not_full.wait(ulk, [&resource](){return resource.data.size() < MAX_DATA_NUM;});
        resource.data.push_back(i); //test
        resource.not_empty.notify_all();
    }
    resource.data.push_back(TOXIC);
}

template<typename T>
void Consume(Resource<T>& resource)
{
    while(1)
    {
        std::unique_lock<std::mutex> ulk(resource.mut);
        resource.not_empty.wait(ulk, [&resource]{return resource.data.size() > 0;});
        T d = resource.data.front();
        resource.data.pop_front();
        if(d != TOXIC)
            std::cout << "Consumed " << d << std::endl;
        else
        {
            std::cout << "Consumed TOXIC" << std::endl;
            break;
        }
        resource.not_full.notify_all();
    }
}

void Test()
{
    Resource<int> r;
    std::thread p(Produce<int>, std::ref(r));
    std::thread c(Consume<int>, std::ref(r));
    p.join();
    c.join();
    return;
}
