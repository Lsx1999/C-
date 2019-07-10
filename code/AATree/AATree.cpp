#include"AATree.h"

template<class KEY,class OTHER>
void AATree<KEY,OTHER>:: makeEmpty(node* t)
{
    if(t)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}

template<class KEY,class OTHER>
void AATree<KEY,OTHER>:: LL(node* &t)
{
    if(t->left && t->left->level == t->level)
   {
     node* tmp = t->left;
     t->left = tmp->right;
     tmp->right = t;
     t = tmp;
   }
}

template<class KEY,class OTHER>
void AATree<KEY,OTHER>:: RR(node* &t)
{
    if(t->right && t->right->right && t->right->right->level == t->level)
    {
        node* tmp = t->right;
        t->right = tmp->left;
        tmp->left = t;
        t = tmp;
        t->level++;
    }
}

template<class KEY,class OTHER>
void AATree<KEY,OTHER>:: insert(const SET<KEY,OTHER>& x,node* &t)
{
    if(!t)
    {
        t = new node(x);
        return;
    }
    if(x < t->data.key)
        insert(x,t->left);
    else if(x > t->data.key)
        insert(x,t->right);
        else return;
    LL(t);
    RR(t);
}

template<class KEY,class OTHER>
void AATree<KEY,OTHER>:: remove(const KEY& x,node* &t)
{
    if(!t)
        return;
    if( x < t->data.key)
        remove(x,t->left);
    else
    {
        if(x > t->data.key)
            remove(x,t->right);
        else
        {
            if(t->left && t->right)
            {
                node* tmp = t->right;
                while(tmp->left)
                    tmp = tmp->left;
                t->data = tmp->data;
                remove(t->data.key,t->right);
            }
            else
            {
                node* old = t;
                t = (t->left != NULL)?t->left:t->right;
                delete old;
                return;
            }
        }
    }
    if(!t->left || !t->right)
        t->level = 1;
    else
        t->level = min(t->left->level,t->right->level) + 1;
    if(t->right && t->right->level > t->level)
        t->right->level = t->level;
    LL(t);
    if(t->right)
        LL(t->right);
    if(t->right && t->right->right)
        LL(t->right->right);
    RR(t);
    if(t->right)
        RR(t->right);
}
