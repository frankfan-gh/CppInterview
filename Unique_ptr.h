

template<typename T>
class Unique_ptr
{
public:
    Unique_ptr() = default;
    Unique_ptr(const Unique_ptr& rhs) = delete;
    Unique_ptr& operator=(const Unique_ptr& rhs) = delete;
    Unique_ptr(Unique_ptr&& rhs)
    {
        swap(rhs);
    }
    Unique_ptr& operator=(Unique_ptr&& rhs)
    {
        swap(rhs);
    }
    ~Unique_ptr()
    {
        if(ptr_)
            delete ptr_;
    }
    Unique_ptr(T* ptr)
    {
        ptr_ = ptr;
    }
    void swap(Unique_ptr& rhs)
    {
        std::swap(ptr_, rhs.ptr_);
    }
    void reset(T* ptr)
    {
        Unique_ptr<T> tmp(ptr);
        swap(tmp);
    }
    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
private:
    T* ptr_ = nullptr;
};