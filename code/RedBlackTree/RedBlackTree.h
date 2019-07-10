#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED
#include<iostream>
using namespace std;
template<class KEY,class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY,class OTHER>
class RedBlackTree
{
    enum colourT{RED,BLACK};
    struct node
    {
        SET<KEY,OTHER> data;
        node *left,*right;
        colourT colour;

        node(const SET<KEY,OTHER>& element,node* l = NULL,node* r = NULL,colourT c = RED):data(element),left(l),right(r),colour(c){}
        ~node(){}
    };
    node* root;
public:
    RedBlackTree(node* t = NULL){root = t;}
    ~RedBlackTree(){makeEmpty(root);}
    void insert(const SET<KEY,OTHER>& x);
    void remove(const KEY& x);
    node* find(const KEY& x)const
    {
        node* tmp = root;
        while(tmp)
        {
            if(x == tmp->data.key)
                return tmp;
            if(x > tmp->data.key)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return NULL;
    }
private:
    void makeEmpty(node* &t);
    void insertAdjust(node* gp,node* p,node* t);
    void removeAdjust(node* &p,node* &c,node* &t,KEY del);
    void LL(node* gp);
    void LR(node* gp);
    void RL(node* gp);
    void RR(node* gp);
};

#endif // REDBLACKTREE_H_INCLUDED
