#pragma once
#include <assert.h>
#include <iostream>
#include <unordered_map>
#include <memory>
using namespace std;

template<typename T>
class List;

template<typename T>
class Node
{
public:
    Node(): val(T()){}
    Node(const T& v): val(v){}
    Node(const T& v, shared_ptr<Node<T>>& p, shared_ptr<Node<T>>& n): val(v), pre(p), next(n){}
    T val;
private:
    shared_ptr<Node<T>> next = nullptr;
    shared_ptr<Node<T>> pre = nullptr;
friend class List<T>;
};

template<typename T>
class List
{
public:
    List(): head(new Node<T>), tail(new Node<T>)
    {
        head->next = tail;
        tail->pre = head;
    }
    void pop_back()
    {
        assert(head->next != tail);
        auto p = tail->pre;
        p->pre->next = tail;
        tail->pre = p->pre;
        p->next = p->pre = nullptr;
    }
    void push_front(const T& val)
    {
        auto node = make_shared<Node<T>>(val);
        auto p = head->next;
        p->pre = node;
        head->next = node;
        node->pre = head;
        node->next = p;
    }
    shared_ptr<Node<T>> erase(shared_ptr<Node<T>> node)
    {
        auto tmp = node->next;
        node->pre->next = node->next;
        node->next->pre = node->pre;
        node->pre = node->next = nullptr;
        return tmp;
    }
    shared_ptr<Node<T>> front()
    {
        return head->next;
    }
    shared_ptr<Node<T>> back()
    {
        return tail->pre;
    }
private:
    shared_ptr<Node<T>> head;//头前节点
    shared_ptr<Node<T>> tail;//尾后节点
};

class LRUCache {
public:
    LRUCache(int capacity): capacity_(capacity){}
    
    int get(int key) {
        if(umap_.count(key) > 0)
        {
            auto node = umap_[key];
            list_.erase(node);
            list_.push_front(node->val);
            umap_[key] = list_.front();
            return list_.front()->val.second;
        }
        else
            return -1;
    }
    
    void put(int key, int value) {
        if(umap_.count(key) == 0 && umap_.size() == capacity_)
        {
            umap_.erase(list_.back()->val.first);
            list_.pop_back();
        }
        if(umap_.count(key) > 0)
        {
            auto node = umap_[key];
            list_.erase(node);
        }
        list_.push_front(make_pair(key, value));
        umap_[key] = list_.front();
    }
private:
    List<pair<int, int>> list_;
    unordered_map<int, shared_ptr<Node<pair<int, int>>>> umap_;
    int capacity_;
};