#include<iostream>
#include<string>
using namespace std;

template<class KEY, class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};

template<class KEY, class OTHER>
class binarySearchTree
{
private:
	struct node
	{
		SET<KEY, OTHER> data;
		node* left, * right;

		node(const SET<KEY, OTHER>& thedata, node* l = NULL, node* r = NULL) :data(thedata), left(l), right(r) {}
		node() :left(NULL), right(NULL) {}
		~node() {}
	};
	node* root;
public:
	binarySearchTree();
	~binarySearchTree();
	SET<KEY, OTHER>* find(const KEY& x)const { return find(x, root); }
	void insert(const SET<KEY, OTHER>& x);
	void remove(const KEY& x);
	KEY getRoot()
	{
		return root->data.key;
	}
	bool isEmpty()const
	{
		return (root == NULL);
	}
private:
	void insert(const SET<KEY, OTHER> & x, node * &t);
	void remove(const KEY & x, node * &t);
	SET<KEY, OTHER>* find(const KEY & x, node * t)const
	{
		if (t == NULL || t->data.key == x)
			return (SET<KEY, OTHER>*)t;
		if (x < t->data.key)
			return find(x, t->left);
		else
			return find(x, t->right);
	}
	void makeEmpty(node * t);
};

template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> & x)
{
	insert(x, root);
}

template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> & x, node * &t)  //相等的不插入
{
	if (t == NULL)
		t = new node(x);
	else
	{
		if (x.key < t->data.key)
			insert(x, t->left);
		else
		{
			if (x.key > t->data.key)
				insert(x, t->right);
		}
	}
}

template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::remove(const KEY & x)
{
	remove(x, root);
}

template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::remove(const KEY & x, node * &t)
{
	if (t == NULL)
		return;
	if (x < t->data.key)
		remove(x, t->left);
	else
	{
		if (x > t->data.key)
			remove(x, t->right);
		else
		{
			if (t->left && t->right)
			{
				node* tmp = t->right;
				while (tmp->left)
					tmp = tmp->left;
				t->data = tmp->data;
				remove(t->data.key, t->right);
			}
			else
			{
				node* oldNode = t;
				t = (t->left) ? t->left : t->right;
				delete oldNode;
			}
		}
	}

}

template<class KEY, class OTHER>
binarySearchTree<KEY, OTHER>::binarySearchTree()
{
	root = NULL;
}

template<class KEY, class OTHER>
binarySearchTree<KEY, OTHER>:: ~binarySearchTree()
{
	makeEmpty(root);
}

template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::makeEmpty(node * t)
{
	if (!t)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
}

//***************************************************************************************************************************************************
struct nameList
{

	struct node
	{
		string name;
		node* next;

		node(const string& x, node* n = NULL) :name(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};
	node* head, * tail;

	nameList()
	{
		head = tail = NULL;
	}

	void add(const string& n)
	{
		if (head == NULL)
		{
			head = tail = new node(n);
		}
		else
		{
			node* tmp = new node(n);
			tail->next = tmp;
			tail = tmp;
			tail->next = NULL;
		}
	}
	void display()
	{
		node* p = head;
		while (p)
		{
			ios::sync_with_stdio(false);
			cout << p->name << ' ';
			p = p->next;
		}
	}
};


int main()
{
	int n, i;
	binarySearchTree<string, nameList> t;
	string name, email;
	string email1[10000];
	int cnt1 = 0;
	ios::sync_with_stdio(false);
	cin >> n;
	for (i = 0; i < n; ++i)
	{
		ios::sync_with_stdio(false);
		cin >> name;
		ios::sync_with_stdio(false);
		cin >> email;
		if (t.find(email))
		{
			t.find(email)->other.add(name);
		}
		else
		{
			email1[cnt1] = email;
			cnt1++;
			SET<string, nameList> auth;
			auth.key = email;
			auth.other.add(name);
			t.insert(auth);
		}
	}
	for (i = 0; i < cnt1; ++i)
	{
		t.find(email1[i])->other.display();
		ios::sync_with_stdio(false);
		cout <<'\n';
	}
	return 0;
}
