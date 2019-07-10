#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<iostream>
using namespace std;

class outOfBound{};
class illegal{};

template<class elemType>
class queue
{
public:
    virtual void enqueue(const elemType& x) = 0;
    virtual void dequeue() = 0;
    virtual bool isEmpty()const = 0;
    virtual elemType getHead()const = 0;
    virtual ~queue(){}
};

template<class elemType>
class seqQueue: public queue<elemType>
{
private:
    elemType* elem;
    int maxSize;
    int front,rear;
    void doubleSpace();
public:
    seqQueue(int init = 10);
    ~seqQueue(){delete[] elem;}
    bool isEmpty()const{return (front == rear);}
    void enqueue(const elemType& x);
    void dequeue();
    elemType getHead()const;
};

template<class T>
class linkQueue: public queue<T>
{
private:
    struct node
    {
        T data;
        node* next;

        node(const T& x,node* n = NULL):data(x),next(n){}
        node():next(NULL){}
        ~node(){}
    };
    node* front,*rear;
public:
    linkQueue();
    ~linkQueue();
    void enqueue(const T& x);
    void dequeue();
    bool isEmpty()const;
    T getHead()const;
} ;

#endif // QUEUE_H_INCLUDED
