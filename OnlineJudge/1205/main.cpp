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

struct Ack
{
	int vm, vn;
	int value;
	int flag;
};

int main()
{
	linkStack<Ack> s;
	Ack init;
	cin >> init.vm >> init.vn;
	init.flag = 1;
	s.push(init);
	while (!s.isEmpty())
	{
		if (s.top().flag == 1)
		{
			if (s.top().vm == 0)
			{
				Ack A = s.top();
				s.pop();
				A.value = A.vn + 1;
				A.flag = 0;
				s.push(A);
			}
			else
			{
				if (s.top().vn == 0)
				{
					Ack A1;
					A1.vm = s.top().vm - 1;
					A1.vn = 1;
					A1.flag = 1;
					s.push(A1);
				}
				else
				{
					Ack A2;
					A2.vm = s.top().vm;
					A2.vn = s.top().vn - 1;
					A2.flag = 1;
					s.push(A2);
				}
			}
		}
		else
			if (s.top().flag == 0)
			{
				Ack tmp = s.top(), tmp2;
				s.pop();
				if (!s.isEmpty() && s.top().vn == 0)
				{
					tmp2 = s.top();
					s.pop();
					tmp2.value = tmp.value;
					tmp2.flag = 0;
					s.push(tmp2);
				}
				else
					if (!s.isEmpty())
					{
						tmp2 = s.top();
						s.pop();
						tmp2.vm = tmp2.vm - 1;
						tmp2.vn = tmp.value;
						tmp2.flag = 1;
						s.push(tmp2);
					}
				if (s.isEmpty())
					cout << tmp.value;
			}
	}
	return 0;
}

/*
int Ackerman(int m,int n)
{
    if(m == 0)
        return n+1;
    if(m != 0 && n == 0)
        return Ackerman(m - 1,1);
    if(m != 0 && n != 0)
        return Ackerman(m-1,Ackerman(m,n-1));
}
*/
