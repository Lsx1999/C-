#ifndef LEFTHEAP_H_INCLUDED
#define LEFTHEAP_H_INCLUDED
#include<iostream>
using namespace std;

template<class Type>
class leftHeap
{
private:
    struct node
    {
        Type data;
        int npl;
        node *left,*right;

        node(const Type& x):data(x),npl(0),left(NULL),right(NULL){}
        node():npl(0),left(NULL),right(NULL){}
        ~node(){}
    };
node* root;
void clear(node* r);
public:
    leftHeap();
    ~leftHeap();
    void enqueue(const Type& x);
    void dequeue();
    bool isEmpty()const;
    Type getHead()const;
    node* merge(node* r1,node* r2)
    {
        node *r,*tmp;
    if(!r1 || !r2)
        return (r1)?r1:r2;
    if(r1->data < r2->data)
    {
        r = r1;
        r->right = merge(r1->right,r2);
    }
    else
    {
        r = r2;
        r->right = merge(r2->right,r1);
    }
    if(!r->left && r->right)
    {
        r->left = r->right;
        r->right = NULL;
        r->npl = 0;
    }
    else
        if(r->left && r->right)
    {
       if(r->left->npl < r->right->npl)
       {
            tmp = r->left;
            r->left = r->right;
            r->right = tmp;
       }
        r->npl = r->right->npl + 1;
    }
    return r;
    }
};


#endif // LEFTHEAP_H_INCLUDED
