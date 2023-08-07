#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>

class Singleton1
{
public:
    Singleton1* getInstance()
    {
        return &sm_instance;
    }
    Singleton1() = default;
    Singleton1(const Singleton1& rhs) = delete;
    Singleton1& operator=(const Singleton1& rhs) = delete;
private:
    static Singleton1 sm_instance;
};
Singleton1 Singleton1::sm_instance;

class Singleton2
{
public:
    Singleton2* getInstance()
    {
        if(sm_instance == nullptr)
        {
            sm_mut.lock();
            if(sm_instance == nullptr)
            {
                sm_instance = new Singleton2();
            }
            sm_mut.unlock();
        }
        return sm_instance;
    }

    class CGarbo
    {
        public:
        ~CGarbo()
        {
            if(sm_instance)
                delete sm_instance;
        }
    };
private:
    static Singleton2* sm_instance;
    static std::mutex sm_mut;
    static CGarbo sm_garbo;
};
Singleton2* Singleton2::sm_instance = nullptr;
std::mutex Singleton2::sm_mut;
Singleton2::CGarbo Singleton2::sm_garbo;

#endif //#ifndef SINGLETON_H

