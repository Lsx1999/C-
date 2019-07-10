#include<iostream>
#include"binaryTree.h"
#include"queue.h"
#include"stack.h"

using namespace std;

template<class elemType>
void binaryTree<elemType>:: clear()
{
    clear(root);
}

template<class elemType>
void binaryTree<elemType>:: clear(node *t)
{
    if(t == NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template<class elemType>
bool binaryTree<elemType>:: isEmpty()const
{
    return root == NULL;
}

template<class elemType>
elemType binaryTree<elemType>:: Root(elemType flag)const
{
    if(!root)
        return flag;
    return root->data;
}

template<class elemType>
elemType binaryTree<elemType>:: lchild(elemType x,elemType flag)const
{
    node* tmp = find(x,root);
    if(tmp == NULL || tmp->left == NULL)
        return flag;
    return tmp->left->data;
}

template<class elemType>
elemType binaryTree<elemType>:: rchild(elemType x,elemType flag)const
{
    node* tmp = find(x,root);
    if(tmp == NULL || tmp->right == NULL)
        return flag;
    return tmp->right->data;
}

template<class elemType>
void binaryTree<elemType>:: delLeft(elemType x)
{
    node* tmp = find(x,root);
    if(!tmp)
        return;
    clear(tmp->left);
}

template<class elemType>
void binaryTree<elemType>:: delRight(elemType x)
{
    node* tmp = find(x,root);
    if(!tmp)
        return;
    clear(tmp->right);
}

template<class elemType>
void binaryTree<elemType>:: preOrder()const
{
    if(!root)
        return;
    linkStack<node*> s;
    node* tmp;
    s.push(root);
    while(!s.isEmpty())
    {
        tmp = s.top();
        s.pop();
        cout<<tmp->data<<' ';
        if(tmp->right)
            s.push(tmp->right);
        if(tmp->left)
            s.push(tmp->left);
    }
}

template<class elemType>
void binaryTree<elemType>:: midOrder()const
{
    if(!root)
        return;
    linkStack<node*> s;
    node* tmp;
    s.push(root);
    tmp = s.top();
    while(tmp->left)     //通过这个循环找到树的最左边元素
    {
        s.push(tmp->left);
        tmp = s.top();
    }
    while(!s.isEmpty())
    {
        tmp = s.top();
        s.pop();
        cout<<tmp->data<<' ';
        if(tmp->right)
        {
            s.push(tmp->right);
            tmp = s.top();
            while(tmp->left)
            {
                s.push(tmp->left);
                tmp = s.top();
            }
        }
    }
}

template<class elemType>
void binaryTree<elemType>:: postOrder()const
{
    if(!root)
        return;
    linkStack<node*> s1;
    linkStack<int> s2;
    node* tmp;
    s1.push(root);
    s2.push(0);
    while(!s1.isEmpty())
    {
        tmp = s1.top();
        if(s2.top() == 0)
        {
            s2.pop();
            s2.push(1);
            if(tmp->left)
            {
                s1.push(tmp->left);
                s2.push(0);
            }
        }
        if(s2.top() == 1)
        {
            s2.pop();
            s2.push(2);
            if(tmp->right)
            {
                 s1.push(tmp->right);
                 s2.push(0);
            }
        }
        if(s2.top() == 2)
        {
            cout<<tmp->data<<' ';
            s1.pop();
            s2.pop();
        }
    }
}

template<class elemType>
void binaryTree<elemType>:: levelOrder()const
{
    if(!root)
        return;
    linkQueue<node*> q;
    node* tmp;
    q.enqueue(root);
    while(!q.isEmpty())
    {
        tmp = q.getHead();
        q.dequeue();
        cout<<tmp->data<<' ';
        if(tmp->left)
            q.enqueue(tmp->left);
        if(tmp->right)
            q.enqueue(tmp->right);
    }
}

template<class elemType>
void binaryTree<elemType>:: creatTree(elemType flag)
{
    linkQueue<node*> q;
    node* tmp;
    elemType x,ldata,rdata;
    cout<<"请输入根节点";
    cin>>x;
    if(x == flag)
        return;
    root = new node(x);
    q.enqueue(root);
    while(!q.isEmpty())
    {
        tmp = q.getHead();
        q.dequeue();
        cout<<"请输入"<<tmp->data<<"的左子";
        cin>>ldata;
        cout<<"请输入"<<tmp->data<<"的右子";
        cin>>rdata;
        if(ldata != flag)
            q.enqueue(tmp->left = new node(ldata));
        if(rdata != flag)
            q.enqueue(tmp->right = new node(rdata));
    }
    cout<<"creat completed!"<<endl;
}
