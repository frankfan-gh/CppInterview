
#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity): capacity_(capacity) {}
    
    int get(int key) {
        if(umap_.count(key) > 0)
        {
            auto iter = umap_[key];
            int val = umap_[key]->second;
            list_.erase(iter);
            list_.push_front(make_pair(key, val));
            umap_[key] = list_.begin();
            return val;
        }
        else
            return -1;
    }
    
    void put(int key, int value) {
        if(umap_.count(key) == 0 && list_.size() == capacity_)
        {
            umap_.erase(list_.back().first);
            list_.pop_back();
        }
        if(umap_.count(key) > 0)
        {
            auto iter = umap_[key];
            list_.erase(iter);
        }
        list_.push_front(make_pair(key, value));
        umap_[key] = list_.begin();
    }
private:
    list<pair<int, int>> list_;
    unordered_map<int, list<pair<int, int>>::iterator> umap_;
    int capacity_;
};

