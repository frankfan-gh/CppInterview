#include <iostream>

template<typename T>
class Vector
{
public:
    Vector() = default;
    void swap(Vector& rhs)
    {
        std::swap(rhs.data_, data_);
        std::swap(rhs.size_, size_);
        std::swap(rhs.capacity_, capacity_);
    }
    size_t size()
    {
        return size_ - data_;
    }
    size_t capacity()
    {
        return capacity_ - data_;
    }
    Vector(const Vector& rhs)
    {
        data_ = new T[rhs.capacity()];
        memcpy(data_, rhs.data_, sizeof(T) * rhs.capacity_());
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
    }
    Vector(Vector&& rhs)
    {
        swap(rhs);
    }
    ~Vector()
    {
        if(data_)
            delete[] data_;
    }
    Vector& operator=(Vector rhs)
    {
        swap(rhs);
        return *this;
    }
    Vector& operator=(Vector&& rhs)
    {
        swap(rhs);
        return *this;
    }
    Vector(size_t num, const T& val)
    {
        data_ = new T[num];
        for(size_t i = 0; i < num; ++i)
            data_[i] = val;
        size_ = data_ + num;
        capacity_ = size_;
    }
    void reserve(size_t cap)
    {
        if(capacity() < cap)
        {
            T* tmp = new T[cap];
            size_t s = size();
            if(data_)
            {
                memcpy(tmp, data_, capacity());
                delete[] data_;
            }
            data_ = tmp;
            size_ = data_ + s;
            capacity_ = data_ + cap;
        }
    }
    void resize(size_t s)
    {
        if(capacity() < s)
            reserve(s);
        if(size() < s)
        {
            while(size_ != data_ + s)
            {
                *size_ = T();
                ++size_;
            }
        }
        else
            size_ = data_ + s;
    }
    void push_back(const T& val)
    {
        if(size_ == capacity_)
        {
            reserve(capacity_ == nullptr ? 4 : 2 * capacity());
        }
        *size_ = val;
        ++size_;
    }
    void pop_back()
    {
        assert(size() > 0);
        --size_;
    }
    T& operator[](size_t index)
    {
        assert(index >= 0 && index <= size());
        return data_[index];
    }
private:
    T* data_ = nullptr;
    T* size_ = nullptr;
    T* capacity_ = nullptr;
};