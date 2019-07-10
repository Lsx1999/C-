#include<iostream>
#include"list.h"

using namespace std;

//*********************************************************************seqList***************************************************************************
template<class elemType>
seqList<elemType>:: seqList(int init)
{
    elem = new elemType[init];
    maxSize = init;
    currentLength = 0;
}

template<class elemType>
void seqList<elemType>:: clear()
{
    currentLength = 0;
}

template<class elemType>
int seqList<elemType>:: length()const
{
    return currentLength;
}

template<class elemType>
elemType seqList<elemType>:: visit(int i)const
{
    if(i < 0 || i > currentLength - 1)
        throw outOfBound();
    return elem[i];
}

template<class elemType>
int seqList<elemType>:: search(const elemType& x)const
{
    int i;
    for(i = 0;i<currentLength;++i)
    {
        if(elem[i] == x)
            return i;
    }
    return -1;
}

template<class elemType>
void seqList<elemType>:: traverse()const
{
    for(int i = 0;i < currentLength;++i)
    {
        cout<<elem[i]<<' ';
    }
    cout<<endl;
}

template<class elemType>
void seqList<elemType>:: remove(int i)
{
    if(i < 0 || i > currentLength - 1)
        throw outOfBound();
    for(int j = i;j < currentLength - 1;++j)
    {
        elem[j] = elem[j + 1];
    }
    currentLength--;
}

template<class elemType>
void seqList<elemType>:: insert(int i,const elemType& x)
{
    if(i < 0 || i > currentLength)
        throw outOfBound();
    if(currentLength == maxSize)
        doubleSpace();
    for(int j = currentLength - 1;j >= i;--j)
    {
        elem[j+1] = elem[j];
    }
    elem[i] = x;
    currentLength++;
}

template<class elemType>
void seqList<elemType>:: doubleSpace()
{
    elemType* tmp = elem;
    elem = new elemType[2 * maxSize];
    for(int i =0;i < currentLength;++i)
    {
        elem[i] = tmp[i];
    }
    delete[] tmp;
    maxSize *= 2;
}
//********************************************************************linkList*************************************************************************
template<class elemType>
linkList<elemType>:: linkList()
{
    head = new node();
}

template<class elemType>
void linkList<elemType>:: clear()
{
    node* p = head->next,*q;
    head->next = NULL;
    while(p)
    {
        q = p;
        p = p->next;
        delete q;
    }
}

template<class elemType>
void linkList<elemType>:: insert(int i,const elemType& x)
{
    if(i < 0)
        throw outOfBound();
    node* p = head;
    for(int j = 0;j < i && p;++j)
    {
        p = p->next;
    }
    if(!p)
        throw outOfBound();
   p->next = new node(x,p->next);
}

template<class elemType>
void linkList<elemType>:: remove(int i)
{
    if(i < 0)
        throw outOfBound();
    node* p = head,*tmp;
    for(int j = 0; j < i && p;++j)
    {
        p = p->next;
    }
    if(!p || !(p->next))
        throw outOfBound();
    tmp = p->next;
    p->next = tmp->next;
    delete tmp;
}

template<class elemType>
int linkList<elemType>:: length()const
{
    int i = 0;
    node* p =head->next;
    while(p)
    {
        i++;
        p = p->next;
    }
    return i;
}

template<class elemType>
int linkList<elemType>:: search(const elemType& x)const
{
    node* p = head->next;
    int i =0;
    while(p && p->data != x)
    {
        i++;
        p = p->next;
    }
    if(! p)
        return -1;
    return i;
}

template<class elemType>
elemType linkList<elemType>:: visit(int i)const
{
    if(i < 0)
        throw outOfBound();
    node* p = head->next;
    for(int j = 0;j < i && p;++j)
    {
        p = p->next;
    }
    if(! p)
        throw outOfBound();
    return p->data;
}

template<class elemType>
void linkList<elemType>:: traverse()const
{
    node* p = head->next;
    while(p)
    {
        cout<<p->data<<' ';
        p = p->next;
    }
}

















