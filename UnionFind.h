#pragma once
#include <iostream>
#include <vector>

class UnionFind
{
public:
    UnionFind(size_t size): root(std::vector<int>(size)), rank(std::vector<int>(size, 1))
    {
        for(int i = 0; i < root.size(); ++i)
        {
            root[i] = i;
        }
    }

    int find(int x)
    {
        if(root[x] == x)
            return x;
        return root[x] = find(root[x]);
    }
    //基于秩优化
    void f_union(int x, int y)
    {
        if(root[x] != root[y])
        {
            if(rank[root[x]] > rank[root[y]])
            {
                root[root[y]] = root[x];
            }
            else if(rank[root[x]] < rank[root[y]])
            {
                root[root[x]] = root[y];
            }
            else{
                root[root[y]] = root[x];
                ++rank[root[x]];
            }
        }
    }
    //quick union
    void f_union2(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX != rootY)
            root[rootX] = rootY;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
private:
    std::vector<int> root;
    std::vector<int> rank;
};