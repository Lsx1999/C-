#include<iostream>
using namespace std;

template<class Type>
class binarySearchTree
{
private:
	struct node
	{
		Type data;
		node* left, * right;

		node(Type x, node* l = NULL, node* r = NULL) :data(x), left(l), right(r) {}
		node() :left(NULL), right(NULL) {}
		~node() {}
	};
	node* root;
public:
	binarySearchTree();
	~binarySearchTree();
	bool find(const Type& x)const;
	void insert(const Type& x);
	void remove(const Type& x);
	void midorder()const;
	void clear();
private:
	void clear(node*& t);
	void midorder(node* t)const;
};

template<class Type>
binarySearchTree<Type>::binarySearchTree()
{
	root = NULL;
}

template<class Type>
binarySearchTree<Type>:: ~binarySearchTree()
{
	clear(root);
}
template<class Type>
bool binarySearchTree<Type>::find(const Type& x)const
{
	node* tmp;
	tmp = root;
	while (tmp)
	{
		if (x == tmp->data)
			return true;
		if (x < tmp->data)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return false;
}

template<class Type>
void binarySearchTree<Type>::insert(const Type& x)
{
	if (find(x))
		return;
	node* p, * parent = NULL;
	int flag;
	p = root;
	while (p)
	{
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
	if (parent == NULL)
	{
		root = new node(x); return;
	}
	if (flag == 1)
	{
		parent->left = new node(x); return;
	}
	if (flag == 2)
	{
		parent->right = new node(x); return;
	}
}

template<class Type>
void binarySearchTree<Type>::clear(node*& t)
{
	if (t == NULL)
		return;
	if (t->left)
		clear(t->left);
	if (t->right)
		clear(t->right);
	delete t;
	t = NULL;
}

template<class Type>
void binarySearchTree<Type>::clear()
{
	clear(root);
}


template<class Type>
void binarySearchTree<Type>::remove(const Type& x)
{
	node* p, * parent = NULL;
	int flag;
	p = root;
	while (p)
	{
		if (p->data == x)
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
	if (!p) return;
	if ((!p->left) || (!p->right))
	{
		if (!parent) { root = (root->left) ? root->left : root->right; delete p; return; }
		if (flag == 1)
		{
			parent->left = (p->left) ? p->left : p->right; delete p;
		}
		else
		{
			parent->right = (p->left) ? p->left : p->right; delete p;
		}
		return;
	}
	if ((p->left) && (p->right))
	{
		node* r = p;
		parent = p; flag = 1; p = p->left;
		while (p->right) { parent = p; flag = 2; p = p->right; }

		r->data = p->data;
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

template<class Type>
void binarySearchTree<Type>::midorder()const
{
	midorder(root);
}

template<class Type>
void binarySearchTree<Type>::midorder(node* t)const
{
	if (t == NULL)
		return;
	midorder(t->left);
	cout << t->data << ' ';
	midorder(t->right);
}

int a[100];
int same[100];
int main()
{
	binarySearchTree<int> tree;
	int n, m, i, j, cnt;
	char c;
	cin >> n;
	for (i = 0; i < n; ++i)
	{
		cnt = 0;
		cin >> c;
		cin >> m;
		if (c == '+')
		{
			for (j = 0; j < m; ++j)
			{
				cin >> a[j];
				tree.insert(a[j]);
			}
		}

		if (c == '-')
		{
			for (j = 0; j < m; ++j)
			{
				cin >> a[j];
				tree.remove(a[j]);
			}
		}

		if (c == '*')
		{
			for (j = 0; j < m; ++j)
			{
				cin >> a[j];
				if (tree.find(a[j]))
				{
					same[cnt] = a[j];
					cnt++;
				}
			}
			tree.clear();
			for (j = 0; j < cnt; ++j)
			{
				tree.insert(same[j]);
			}
		}
		tree.midorder();
		cout << endl;
	}
	return 0;
}
