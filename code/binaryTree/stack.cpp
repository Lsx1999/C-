#include<iostream>
#include"stack.h"

using namespace std;

//*******************************************************************seqStack**************************************************************************
template<class elemType>
seqStack<elemType> :: seqStack(int init)
{
    elem = new elemType[init];
    maxSize = init;
    Top = -1;
}

template<class elemType>
void seqStack<elemType>:: push(const elemType& x)
{
    if(Top == maxSize - 1)
        doubleSpace();
    else
        elem[++Top] = x;
}

template<class elemType>
void seqStack<elemType>:: pop()
{
    if(Top == -1)
        throw outOfBound1();
    Top--;
}

template<class elemType>
elemType seqStack<elemType>:: top()const
{
    if(Top == -1)
        throw outOfBound1();
    return elem[Top];
}

template<class elemType>
void seqStack<elemType>:: doubleSpace()
{
    elemType* tmp = elem;
    elem = new elemType[2 * maxSize];
    for(int i = 0;i <= Top;++i)
    {
        elem[i] = tmp[i];
    }
    maxSize *= 2;
    delete[] tmp;
}

//****************************************************************linkStack**************************************************************************

template<class T>
linkStack<T>:: linkStack()
{
    Top = NULL;
}

template<class T>
linkStack<T>:: ~linkStack()
{
    node* tmp;
    while(Top)
    {
        tmp = Top;
        Top = Top->next;
        delete tmp;
    }
}

template<class T>
void linkStack<T>:: push(const T& x)
{
    Top = new node(x,Top);
}

template<class T>
void linkStack<T>:: pop()
{
    if(isEmpty())
        throw outOfBound1();
    node* tmp = Top;
    Top = Top->next;
    delete tmp;
}

template<class T>
T linkStack<T>:: top()const
{
    if(isEmpty())
        throw outOfBound1();
    return Top->data;
}

template<class T>
bool linkStack<T>:: isEmpty()const
{
    return Top == NULL;
}
