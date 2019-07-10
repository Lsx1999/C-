#include <iostream>
#include"priorityQueue.h"
#include"priorityQueue.cpp"
using namespace std;

int main()
{
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    priorityQueue<int> q(a,10);
    q.display();
    return 0;
}
