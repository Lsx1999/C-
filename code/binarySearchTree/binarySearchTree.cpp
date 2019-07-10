#include<iostream>
#include"binarySearchTree.h"
using namespace std;

template<class Type>
binarySearchTree<Type>:: binarySearchTree()
{
    root = NULL;
}

template<class Type>
binarySearchTree<Type>:: ~binarySearchTree()
{
    clear(root);
}
template<class Type>
bool binarySearchTree<Type>:: find(const Type& x)const
{
    node* tmp;
    tmp = root;
    while(tmp)
    {
        if(x == tmp->data)
            return true;
        if(x < tmp->data)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return false;
}

template<class Type>
void binarySearchTree<Type>:: insert(const Type& x)
{
    if(find(x))
        return;
    node *p,*parent = NULL;
    int flag;
    p = root;
    while(p)
    {
        if(x < p->data)
        {
            parent = p;
            p = p->left;
            flag = 1;
        }
        else
        {
            parent = p;
            p = p->right;
            flag = 2;
        }
    }
    if(parent == NULL)
        {root = new node(x);return;}
    if(flag == 1)
        {parent->left = new node(x);return;}
    if(flag == 2)
        {parent->right = new node(x);return;}
}

template<class Type>
void binarySearchTree<Type>:: clear(node* &t)
{
    if(t == NULL)
        return;
    if(t->left)
        clear(t->left);
    if(t->right)
        clear(t->right);
    delete t;
    t = NULL;
}

template<class Type>
void binarySearchTree<Type>::remove(const Type& x)
{
	node* p, * parent = NULL;
	int flag;
	p = root;
	while (p)
	{
	    if(p->data == x)
            break;
		if (x < p->data)
		{
			parent = p;
			p = p->left;
			flag = 1;
		}
		else
		{
			parent = p;
			p = p->right;
			flag = 2;
		}
	}
	if(!p) return;
	if ((!p->left) || (!p->right))  //��ɾ�����ΪҶ�ӻ���ֻ��һ�����ӵĽ��
	{
		if (!parent) { root = (root->left) ? root->left : root->right; delete p; return; }
		if (flag == 1)
		{
			parent->left = (p->left) ? p->left : p->right ;delete p;
		}
		else
		{
			parent->right = (p->left) ? p->left : p->right ;delete p;
		}
		return;
	}
	if ((p->left) && (p->right))//��ɾ���������������
	{
		node* r = p;
		parent = p; flag = 1; p = p->left; //�����������������㼴�����
		while (p->right) { parent = p; flag = 2; p = p->right; }

		r->data = p->data;  //���������Ԫ��ֵ��������ɾ�����r�ϣ�
		//�����Ϊɾ������, �������������
		if (flag == 1)
		{
			parent->left = p->left;  delete p;
		}
		else
		{
			parent->right = p->left; delete p;
		}

	}
}
