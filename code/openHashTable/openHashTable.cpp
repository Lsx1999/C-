#include"openHashTable.h"
#include<iostream>
using namespace std;

template<class KEY,class OTHER>
openHashTable<KEY,OTHER>:: openHashTable(int length,int (*f)(const KEY& x))
{
    size = length;
    array = new node*[size];
    key = f;
    for(int i = 0;i < size;++i)
    {
        array[i] = NULL;
    }
}

template<class KEY,class OTHER>
openHashTable<KEY,OTHER>:: ~openHashTable()
{
    node *p,*q;
    for(int i = 0;i < size;++i)
    {
        p = array[i];
        while(p)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
    delete[] array;
}

template<class KEY,class OTHER>
void openHashTable<KEY,OTHER>:: insert(const SET<KEY,OTHER>& x)
{
    int pos;
    pos = key(x.key)%size;
    array[pos] = new node(x,array[pos]);
}

template<class KEY,class OTHER>
void openHashTable<KEY,OTHER>:: remove(const KEY& x)
{
    int pos;
    node *p,*q;
    pos = key(x)%size;
    p = array[pos];
    if(!p)
        return;
    if(array[pos]->data.key == x)
    {
        array[pos] = p->next;
        delete p;return;
    }
    while(p && p->data.key != x)
    {
        q = p;
        p = q->next;
    }
    if(!p)
        return;
    else
        q->next = p->next;
    delete p;
}

