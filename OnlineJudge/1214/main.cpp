#include<iostream>

using namespace std;

class outOfBound {};
class illegal {};

template<class T>
class linkStack
{
private:
	struct node
	{
		T data;
		node* next;

		node(const T& x, node* n = NULL) :data(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};
	node* Top;
public:
	linkStack();
	~linkStack();
	void push(const T& x);
	void pop();
	bool isEmpty()const;
	T top()const;
};

template<class T>
linkStack<T>::linkStack()
{
	Top = NULL;
}

template<class T>
linkStack<T>:: ~linkStack()
{
	node* tmp;
	while (Top)
	{
		tmp = Top;
		Top = Top->next;
		delete tmp;
	}
}

template<class T>
void linkStack<T>::push(const T& x)
{
	Top = new node(x, Top);
}

template<class T>
void linkStack<T>::pop()
{
	if (isEmpty())
		throw outOfBound();
	node* tmp = Top;
	Top = Top->next;
	delete tmp;
}

template<class T>
T linkStack<T>::top()const
{
	if (isEmpty())
		throw outOfBound();
	return Top->data;
}

template<class T>
bool linkStack<T>::isEmpty()const
{
	return Top == NULL;
}


template<class T>
class linkQueue
{
private:
	struct node
	{
		T data;
		node* next;

		node(const T& x, node* n = NULL) :data(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};
	node* front, * rear;
public:
	linkQueue();
	~linkQueue();
	void enqueue(const T& x);
	void dequeue();
	bool isEmpty()const;
	T getHead()const;
	T getTail()const;
};

template<class T>
linkQueue<T> ::linkQueue()
{
	front = rear = NULL;
}

template<class T>
linkQueue<T> :: ~linkQueue()
{
	node* tmp;
	while (front)
	{
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template<class T>
bool linkQueue<T> ::isEmpty()const
{
	return rear == NULL;
}

template<class T>
void linkQueue<T> ::enqueue(const T& x)
{
	if (rear == NULL)
		front = rear = new node(x);
	else
	{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template<class T>
void linkQueue<T> ::dequeue()
{
	if (rear == NULL)
		throw outOfBound();
	node * tmp = front;
	front = front->next;
	if (!front) rear = NULL;
	delete tmp;
}

template<class T>
T linkQueue<T> ::getHead()const
{
	if (front == NULL)
		throw outOfBound();
	return front->data;
}

template<class T>
T linkQueue<T> ::getTail()const
{
	if (rear == NULL)
		throw outOfBound();
	return rear->data;
}

template<class elemType>
class binaryTree
{
private:
	struct node
	{
		elemType data;
		int L, R;
		node* left, * right;

		node() :left(NULL), right(NULL) {}
		node(const elemType x, const int y, const int z, node* l = NULL, node* r = NULL) :data(x), L(y), R(z), left(l), right(r) {}
		~node() {}
	};
	node* root;
public:
	binaryTree() { root = NULL; }
	binaryTree(const elemType x, const int y, const int z) { root = new node(x, y, z); }
	~binaryTree() { clear(root); }
	void clear();
	bool isEmpty()const;
	bool isCBT()const;
	void buildTree(int n);  //n表示总结点数
	void BSpreOrder()const;
	void BSpostOrder()const;
	void BSlevelOrder()const;
private:
	void clear(node* t);

};

template<class elemType>
void binaryTree<elemType>::clear()
{
	clear(root);
}

template<class elemType>
void binaryTree<elemType>::clear(node * t)
{
	if (t == NULL)
		return;
	clear(t->left);
	clear(t->right);
	delete t;
	t = NULL;
}

template<class elemType>
bool binaryTree<elemType>::isEmpty()const
{
	return root == NULL;
}


template<class elemType>
bool binaryTree<elemType>::isCBT()const
{
	if (!root)
		return false;
	linkQueue<node*> q;
	q.enqueue(root);
	node* tmp;
	while (!q.isEmpty())
	{
		tmp = q.getHead();
		if (tmp->left && tmp->right)
		{
			q.dequeue();
			q.enqueue(tmp->left);
			q.enqueue(tmp->right);
		}
		if (!(tmp->left) && tmp->right)
			return false;
		if ((tmp->left && !(tmp->right)) || (!(tmp->left) && !(tmp->right)))
		{
			q.dequeue();
			while (!q.isEmpty())
			{
				tmp = q.getHead();
				if (!(tmp->left) && !(tmp->right))
					q.dequeue();
				else
					return false;
			}
			return true;
		}
	}
	return true;
}
template<class elemType>
void binaryTree<elemType>::buildTree(int n)  //n表示总结点数
{
	elemType value[n];
	int leftSon[n], rightSon[n];
	int a[n + 1], r;
	for (int i = 0; i < n + 1; ++i)
	{
		a[i] = i;
	}

	for (int i = 0; i < n; ++i)
	{
		cin >> leftSon[i] >> rightSon[i];
		cin >> value[i];
	}

	for (int i = 0; i < n; ++i)
	{
		a[leftSon[i]] = 0;
		a[rightSon[i]] = 0;
	}

	for (int i = 0; i < n + 1; ++i)
	{
		if (a[i] != 0)
		{
			r = i;
			break;
		}

	}

	root = new node(value[r - 1], leftSon[r - 1], rightSon[r - 1]);
	if (!root)
		return;
	linkQueue<node*> q;
	node * tmp;
	q.enqueue(root);
	while (!q.isEmpty())
	{
		tmp = q.getHead();
		q.dequeue();
		if (tmp->L != 0)
		{
			tmp->left = new node(value[tmp->L - 1], leftSon[tmp->L - 1], rightSon[tmp->L - 1]);
			q.enqueue(tmp->left);
		}
		if (tmp->R != 0)
		{
			tmp->right = new node(value[tmp->R - 1], leftSon[tmp->R - 1], rightSon[tmp->R - 1]);
			q.enqueue(tmp->right);
		}
	}

}

template<class elemType>
void binaryTree<elemType>::BSpreOrder()const
{
	if (!root)
		return;
	linkStack<node*> s;
	node* tmp;
	s.push(root);
	while (!s.isEmpty())
	{
		tmp = s.top();
		s.pop();
		cout << tmp->data << ' ';
		if (tmp->right)
			s.push(tmp->right);
		if (tmp->left)
			s.push(tmp->left);
	}
}




template<class elemType>
void binaryTree<elemType>::BSpostOrder()const
{
	if (!root)
		return;
	linkStack<node*> s;
	node* tmp;
	s.push(root);
	tmp = s.top();
	while (tmp->left)     //通过这个循环找到树的最左边元素
	{
		s.push(tmp->left);
		tmp = s.top();
	}
	while (!s.isEmpty())
	{
		tmp = s.top();
		s.pop();
		cout << tmp->data << ' ';
		if (tmp->right)
		{
			s.push(tmp->right);
			tmp = s.top();
			while (tmp->left)
			{
				s.push(tmp->left);
				tmp = s.top();
			}
		}
	}
}

template<class elemType>
void binaryTree<elemType>::BSlevelOrder()const
{
	if (!root)
		return;
	linkQueue<node*> q;
	node* tmp, * tmp2;
	q.enqueue(root);
	while (!q.isEmpty())
	{
		tmp = q.getHead();
		tmp2 = q.getTail();
		q.dequeue();
		cout << tmp->data << ' ';
		if (tmp2->right)
		{
			while (tmp2->right)
			{
				q.enqueue(tmp2->right);
				tmp2 = q.getTail();
			}
		}

		{
			if (tmp->left)
			{
				q.enqueue(tmp->left);
			}
		}

	}
}


int main()
{
	binaryTree<int> tree;
	int N;
	cin >> N;
	tree.buildTree(N);
	tree.BSpreOrder();
	cout << endl;
	tree.BSpostOrder();
	cout << endl;
	tree.BSlevelOrder();
	return 0;
}
