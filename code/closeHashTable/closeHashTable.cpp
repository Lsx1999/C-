#include"closeHashTable.h"
#include<cmath>
#include<iostream>
using namespace std;
template<class KEY,class OTHER>
closeHashTable<KEY,OTHER>:: closeHashTable(int length,int numOfDel,int (*f)(const KEY& x))
{
    cnt = 0;
    del = 0;
    limit = numOfDel;
    size = prime(length);
    array = new node[size];
    key = f;
}

template<class KEY,class OTHER>
bool closeHashTable<KEY,OTHER>:: isPrime(const int& x)
{
    double tmp = x;
    int k = sqrt(tmp);
    if(x == 1)
        return false;
    for(int i = 2;i <= k;++i)
    {
        if(x%i == 0)
            return false;
    }
    return true;
}

template<class KEY,class OTHER>
int closeHashTable<KEY,OTHER>:: prime(const int& x)
{
    int tmp = x;
    while(!isPrime(tmp))
    {
        tmp++;
    }
    return tmp;
}

template<class KEY,class OTHER>
void closeHashTable<KEY,OTHER>:: doubleSpace()
{
    node* tmp = array;
    int s = size;
    int newSize = 2*size;
    size = prime(newSize);
    array = new node[size];
    for(int i = 0;i < s;++i)
    {
        insert(tmp[i].data);
    }
    delete tmp;
    limit *= 2;
}

template<class KEY,class OTHER>
void closeHashTable<KEY,OTHER>:: insert(const SET<KEY,OTHER>& x)
{
    if(isFull())
        doubleSpace();
    int initpos,pos;
    initpos = pos = key(x.key)%size;
    do
    {
        if(array[pos].state != 1)
        {
            array[pos].data = x;
            if(array[pos].state == 2)
                del--;
            array[pos].state = 1;
            cnt++;
            //cout<<x.key<<"²åÔÚ"<<pos<<endl;
            return;
        }
        pos = (pos + 1)%size;
    }while(pos != initpos);
}

template<class KEY,class OTHER>
void closeHashTable<KEY,OTHER>:: remove(const KEY& x)
{
    int initpos,pos;
    initpos = pos = key(x)%size;
    do
    {
        if(array[pos].state == 0)
        return;
        if(array[pos].state == 1 && array[pos].data.key == x)
        {
            array[pos].state = 2;
            cnt--;
            del++;
            reHash();
            return;
        }
        pos = (pos + 1)%size;
    }while(pos != initpos);

}

template<class KEY,class OTHER>
void closeHashTable<KEY,OTHER>:: reHash()
{
    if(del == limit)
    {
        node* tmp = array;
        array = new node[size];
        cnt = 0;
        del = 0;
        for(int i = 0;i < size;++i)
        {
            if(tmp[i].state == 1)
            {
                insert(tmp[i].data);
            }
        }
    }
}
