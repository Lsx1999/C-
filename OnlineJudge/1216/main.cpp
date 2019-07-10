#include<iostream>
#include<cstring>

using namespace std;

void swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

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
	int find(const int x)const;
	void decrease(const int x, const int y);
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

template<class Type>
int priorityQueue<Type>::find(const int x)const
{
	int i, t;
	int min = 200000000;
	for (i = 1; i <= currentSize; ++i)
	{
		if (array[i] > x && array[i] < min)
		{
			t = i;
			min = array[i];
		}
	}
	return t;
}

template<class Type>
void priorityQueue<Type>::decrease(const int x, const int y)
{
	if (x > currentSize)
		return;
	array[x] -= y;
	int hole = x;
	for (; hole > 1 && array[hole] < array[hole / 2]; hole /= 2)
	{
		swap(array[hole], array[hole / 2]);
	}
}
//**********************************************************************************************************************************************
int main()
{
	priorityQueue<int> q(200000);
	char s[10];
	int M, num1, num2, i;
	cin >> M;
	for (i = 0; i < M; ++i)
	{
		cin >> s;
		cin >> num1;
		if (s[0] == 'i')
			q.enqueue(num1);
		if (s[0] == 'f')
			cout << q.find(num1) << endl;
		if (s[0] == 'd')
		{
			cin >> num2;
			q.decrease(num1, num2);
		}
	}
	return 0;
}
