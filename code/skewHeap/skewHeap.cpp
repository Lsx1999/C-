#include<iostream>
#include"skewHeap.h"
using namespace std;

template<class Type>
skewHeap<Type>:: skewHeap()
{
    root = NULL;
}

template<class Type>
skewHeap<Type>:: ~skewHeap()
{
    clear(root);
}

template<class Type>
void skewHeap<Type>::clear(skewHeap<Type>:: node* r)
{
    if(r == NULL)
        return;
    clear(r->left);
    clear(r->right);
    delete r;
    r = NULL;
}

template<class Type>
void skewHeap<Type>:: enqueue(const Type& x)
{
    node* tmp;
    tmp = new node(x);
    root = merge(root,tmp);
}

template<class Type>
void skewHeap<Type>:: dequeue()
{
    root = merge(root->left,root->right);
}

template<class Type>
Type skewHeap<Type>:: getHead()const
{
    return root->data;
}

template<class Type>
bool skewHeap<Type>:: isEmpty()const
{
    return (root != NULL);
}
