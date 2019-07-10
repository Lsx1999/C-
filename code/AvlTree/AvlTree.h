#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include<iostream>
using namespace std;

template<class Type>
class AvlTree
{
private:
    struct node
    {
        Type data;
        node *left,*right;
        int height;

        node(const Type& x,node* l = NULL,node* r = NULL,int& h = 0):data(x),left(l),right(r),height(h){}
        node():left(NULL),right(NULL),height(0){}
        ~node(){}
    };
    node* root;
public:
    AvlTree();
    ~AvlTree();
    bool find(const Type& x)const;
    void insert(const Type& x);
    void remove(const Type& x);
private:
    void clear(node* t);
    void LL(node*& t);
    void LR(node*& t);
    void RL(node*& t);
    void RR(node*& t);
    void insert(const Type& x,node*& t);
    bool remove(const Type& x,node*& t);
    bool adjust(node*& t,int subTree);
    int max(int a,int b){return(a > b)?a:b;}
    int height(node* t){return(t == NULL)?0:t->height;}
};

#endif // AVLTREE_H_INCLUDED
