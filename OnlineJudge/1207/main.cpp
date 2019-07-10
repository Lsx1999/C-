#include <iostream>
#include<iomanip>
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

int main()
{
	void ferry(double& t1, double& t2);
	double waitTime1, waitTime2;
	ferry(waitTime1, waitTime2);
	cout << fixed << setprecision(3) << waitTime1 << ' ' << waitTime2;
	return 0;
}

void ferry(double& t1, double& t2)
{
	linkQueue<int> Qbus, Qvan;
	int i, n, cnt, q, p, time, busNum = 0, vanNum = 0;
	double busWaitTime = 0, vanWaitTime = 0;
	cin >> n;
	for (i = 0; i < n; ++i)
	{
		cin >> p >> q;
		if (p == 0)
		{
			Qbus.enqueue(q);
			busNum++;
		}
		if (p == 1)
		{
			Qvan.enqueue(q);
			vanNum++;
		}
	}
	time = 0;
	for (i = 0; i < n; ++i)
	{
		for (cnt = 0; cnt < 8 && !Qbus.isEmpty() && Qbus.getHead() <= time; ++cnt)
		{
			int tmp = Qbus.getHead();
			Qbus.dequeue();
			busWaitTime += time - tmp;
		}
		for (; cnt < 10 && !Qvan.isEmpty() && Qvan.getHead() <= time; ++cnt)
		{
			int tmp = Qvan.getHead();
			Qvan.dequeue();
			vanWaitTime += time - tmp;
		}
		for (; cnt < 10 && !Qbus.isEmpty() && Qbus.getHead() <= time; ++cnt)
		{
			int tmp = Qbus.getHead();
			Qbus.dequeue();
			busWaitTime += time - tmp;
		}
		time += 10;
	}
	t1 = busWaitTime / busNum;
	t2 = vanWaitTime / vanNum;

}

