#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
# include <stdio.h>
using namespace std;

template<class KEY, class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};

template<class KEY, class OTHER>
struct node
{
	SET<KEY, OTHER> data;
	node* left, * right;
	int height;

	node(const SET<KEY, OTHER>& element, node* l = NULL, node* r = NULL, int h = 1) :data(element), left(l), right(r), height(h) {}
	node() :left(NULL), right(NULL), height(1) {}
	~node() {}
};

template<class KEY, class OTHER>
class AvlTree
{
private:
	node<KEY, OTHER>* root;
public:
	AvlTree() { root = NULL; }
	~AvlTree() { makeEmpty(root); }
	SET<KEY, OTHER>* find(const KEY& x)const
	{
		node<KEY, OTHER>* tmp = root;
		while (tmp != NULL && strcmp(tmp->data.key ,x)!=0)
		{
			if ( strcmp(tmp->data.key,x) > 0)
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
	void insert(const SET<KEY, OTHER> & x, node<KEY, OTHER>* &t);
	void makeEmpty(node<KEY, OTHER>* t);
	int height(node<KEY, OTHER>* t) { return(t == NULL) ? 0 : t->height; }
	void LL(node<KEY, OTHER>* &t);
	void LR(node<KEY, OTHER>* &t);
	void RL(node<KEY, OTHER>* &t);
	void RR(node<KEY, OTHER>* &t);
	int max(int a, int b) { return(a > b) ? a : b; }
};



template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::makeEmpty(node<KEY, OTHER>* t)
{
	if (t == NULL)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
	t = NULL;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(node<KEY, OTHER>* &t)
{
	node<KEY, OTHER>* tmp = t->left;     //调整指针指向
	t->left = tmp->right;
	tmp->right = t;
	t->height = max(height(t->right), height(t->left)) + 1;   //重新计算高度
	tmp->height = max(height(t), height(tmp->left)) + 1;   //这里用eight()函数而不直接用数据成员height，是因为t->right这些参数可能为空
	t = tmp;   //通过引用传递将父节点与子节点连接起来
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(node<KEY, OTHER>* &t)
{
	RR(t->left);
	LL(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(node<KEY, OTHER>* &t)
{
	LL(t->right);
	RR(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(node<KEY, OTHER>* &t)
{
	node<KEY, OTHER>* tmp = t->right;
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
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> & x, node<KEY, OTHER>* &t)
{
	if (!t)
	{
		t = new node<KEY, OTHER>(x);
		return;
	}
	if (strcmp(x.key,t->data.key) < 0)
	{
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2)
		{
			if (strcmp(x.key,t->left->data.key) < 0)
				LL(t);
			else
				LR(t);
		}
	}
	else
	{
		if (strcmp(x.key,t->data.key) > 0)
		{
			insert(x, t->right);
			if (height(t->right) - height(t->left) == 2)
			{
				if (strcmp(x.key,t->right->data.key) > 0)
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
	int max = 0;
	char s[10], name[300];
	AvlTree<char*, int> t;
	while (true)
	{
		scanf("%s", s);
		if (s[0] == 'c')
		{
			char title[300];
			//cin.get();
			//cin.getline(title, 300);
			getchar();
			scanf("%[^\n]",title);
			SET<char*, int>* t1 = t.find(title);
			if (!t1)
			{
				SET< char*, int> paper;
				paper.key = new char[300];
				strcpy(paper.key,title);
				paper.other = 1;
				t.insert(paper);
				if (max < paper.other)
				{
					max = paper.other;
					strcpy(name, paper.key);
				}
				else
				{
					if (max == paper.other && strcmp(name, paper.key) > 0)
					{
						strcpy(name, paper.key);
					}
				}
			}
			else
			{
				int cnt = ++t1->other;
				if (max < cnt)
				{
					max = cnt;
					strcpy(name, title);
				}
				else
				{
					if (max == cnt && strcmp(name, title) > 0)
					{
						strcpy(name, title);
					}
				}

			}

		}
		if (s[0] == 'q')
		{
			printf("%d %s\n", max, name);
		}
		if (s[0] == 'f')
			break;
	}
	return 0;
}
