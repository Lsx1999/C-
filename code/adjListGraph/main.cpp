#include <iostream>
#include"adjListGraph.h"
#include"adjListGraph.cpp"
using namespace std;

int main()
{
    int a[7] = {1,2,3,4,5,6,7};
    adjListGraph<int,int> g(7,a);
    g.insert(1,2,0);
    g.insert(1,3,0);
    g.insert(2,5,0);
    g.insert(2,6,0);
    g.insert(2,4,0);
    g.insert(3,5,0);
    g.insert(3,7,0);
    g.insert(5,7,0);
    g.insert(5,6,0);
    g.insert(6,4,0);
    g.dfs();
    return 0;
}
