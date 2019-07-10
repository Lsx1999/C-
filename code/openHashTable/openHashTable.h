#ifndef OPENHASHTABLE_H_INCLUDED
#define OPENHASHTABLE_H_INCLUDED
#include<iostream>
using namespace std;

template<class KEY,class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};


template<class KEY,class OTHER>
class openHashTable
{
private:
    struct node
    {
        SET<KEY,OTHER> data;
        node* next;

        node(const SET<KEY,OTHER>& x,node* n = NULL):data(x),next(n){}
        node():next(NULL){}
    };
    node** array;
    int size;
    int (*key)(const KEY& x);
    static int defaultKey(const int& x){return x;}
public:
    openHashTable(int length = 20,int (*f)(const KEY& x) = defaultKey);
    ~openHashTable();
    SET<KEY,OTHER> *find(const KEY& x)const
    {
        int pos;
        pos = key(x)%size;

        if(!array[pos])
            return NULL;
        node* p = array[pos];
        while(p && p->data.key != x)
            p = p->next;
        if(!p)
            return NULL;
        else
            return (SET<KEY,OTHER>*)p;
    }
    void insert(const SET<KEY,OTHER>& x);
    void remove(const KEY& x);
};


#endif // OPENHASHTABLE_H_INCLUDED
