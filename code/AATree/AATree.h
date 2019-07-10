#ifndef AATREE_H_INCLUDED
#define AATREE_H_INCLUDED
#include<iostream>
template<class KEY,class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY,class OTHER>
class AATree
{
private:
    struct node
    {
        SET<KEY,OTHER> data;
        node *left,*right;
        int level;

        node(const SET<KEY,OTHER>& x,node* l = NULL,node* r = NULL,int lev = 1):data(x),left(l),right(r),level(lev){}
    };
    node* root;
public:
    AATree(){root = NULL;}
    ~AATree(){makeEmpty(root);}
    void insert(const SET<KEY,OTHER>& x){insert(x,root);}
    void remove(const KEY& x){remove(x,root);}
    node* find(const KEY& x)const
    {
        node* tmp = root;
        while(tmp)
        {
            if(x == tmp->data.key)
                return tmp;
            if(x < tmp->data.key)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        return NULL;
    }
private:
    void makeEmpty(node* t);
    void LL(node* &t);
    void RR(node* &t);
    void insert(const SET<KEY,OTHER>& x,node* &t);
    void remove(const KEY& x,node* &t);
    int min(int a,int b){return (a < b)?a:b;}
};

#endif // AATREE_H_INCLUDED
