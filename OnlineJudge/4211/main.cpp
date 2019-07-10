#include <iostream>
#include<cstring>

const int MAX = 500000;
char namelist[500000][31];
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


struct researcher
{
	int H_index;
	char name[31];
	int num;
};

int main()
{
	linkStack<researcher> s;
	int n;
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		researcher tmp;
		tmp.num = i;
		ios::sync_with_stdio(false);
		cin >> tmp.H_index;
		ios::sync_with_stdio(false);
		cin.get();
		ios::sync_with_stdio(false);
		cin.getline(tmp.name, 31);


		while (!s.isEmpty())
		{
			if (tmp.H_index > s.top().H_index)
			{
				int site = s.top().num;
				strcpy(namelist[site], tmp.name);
				s.pop();
			}
			else
			{
				s.push(tmp); break;
			}
		}
		if (s.isEmpty())
			s.push(tmp);
	}




	while (!s.isEmpty())
	{
		strcpy(namelist[s.top().num], "minus one");
		s.pop();
	}
	for (int i = 0; i < n; ++i)
	{
		ios::sync_with_stdio(false);
		if (strcmp(namelist[i], "minus one") == 0)
		{
			ios::sync_with_stdio(false);
			cout << -1 << '\n';
		}
		else
		{
			ios::sync_with_stdio(false);
			cout << namelist[i] << '\n';
		}
	}

	return 0;
}
