#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<iostream>
using namespace std;

class outOfBound1{};
class illegal1{};

template<class elemType>
class stack
{
public:
    virtual void push(const elemType& x) = 0;
    virtual void pop() = 0;
    virtual elemType top()const = 0;
    virtual bool isEmpty()const = 0;
    virtual ~stack(){}
};

template<class elemType>
class seqStack: public stack<elemType>
{
private:
    elemType* elem;
    int Top,maxSize;
    void doubleSpace();
public:
    seqStack(int init = 10);
    ~seqStack(){delete[] elem;}
    void push(const elemType& x);
    void pop();
    bool isEmpty()const{return Top == -1;}
    elemType top()const;
};

template<class T>
class linkStack: public stack<T>
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
    node* Top;
public:
    linkStack();
    ~linkStack();
    void push(const T& x);
    void pop();
    bool isEmpty()const;
    T top()const;
};

#endif // STACK_H_INCLUDED
