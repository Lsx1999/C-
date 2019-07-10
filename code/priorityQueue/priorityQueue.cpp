#include<iostream>
#include"priorityQueue.h"
using namespace std;

template<class Type>
priorityQueue<Type>:: priorityQueue(int capacity)
{
    array = new Type[capacity];
    currentSize = 0;
    maxSize = capacity;
}

template<class Type>
priorityQueue<Type>:: priorityQueue(const Type data[],int size)
{
    maxSize = size + 10;
    currentSize = size;
    array = new Type[maxSize];
    for(int i = 0;i < size;++i)
    {
        array[i+1] = data[i];
    }
    buildHeap();
}

template<class Type>
priorityQueue<Type>:: ~priorityQueue()
{
    delete[] array;
}

template<class Type>
void priorityQueue<Type>:: enqueue(const Type& x)
{
    if(currentSize == maxSize - 1)
        doubleSpace();
    int hole = ++currentSize;
    for(;hole > 1 && x < array[hole/2];hole/=2)
    {
        array[hole] = array[hole/2];
    }
    array[hole] = x;
}

template<class Type>
void priorityQueue<Type>:: dequeue()
{
    array[1] = array[currentSize--];
    percolateDown(1);
}

template<class Type>
Type priorityQueue<Type>:: getHead()const
{
    return array[1];
}

template<class Type>
bool priorityQueue<Type>:: isEmpty()const
{
    return currentSize == 0;
}

template<class Type>
void priorityQueue<Type>:: percolateDown(int hole)
{
    int child;
    Type tmp = array[hole];
    for(;hole * 2 <= currentSize;hole = child)
    {
        child  = 2 * hole;
        if(child != currentSize && array[child+1] < array[child])
            child++;
        if(array[child] < tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>:: buildHeap()
{
    for(int i = currentSize/2;i > 0;--i)
        percolateDown(i);
}

template<class Type>
void priorityQueue<Type>:: doubleSpace()
{
    Type* tmp = array;
    array = new Type[2*maxSize];
    for(int i = 0;i <= currentSize;++i)
    {
        array[i] = tmp[i];
    }
    maxSize *= 2;
    delete[] tmp;
}
