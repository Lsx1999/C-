#include"RedBlackTree.h"
#include<iostream>
using namespace std;

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: makeEmpty(node* &t)
{
    if(t)
    {
        makeEmpty(t->left);
        makeEmpty(t->righr);
        delete t;
    }
    t = NULL;
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: LL(node* gp)
{
    node *p = gp->left,*t = p->left;
    node tmp = *gp;
    gp->data = p->data;
    gp->left = t;
    gp->left = p;
    p->data = tmp.data;
    p->left = p->right;
    p->right = tmp.right;
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: LR(node* gp)
{
    node *p = gp->left,*t = p->right;
    node tmp = *gp;
    gp->data = t->data;
    gp->right = t;
    p->right = t->left;
    t->data = tmp.data;
    t->left = t->right;
    t->right = tmp.right;
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: RL(node* gp)
{
    node *p = gp->right,*t = p->left;
    node tmp = *gp;
    gp->data = t->data;
    gp->left = t;
    p->left = t->right;
    t->data = tmp.data;
    t->right = t->left;
    t->left = tmp.left;
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: RR(node* gp)
{
    node *p = gp->right,*t = p->right;
    node tmp = *gp;
    gp->data = p->data;
    gp->right = t;
    gp->left = p;
    p->data = tmp.data;
    p->right = p->left;
    p->left = tmp.left;
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: insert(const SET<KEY,OTHER>& x)
{
    if(!root)
    {
        root = new node(x,NULL,NULL,BLACK);return;
    }
    node *gp,*p,*t;
    gp = p = t = root;
    while(true)
    {
        if(t)
        {
            if(t->left && t->left->colour == RED && t->right && t->right->colour == RED)
            {
                t->left->colour = t->right->colour = BLACK;
                t->colour = RED;
                insertAdjust(gp,p,t);
            }
            gp = p;
            p = t;
            t = ((t->data.key > x.key)?t->left:t->right);
        }
        else
        {
            t = new node(x);
            if(x.key < p->data.key)
                p->left = t;
            else
                p->right = t;
            insertAdjust(gp,p,t);
            root->colour = BLACK;
            return;
        }
    }
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: insertAdjust(node* gp,node* p,node* t)
{
    if(p->colour)
        return;
    if(p == root)
    {
        p->colour = BLACK;
        return;
    }
    if(gp->left == p)
    {
        if(t == p->left)
            LL(gp);
        else
            LR(gp);
    }
    else
    {
        if(t == p->right)
            RR(gp);
        else
            RL(gp);
    }
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: remove(const KEY& x)
{
    KEY del = x;
    node *t,*p,*c;
    if(!root)
        return;
    if(root->data.key == x && !root->left && !root->right)
    {
        delete root;
        root = NULL;
        return;
    }
    p = c = t = root;
    while(true)
    {
        removeAdjust(p,c,t,del);
        if(c->data.key == del && c->left && c->right)
        {
            node* tmp = c->right;
            while(tmp->left)
                tmp = tmp->left;
            c->data = tmp->data;
            del = tmp->data.key;
            p = c;
            c = c->right;
            t = p->left;
            continue;
        }
        if(c->data.key == del)
        {
            if(p->left == c)
                p->left = NULL;
            else
                p->right = NULL;
            delete c;
            root->colour = BLACK;
            return;
        }
        p = c;
        c = (del < p->data.key)?p->left:p->right;
        t = (c == p->left)?p->right:p->left;
    }
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>:: removeAdjust(node* &p,node* &c,node* &t,KEY del)
{
    if(c->colour == RED)
        return;
    if(c == root)
    {
        if(c->left && c->right && c->right->colour == c->left->colour)
        {
            c->colour = RED;
            c->left->colour = c->right->colour = BLACK;
            return;
        }
    }

    if((c->left && c->left->colour || !c->left) && (c->right && c->right->colour || !c->right))
        if((t->left && t->left->colour || !t->left) && (t->right && t->right->colour || !t->right))
            {
                p->colour = BLACK;
                t->colour = c->colour = RED;
            }
        else
        {
            if(p->left == t)
                if(t->left && t->left->colour == RED)
            {
                t->left->colour = BLACK;
                LL(p);
                p = t;
            }
            else
            {
                LR(p);
                p = p->right;
                p->colour = BLACK;
            }
            else if(t->right && t->right->colour == RED)
            {
                t->right->colour = BLACK;
                RR(p);
                p = t;
            }
            else
            {
                RL(p);
                p = p->left;
                p->colour = BLACK;
            }
            c->colour = RED;
        }
        else
        {
            if(c->data.key == del)
            {
                if(c->left && c->right)
                {
                    if(c->right->colour == BLACK)
                    {
                        LL(c);
                        c = c->right;
                    }
                    return;
                }
                if(c->left)
                {
                    LL(c);
                    p = c;
                    c = c->right;
                }
                else
                {
                    RR(c);
                    p = c;
                    c = c->left;
                }
            }
            else
            {
                p = c;
                c = (del < p->data.key)?p->left:p->right;
                t = (c == p->left)?p->right:p->left;
                if(c->colour == BLACK)
                {
                    if(t == p->right)
                        RR(p);
                    else
                        LL(p);
                    p = t;
                    t = (c == p->left)?p->right:p->left;
                    removeAdjust(p,c,t,del);
                }
            }
        }
}
