#include<iostream>
#include"leftHeap.h"
using namespace std;

template<class Type>
leftHeap<Type>:: leftHeap()
{
    root = NULL;
}

template<class Type>
leftHeap<Type>:: ~leftHeap()
{
    clear(root);
}

template<class Type>
void leftHeap<Type>::clear(leftHeap<Type>:: node* r)
{
    if(r == NULL)
        return;
    clear(r->left);
    clear(r->right);
    delete r;
    r = NULL;
}

template<class Type>
void leftHeap<Type>:: enqueue(const Type& x)
{
    node* tmp;
    tmp = new node(x);
    root = merge(root,tmp);
}

template<class Type>
void leftHeap<Type>:: dequeue()
{
    root = merge(root->left,root->right);
}

template<class Type>
Type leftHeap<Type>:: getHead()const
{
    return root->data;
}

template<class Type>
bool leftHeap<Type>:: isEmpty()const
{
    return (root != NULL);
}
