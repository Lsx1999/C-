#include<iostream>
using namespace std;

template<class Type>
class priorityQueue
{
public:
	priorityQueue(int capacity = 100);
	priorityQueue(const Type data[], int size);
	~priorityQueue();
	void enqueue(const Type& x);
	void dequeue();
	Type getHead()const;
	bool isEmpty()const;
	void display()const
	{
		for (int i = 1; i <= currentSize; ++i)
		{
			cout << array[i] << " ";
		}
	}
	bool find(const Type& x)const
	{
		for (int i = 1; i <= currentSize; ++i)
		{
			if (x == array[i])
			{
				return true; break;
			}
		}
		return false;
	}
	void find_ith(const int& i)const
	{
		if (i > currentSize)
		{
			cout << 'N' << endl; return;
		}
		priorityQueue other(maxSize);
		for (int j = 1; j <= currentSize; ++j)
		{
			other.enqueue(array[j]);
		}
		for (int j = 1; j < i; ++j)
		{
			other.dequeue();
		}
		cout << other.getHead() << endl;
	}
private:
	Type* array;
	int currentSize;
	int maxSize;
	void buildHeap();
	void doubleSpace();
	void percolateDown(int hole);
};

template<class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
	array = new Type[capacity];
	currentSize = 0;
	maxSize = capacity;
}

template<class Type>
priorityQueue<Type>::priorityQueue(const Type data[], int size)
{
	maxSize = size + 10;
	currentSize = size;
	array = new Type[maxSize];
	for (int i = 0; i < size; ++i)
	{
		array[i + 1] = data[i];
	}
	buildHeap();
}

template<class Type>
priorityQueue<Type>:: ~priorityQueue()
{
	delete[] array;
}

template<class Type>
void priorityQueue<Type>::enqueue(const Type& x)
{
	if (currentSize == maxSize - 1)
		doubleSpace();
	int hole = ++currentSize;
	for (; hole > 1 && x < array[hole / 2]; hole /= 2)
	{
		array[hole] = array[hole / 2];
	}
	array[hole] = x;
}

template<class Type>
void priorityQueue<Type>::dequeue()
{
	array[1] = array[currentSize--];
	percolateDown(1);
}

template<class Type>
Type priorityQueue<Type>::getHead()const
{
	return array[1];
}

template<class Type>
bool priorityQueue<Type>::isEmpty()const
{
	return currentSize == 0;
}

template<class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
	int child;
	Type tmp = array[hole];
	for (; hole * 2 <= currentSize; hole = child)
	{
		child = 2 * hole;
		if (child != currentSize && array[child + 1] < array[child])
			child++;
		if (array[child] < tmp)
			array[hole] = array[child];
		else
			break;
	}
	array[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; --i)
		percolateDown(i);
}

template<class Type>
void priorityQueue<Type>::doubleSpace()
{
	Type* tmp = array;
	array = new Type[2 * maxSize];
	for (int i = 0; i < currentSize; ++i)
	{
		array[i] = tmp[i];
	}
	maxSize *= 2;
	delete[] tmp;
}


int main()
{
	priorityQueue<int> q(5000);
	int n, i, num1, num2;
	char s[30];
	cin >> n;
	for (i = 0; i < n; ++i)
	{
		cin >> s;
		cin >> num1;
		if (s[0] == 'i')
		{
			q.enqueue(num1);
		}

		if (s[0] == 'f' && s[4] != '_')
		{
			if (q.find(num1))
				cout << 'Y' << endl;
			else
				cout << 'N' << endl;
		}

		if (s[0] == 'f' && s[4] == '_')
		{
			q.find_ith(num1);
		}

		if (s[0] == 'd' && s[6] != '_')
		{
			int b[5000];
			int cnt = 0;
			while (!q.isEmpty())
			{
				if (q.getHead() != num1)
				{
					b[cnt] = q.getHead();
					q.dequeue();
					cnt++;
				}
				else
					break;
			}
			if (q.isEmpty())return -1;
			q.dequeue();
			for (int k = 0; k < cnt; ++k)
			{
				q.enqueue(b[k]);
			}
		}

		if (s[0] == 'd' && s[6] == '_' && s[7] == 'l')
		{
			while (!q.isEmpty())
			{
				if (q.getHead() < num1)
					q.dequeue();
				else
					break;
			}
		}

		if (s[0] == 'd' && s[6] == '_' && s[7] == 'g')
		{
			int b[5000];
			int cnt = 0;
			while (!q.isEmpty())
			{
				if (q.getHead() <= num1)
				{
					b[cnt] = q.getHead();
					q.dequeue();
					cnt++;
				}
				else
				q.dequeue();
			}
			for (int k = 0; k < cnt; ++k)
			{
				q.enqueue(b[k]);
			}
		}

		if (s[0] == 'd' && s[6] == '_' && s[7] == 'i')
		{
			cin >> num2;
			int b[5000];
			int cnt = 0;
			while (!q.isEmpty())
			{
				if (q.getHead() <= num1 || q.getHead() >= num2)
				{
					b[cnt] = q.getHead();
					q.dequeue();
					cnt++;
				}
				else
					q.dequeue();
			}
			for (int k = 0; k < cnt; ++k)
			{
				q.enqueue(b[k]);
			}
		}
	}
	return 0;
}
