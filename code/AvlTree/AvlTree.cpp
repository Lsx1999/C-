#include"AvlTree.h"
using namespace std;
template<class Type>
AvlTree<Type>:: AvlTree()
{
    root = NULL;
}

template<class Type>
AvlTree<Type>:: ~AvlTree()
{
    clear(root);
}

template<class Type>
void AvlTree<Type>:: clear(node* t)
{
    if(t == NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template<class Type>
bool AvlTree<Type>:: find(const Type& x)const
{
    node* tmp = root;
    while(tmp)
    {
        if(x == tmp->data)return true;
        if(x < tmp->data)tmp = tmp->left;
        else tmp = tmp->right;
    }
    return false;
}

template<class Type>
void AvlTree<Type>:: LL(node*& t)
{
    node* tmp = t->left;     //调整指针指向
    t->left = tmp->right;
    tmp->right = t;
    t->height = max(height(t->right),height(t->left)) + 1;   //重新计算高度
    tmp->height = max(height(t),height(tmp->left)) + 1;   //这里用eight()函数而不直接用数据成员height，是因为t->right这些参数可能为空
    t = tmp;   //通过引用传递将父节点与子节点连接起来
}

template<class Type>
void AvlTree<Type>:: LR(node*& t)
{
    RR(t->left);
    LL(t);
}

template<class Type>
void AvlTree<Type>:: RL(node*& t)
{
    LL(t->right);
    RR(t);
}

template<class Type>
void AvlTree<Type>:: RR(node*& t)
{
    node* tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t->height = max(height(t->left),height(t->right)) + 1;
    tmp->height = max(height(t),height(tmp->right)) + 1;
    t = tmp;
}

template<class Type>
void AvlTree<Type>:: insert(const Type& x)
{
    insert(x,root);
}

template<class Type>
void AvlTree<Type>:: insert(const Type& x,node*& t)
{
    if(!t)
    {
        t = new node(x);
        return;
    }
    if(x < t->data)
    {
        insert(x,t->left);
        if(height(t->left) - height(t->right) == 2)
           {
             if(x < t->left->data)
               LL(t);
             else
               LR(t);
           }
    }
    else
    {
        if(x > t->data)
        {
            insert(x,t->right);
            if(height(t->right) - height(t->left) == 2)
               {
                 if(x > t->right->data)
                    RR(t);
                 else
                    RL(t);
               }
        }
    }
    t->height = max(height(t->left),height(t->right)) + 1;
}

template<class Type>
void AvlTree<Type>:: remove(const Type& x)
{
    remove(x,root);
}

template<class Type>
bool AvlTree<Type>:: remove(const Type& x,node*& t)
{
    if(!t)
        return true;
    if(x == t->data)
    {
        if(!t->left || !t->right)  //删除叶子节点或者只有一个儿子的节点
        {
            node* tmp = t;
            t = (t->left)?t->left:t->right;
            delete tmp;
            return false;
        }
        else
        {
            node* tmp = t->right;
            while(tmp->left)
                tmp = tmp->left;
            t->data = tmp->data;
            if(remove(tmp->data,t->right))
                return true;
            return adjust(t,1);
        }
    }
    if(x < t->data)
    {
        if(remove(x,t->left))
            return true;
        return adjust(t,0);
    }
    else
    {
        if(remove(x,t->right))
            return true;
        return adjust(t,1);
    }
}

template<class Type>
bool AvlTree<Type>::adjust(node*& t,int subTree)
{
    if(subTree)  //删除发生在t的右子树上
    {
        if(height(t->left) - height(t->right) == 1)
            return true;
        if(height(t->left) == height(t->right))
           {
               --t->height;
              return false;
           }
        if(height(t->left->right) > height(t->left->left))
        {
            LR(t);
            return false;
        }
        LL(t);
        if(height(t->right) == height(t->left))
            return false;
        else
            return true;
    }
    else
    {
        if(height(t->right) - height(t->left) == 1)
            return true;
        if(height(t->left) == height(t->right))
           {
               --t->height;
              return false;
           }
        if(height(t->right->right) > height(t->right->left))
        {
            RL(t);
            return false;
        }
        RR(t);
        if(height(t->right) == height(t->left))
            return false;
        else
            return true;
    }
}
