#pragma once
#include <iostream>
#include <stack>

template<typename T>
class Deque
{
public:
    void push_front(const T& val)
    {
        front_.push(val);
    }
    void push_back(const T& val)
    {
        back_.push(val);
    }
    void pop_front()
    {
        if(front_.empty())
        {
            while(!back_.empty())
            {
                T val = back_.top();
                back_.pop();
                front_.push(val);
            }
        }
        front_.pop();
    }
    void pop_back()
    {
        if(back_.empty())
        {
            while(!front_.empty())
            {
                T val = front_.top();
                front_.pop();
                back_.push(val);
            }
        }
        back_.pop();
    }
    T& front()
    {
        if(front_.empty())
        {
            while(!back_.empty())
            {
                T val = back_.top();
                back_.pop();
                front_.push(val);
            }
        }
        return front_.top();
    }
    T& back()
    {
        if(back_.empty())
        {
            while(!front_.empty())
            {
                T val = front_.top();
                front_.pop();
                back_.push(val);
            }
        }
        return back_.top();
    }
    bool empty()
    {
        return front_.empty() && back_.empty();
    }
    size_t size()
    {
        return front_.size() + back_.size();
    }
private:
    std::stack<T> front_;
    std::stack<T> back_;
};