#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
#include<iostream>
using namespace std;

template<class Type>
class priorityQueue
{
public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[],int size);
    ~priorityQueue();
    void enqueue(const Type& x);
    void dequeue();
    Type getHead()const;
    bool isEmpty()const;
    void display()const
    {
        for(int i = 1;i <=currentSize;++i)
        {
            cout<<array[i]<<" ";
        }
    }
private:
    Type* array;
    int currentSize;
    int maxSize;
    void buildHeap();
    void doubleSpace();
    void percolateDown(int hole);
};
#endif // PRIORITYQUEUE_H_INCLUDED
