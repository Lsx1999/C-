#include<iostream>

using namespace std;

class outOfBound {};
class illegal {};


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

template<class elemType>
struct node
{
	elemType data,L,R;
	node* left, * right;

	node() :left(NULL), right(NULL) {}
	node(const elemType x, const elemType y, const elemType z, node* l = NULL, node* r = NULL) :data(x),L(y),R(z), left(l), right(r) {}
	~node() {}
};

template<class elemType>
class binaryTree
{
private:
	node<elemType>* root;
public:
	binaryTree() { root = NULL; }
	binaryTree(const elemType x, const elemType y, const elemType z) { root = new node<elemType>(x,y,z); }
	~binaryTree() { clear(root); }
	void clear();
	node<elemType>* buildTree(int n, node<elemType>* t[])
	{

		int Pi, Qi, x;
		int* a;
		a = new int[n];                  //数组a是用来找寻根节点的
		for (int j = 1; j <= n; ++j)
		{
			a[j - 1] = j;
		}

		for (int i = 1; i <= n; ++i)              //通过这个循环为t中的元素赋值
		{
			cin >> Pi >> Qi;
			t[i] = new node<elemType>(i, Pi, Qi);
		}

		for (int i = 1; i <= n; ++i)           //将每个节点连接起来
		{
			if (t[i]->L != 0)
			{
				t[i]->left = t[t[i]->L];
				a[t[i]->L - 1] = 0;
			}
			if (t[i]->R != 0)
			{
				t[i]->right = t[t[i]->R];
				a[t[i]->R - 1] = 0;
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (a[i] != 0)
			{
				x = i + 1; break;
			}
		}
		root = t[x];
		return root;
	}
private:
	void clear(node<elemType>* t);

};

template<class elemType>
void binaryTree<elemType>::clear()
{
	clear(root);
}

template<class elemType>
void binaryTree<elemType>::clear(node<elemType> * t)
{
	if (t == NULL)
		return;
	clear(t->left);
	clear(t->right);
	delete t;
	t = NULL;
}


node<int>* t[100000 + 1];

int main()
{
	void levelOrder(node<int>*);
	binaryTree<int> tree;
	bool isCBT(node<int>*);
	node<int>* Root;
	int N;
	cin >> N;
	t[0] = NULL;
	Root = tree.buildTree(N,t);
	if (isCBT(Root))
		cout << 'Y';
	else
		cout << 'N';
	return 0;
}

bool isCBT(node<int>* R)
{
	if (!R)
		return false;
	linkQueue<node<int>*> q;
	q.enqueue(R);
	//node<elemType>* tmp;
	while (!q.isEmpty())
	{
		//tmp = q.getHead();
		if (q.getHead()->left && q.getHead()->right)
		{
			q.enqueue(q.getHead()->left);
			q.enqueue(q.getHead()->right);
			q.dequeue();
		}
		if (!(q.getHead()->left) && q.getHead()->right)
			return false;
		if ((q.getHead()->left && !(q.getHead()->right)) || (!(q.getHead()->left) && !(q.getHead()->right)))
		{
			q.dequeue();
			while (!q.isEmpty())
			{
				//tmp = q.getHead();
				if (!(q.getHead()->left) && !(q.getHead()->right))
					q.dequeue();
				else
					return false;
			}
			return true;
		}
	}
	return true;
}

