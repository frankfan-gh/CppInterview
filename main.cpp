#include "Vector.h"
#include "String.h"
#include "Shared_ptr.h"
#include "Singleton.h"
#include "Deque.h"
#include "Producer_Consumer.h"
#include "UnionFind.h"
#include <iostream>

int main()
{
    UnionFind uf(10);
    uf.f_union2(1, 2);
        uf.f_union2(2, 5);
        uf.f_union2(5, 6);
        uf.f_union2(6, 7);
        uf.f_union2(3, 8);
        uf.f_union2(8, 9);
        std:: cout << uf.connected(1, 5); // true
        std:: cout << uf.connected(5, 7); // true
        std:: cout << uf.connected(4, 9); // false
        // 1-2-5-6-7 3-8-9-4
        uf.f_union2(9, 4);
        std:: cout << uf.connected(4, 9); // true

    return 0;
}