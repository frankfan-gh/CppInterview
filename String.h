#include <iostream>
#include <cstring>

class String
{
friend std::ostream& operator<<(std::ostream& os, const String& mystring);
public:
    String()
    {
        data_ = new char('\0');
    }
    String(const char* str)
    {
        delete[] data_;
        size_ = strlen(str);
        data_ = new char[size_ + 1];
        std::memcpy(data_, str, size_ + 1);
        capacity_ = size_;
    }
    ~String()
    {
        delete[] data_;
    }

private:
    char* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

std::ostream& operator<<(std::ostream& os, const String& mystring)
{
    char* ptr = mystring.data_;
    for(size_t i = 0; i < mystring.size_; ++i)
        os << *(ptr++);
    return os;
}