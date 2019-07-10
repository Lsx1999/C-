#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
# include <stdio.h>
using namespace std;


template<class KEY, class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};


template<class KEY, class OTHER>
class AvlTree
{
private:
	struct node
	{
		SET<KEY, OTHER> data;
		node* left, * right;
		int height;

		node(const SET<KEY, OTHER>& element, node* l = NULL, node* r = NULL, int h = 1) :data(element), left(l), right(r), height(h) {}
	};
	node* root;
public:
	AvlTree() { root = NULL; }
	~AvlTree() { makeEmpty(root); }
	SET<KEY, OTHER>* find(const KEY& x)const
	{
		node* tmp = root;
		while (tmp != NULL && tmp->data.key != x)
		{
			if (tmp->data.key > x)
				tmp = tmp->left;
			else
			{
				tmp = tmp->right;
			}

		}
		if (!tmp)
			return NULL;
		else
		{
			return (SET<KEY, OTHER>*)tmp;
		}

	}


	void insert(const SET<KEY, OTHER>& x);

private:
	void insert(const SET<KEY, OTHER> & x, node * &t);
	void makeEmpty(node * t);
	int height(node * t) { return(t == NULL) ? 0 : t->height; }
	void LL(node * &t);
	void LR(node * &t);
	void RL(node * &t);
	void RR(node * &t);
	int max(int a, int b) { return(a > b) ? a : b; }
};



template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::makeEmpty(node * t)
{
	if (t == NULL)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
	t = NULL;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(node * &t)
{
	node* tmp = t->left;     //调整指针指向
	t->left = tmp->right;
	tmp->right = t;
	t->height = max(height(t->right), height(t->left)) + 1;   //重新计算高度
	tmp->height = max(height(t), height(tmp->left)) + 1;   //这里用eight()函数而不直接用数据成员height，是因为t->right这些参数可能为空
	t = tmp;   //通过引用传递将父节点与子节点连接起来
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(node * &t)
{
	RR(t->left);
	LL(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(node * &t)
{
	LL(t->right);
	RR(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(node * &t)
{
	node* tmp = t->right;
	t->right = tmp->left;
	tmp->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	tmp->height = max(height(t), height(tmp->right)) + 1;
	t = tmp;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> & x)
{
	insert(x, root);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> & x, node * &t)
{
	if (!t)
	{
		t = new node(x);
		return;
	}
	if (x.key < t->data.key)
	{
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2)
		{
			if (x.key < t->left->data.key)
				LL(t);
			else
				LR(t);
		}
	}
	else
	{
		if (x.key > t->data.key)
		{
			insert(x, t->right);
			if (height(t->right) - height(t->left) == 2)
			{
				if (x.key > t->right->data.key)
					RR(t);
				else
					RL(t);
			}
		}
	}
	t->height = max(height(t->left), height(t->right)) + 1;
}


int main()
{
	int n,i,j,k;
	int max = 0,index = 0;
	char s[10];
	AvlTree<int, int> t;
	scanf("%d", &n);
	for (k = 0; k < n; ++k)
	{
		SET<int, int> paper;
		paper.key = k;
		paper.other = 0;
		t.insert(paper);
	}
	while (true)
	{
		scanf("%s", &s);
		if (s[0] == 'a')
		{
			scanf("%d%d", &i, &j);
			int cnt = ++t.find(j)->other;
			if (cnt > max)
			{
				max = cnt;
				index = j;
			}
			else
			{
				if (max == cnt && index > j)
					index = j;
			}
		}
		if (s[0] == 'q')
		{
			printf("%d %d\n", index, max);
		}
		if (s[0] == 'f')
			break;
	}
	return 0;
}
