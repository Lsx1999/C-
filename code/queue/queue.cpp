#include<iostream>
#include"queue.h"

using namespace std;

//**************************************************************seqQueue*******************************************************************************
template<class elemType>
seqQueue<elemType> :: seqQueue(int init)
{
    elem = new elemType[init];
    maxSize = init;
    front = rear = 0;
}

template<class elemType>
void seqQueue<elemType> :: enqueue(const elemType& x)
{
    if((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template<class elemType>
void seqQueue<elemType> :: dequeue()
{
    if(front == rear)
        throw outOfBound();
    front = (front + 1) % maxSize;
}

template<class elemType>
elemType seqQueue<elemType> :: getHead()const
{
    if(front == rear)
        throw outOfBound();
    return elem[(front + 1) % maxSize];
}

template<class elemType>
void seqQueue<elemType> :: doubleSpace()
{
    elemType* tmp = elem;
    elem = new elemType[2 * maxSize];
    for(int i = 1;i < maxSize;++i)
        elem[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}

//******************************************************************linkQueue**************************************************************************

template<class T>
linkQueue<T> :: linkQueue()
{
    front = rear = NULL;
}

template<class T>
linkQueue<T> :: ~linkQueue()
{
    node* tmp;
    while(front)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template<class T>
bool linkQueue<T> :: isEmpty()const
{
    return rear == NULL;
}

template<class T>
void linkQueue<T> :: enqueue(const T& x)
{
    if(rear == NULL)
        front = rear = new node(x);
    else
    {
        rear->next = new node(x);
        rear = rear->next;
    }
}

template<class T>
void linkQueue<T> :: dequeue()
{
    if(rear == NULL)
        throw outOfBound();
    node* tmp = front;
    front = front->next;
    if(!front) rear = NULL;
    delete tmp;
}

template<class T>
T linkQueue<T> :: getHead()const
{
    if(front == NULL)
        throw outOfBound();
    return front->data;
}

