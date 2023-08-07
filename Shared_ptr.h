#include <atomic>

template<typename T>
class Shared_ptr
{
public:
    Shared_ptr() = default;
    Shared_ptr(T* ptr): ptr_(ptr), ref_count_(new std::atomic<int>(1)){}
    Shared_ptr(Shared_ptr<T>& rhs): ptr_(rhs.ptr_), ref_count_(rhs.ref_count_)
    {
        ++(*ref_count_);
    }
    ~Shared_ptr()
    {
        if(ptr_)
        {
            --ref_count_;
            if(*ref_count_ <= 0)
            {
                delete ptr_;
                delete ref_count_;
            }
        }
    }
    void swap(Shared_ptr& rhs)
    {
        std::swap(ptr_, rhs.ptr_);
        std::swap(ref_count_, rhs.ref_count_);
    }
    void reset(T* ptr)
    {
        Shared_ptr tmp(ptr);
        swap(tmp);
    }
    T& operator*()
    {
        assert(ptr_);
        return *ptr_;
    }
    T* operator->()
    {
        assert(ptr_);
        return ptr_;
    }
private:
    T* ptr_ = nullptr;
    std::atomic<int>* ref_count_ = nullptr;
};