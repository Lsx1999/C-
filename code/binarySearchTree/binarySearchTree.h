#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
#include<iostream>
using namespace std;

template<class Type>
class binarySearchTree
{
private:
    struct node
    {
        Type data;
        node *left,*right;

        node(Type x,node* l = NULL,node* r = NULL):data(x),left(l),right(r){}
        node():left(NULL),right(NULL){}
        ~node(){}
    };
node* root;
public:
    binarySearchTree();
    ~binarySearchTree();
    bool find(const Type& x)const;
    void insert(const Type& x);
    void remove(const Type& x);
private:
    void clear(node* &t);
};


#endif // BINARYSEARCHTREE_H_INCLUDED
