#include <iostream>
#include <mutex>

class HSingleton
{
public:
    static HSingleton* getInstance()
    {
        return &instance_;
    }
private:
    HSingleton(){}
    static HSingleton instance_;
};
HSingleton HSingleton::instance_;

class FSingleton
{
public:
    static FSingleton* getInstance()
    {
        if(instance_ == nullptr)
        {
            mut_.lock();
            if(instance_ == nullptr)
            {
                instance_ = new FSingleton();
            }
            mut_.unlock();
        }
        return instance_;
    }
    
private:
    class CGarbo
    {
    public:
        CGarbo(){}
        ~CGarbo()
        {
            if(FSingleton::instance_)
                delete FSingleton::instance_;
        }
    };

    FSingleton(){}
    static FSingleton* instance_;
    static CGarbo cgarbo_;
    static std::mutex mut_;
};
FSingleton* FSingleton::instance_ = nullptr;
FSingleton::CGarbo FSingleton::cgarbo_;
std::mutex FSingleton::mut_;