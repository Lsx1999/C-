#include<iostream>
using namespace std;

class openHashTable
{
private:
	struct node
	{
		int data;
		node* next;

		node(const int& x, node* n = NULL) :data(x), next(n) {}
		node() :next(NULL) {}
	};
	node** array;
	int size;
	int (*key)(const int& x);
	static int defaultKey(const int& x) { return x; }
public:
	openHashTable(int length = 20, int (*f)(const int& x) = defaultKey);
	~openHashTable();
	int find(const int& x)const
	{
		int pos;
		int cnt = 0;
		pos = key(x) % size;

		if (!array[pos])
			return 0;
		node* p = array[pos];
		while (p)
		{
			if (p->data == x)
				cnt++;

			p = p->next;
		}
			return cnt;
	}
	void insert(const int& x);
	void remove(const int& x);
};


openHashTable::openHashTable(int length, int (*f)(const int& x))
{
	size = length;
	array = new node * [size];
	key = f;
	for (int i = 0; i < size; ++i)
	{
		array[i] = NULL;
	}
}


openHashTable:: ~openHashTable()
{
	node* p, * q;
	for (int i = 0; i < size; ++i)
	{
		p = array[i];
		while (p)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}
	delete[] array;
}


void openHashTable::insert(const int& x)
{
	int pos;
	pos = key(x) % size;
	array[pos] = new node(x, array[pos]);
}


void openHashTable::remove(const int& x)
{
	int pos;
	node* p = NULL, * q = NULL;
	pos = key(x) % size;
	p = array[pos];
	if (!p)
		return;
	if (array[pos]->data == x)
	{
		array[pos] = p->next;
		delete p; return;
	}
	while (p && p->data != x)
	{
		q = p;
		p = q->next;
	}
	if (!p)
		return;
	else
		q->next = p->next;
	delete p;
}

int main()
{
	int n,tmp1,tmp2,cnt = 0;
	int* a, * b, * c, * d;
	cin >> n;
	openHashTable Hash1(n * n), Hash2(n * n);
	a = new int[n];
	b = new int[n];
	c= new int[n];
	d = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			tmp1 = a[i] + b[j];
			if (tmp1 >= 0)
				Hash1.insert(tmp1);
			else
				Hash2.insert(-tmp1);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			tmp2 = c[i] + d[j];
			if (tmp2 <= 0)
			{
				cnt += Hash1.find(-tmp2);
			}
			else
				cnt += Hash2.find(tmp2);
		}
	}
	cout << cnt;
	return 0;
}
