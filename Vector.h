#include <iostream>
#include <cstring>
#include <assert.h>

template<typename T>
class Vector
{
public:
    Vector() = default;

    Vector(const size_t size, const T& val)
    {
        data_ = new T[size];
        capacity_ = size_ = size;
        for(size_t i = 0; i < size_; ++i)
            data_[i] = T(val);
    }

    Vector(const Vector& rhs)
    {
        if(this == &rhs)
            return;
        Vector tmp;
        swap(tmp);
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        data_ = new T[capacity_];
        std::memcpy(data_, rhs.data_, capacity_ * sizeof(T));
    }

    Vector(Vector&& rhs)
    {
        swap(rhs);
    }

    ~Vector()
    {
        delete[](data_);
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

    void reserve(size_t n)
    {
        if(capacity_ < n)
        {
            T* new_data = new T[n];
            memcpy(new_data, data_, capacity_);
            delete[] data_;
            data_ = new_data;
            capacity_ = n;
        }
    }

    void resize(size_t n)
    {
        if(capacity_ < n)
            reserve(n);
        if(size_ < n)
        {
            memset(data_ + size_, n - size_, 0);
        }
        size_ = n;
    }

    void push_back(const T& val)
    {
        if(size_ == capacity_)
        {
            size_t new_capacity = capacity_ == 0 ? 4 : 2 * capacity_;
            reserve(new_capacity);
        }
        data_[size_++] = val;
    }

    void pop_back()
    {
        assert(size_ > 0);
        --size_;
    }

    T& operator[](size_t size)
    {
        return data_[size];
    }
private:
    void swap(Vector& rhs)
    {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
    }

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};