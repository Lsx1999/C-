#ifndef CLOSEHASHTABLE_H_INCLUDED
#define CLOSEHASHTABLE_H_INCLUDED
#include<iostream>

template<class KEY,class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY,class OTHER>
class closeHashTable
{
private:
   struct node
   {
       SET<KEY,OTHER> data;
       int state;// 0--empty  1--active  2--deleted

       node(){state = 0;}
   };
   node* array;
   int size;
   int cnt;
   int limit;
   int del;
   int (*key)(const KEY& x);
   static int defaultKey(const int& x){return x;}
public:
    closeHashTable(int length = 101,int numOfDel = 60,int (*f)(const KEY& x) = defaultKey);
    ~closeHashTable(){delete[] array;}
    node* find(const KEY& x)const
    {
        int initpos,pos;

        initpos = pos = key(x)%size;

        do
        {
            if(array[pos].state == 0)
                return NULL;
            if(array[pos] == 1 && array[pos].data.key == x)
                return &array[pos];
            pos = (pos + 1)%size;

        }while(pos != initpos);
    }
    void insert(const SET<KEY,OTHER>& x);
    void remove(const KEY& x);
    bool isFull()const{return cnt == size;}
private:
    int prime(const int& len);
    void doubleSpace();
    void reHash();
    bool isPrime(const int& x);
};
#endif // CLOSEHASHTABLE_H_INCLUDED
