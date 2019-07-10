#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<cmath>
#include<iostream>
using namespace std;

class outOfBound {};
class illegal {};

template<class elemType>
class stack
{
public:
	virtual void push(const elemType& x) = 0;
	virtual void pop() = 0;
	virtual elemType top()const = 0;
	virtual bool isEmpty()const = 0;
	virtual ~stack() {}
};

template<class elemType>
class seqStack : public stack<elemType>
{
private:
	elemType* elem;
	int Top, maxSize;
	void doubleSpace();
public:
	seqStack(int init = 10);
	~seqStack() { delete[] elem; }
	void push(const elemType& x);
	void pop();
	bool isEmpty()const { return Top == -1; }
	elemType top()const;
};

template<class T>
class linkStack : public stack<T>
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
template<class elemType>
seqStack<elemType> ::seqStack(int init)
{
	elem = new elemType[init];
	maxSize = init;
	Top = -1;
}

template<class elemType>
void seqStack<elemType>::push(const elemType& x)
{
	if (Top == maxSize - 1)
		doubleSpace();
	else
		elem[++Top] = x;
}

template<class elemType>
void seqStack<elemType>::pop()
{
	if (Top == -1)
		throw outOfBound();
	Top--;
}

template<class elemType>
elemType seqStack<elemType>::top()const
{
	if (Top == -1)
		throw outOfBound();
	return elem[Top];
}

template<class elemType>
void seqStack<elemType>::doubleSpace()
{
	elemType* tmp = elem;
	elem = new elemType[2 * maxSize];
	for (int i = 0; i <= Top; ++i)
	{
		elem[i] = tmp[i];
	}
	maxSize *= 2;
	delete[] tmp;
}

//****************************************************************linkStack**************************************************************************

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
//*******************************************************************************************************************************************
class disJointSet
{
private:
	int* parent;
	int size;
public:
	disJointSet(int s);
	~disJointSet() { delete[] parent; }
	int find(int x)const;
	void Union(int root1, int root2);
};

disJointSet::disJointSet(int s)
{
	size = s;
	parent = new int[s];
	for (int i = 0; i < s; ++i)
		parent[i] = -1;
}

int disJointSet::find(int x)const
{
	if (x < 0 || x > size - 1)
		throw outOfBound();
	if (parent[x] < 0)
		return x;
	int start = x;
	int tmp;
	while (!(parent[x] < 0))
		x = parent[x];
	while (start != x)
	{
		tmp = parent[start];
		parent[start] = x;
		start = tmp;
	}
	return x;
}

void disJointSet::Union(int root1, int root2)
{
	if (root1 == root2)
		return;
	if (parent[root1] > parent[root2])
	{
		parent[root2] += parent[root1];
		parent[root1] = root2;
	}
	else
	{
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
}
//************************************************************************
int main()
{
	//准备工作
	linkStack<int> s;
	bool* visited;
	int rowOfNum(int x);
	int minum(int a, int b);
	int n, Start, End, Pi, Qi, row, col, q,**directly,*path,cnt = 0;
	scanf("%d %d %d", &n, &Start, &End);
	path = new int[n * (n + 1) / 2 + 1];
	visited = new bool[n * (n + 1) / 2 + 1];
	directly = new int*[n * (n + 1) / 2 + 1];
	for (int i = 0; i < n * (n + 1) / 2 + 1; ++i)
	{
		directly[i] = new int[n * (n + 1) / 2 + 1];
	}
	for (int i = 0; i < n * (n + 1) / 2 + 1; ++i)
	{
		for (int j = 0; j < n * (n + 1) / 2 + 1; ++j)
			directly[i][j] = 0;
	}
	disJointSet d(n * (n + 1) / 2 + 1);

	for (int i = 0; i < n * (n + 1) / 2 + 1; ++i)
		visited[i] = false;
	//生成迷宫
	while (d.find(Start) != d.find(End))
	{
		while (true)
		{
			scanf("%d %d", &Pi, &Qi);
			row = rowOfNum(Pi);          //计算所给格子的行数
			col = Pi - row * (row - 1) / 2;  //计算列数
			if (Qi == 0)    //左上
			{
				if (col == 1)  //第一列没有左上
					continue;
				else
					q = (row - 1) * (row - 2) / 2 + col - 1;  //计算要打通到的格子序号
				d.Union(d.find(Pi), d.find(q));//砸墙
				directly[Pi][q] = 1;
				directly[q][Pi] = 1;
					break;
			}
			if (Qi == 1)   //右上
			{
				if (col == row) //最后一列没有右上
					continue;
				else
					q = (row - 1) * (row - 2) / 2 + col;
				d.Union(d.find(Pi), d.find(q));//砸墙
				directly[Pi][q] = 1;
				directly[q][Pi] = 1;
					break;
			}
			if (Qi == 2)    //左下
			{
				if (row == n)  //最后一行没有下方
					continue;
				else
					q = row * (row + 1) / 2 + col;
				d.Union(d.find(Pi), d.find(q));//砸墙
				directly[Pi][q] = 1;
				directly[q][Pi] = 1;
					break;

			}
			if (Qi == 3) //右下
			{
				if (row == n)//最后一行没有下方
					continue;
				else
					q = row * (row + 1) / 2 + col + 1;
				d.Union(d.find(Pi), d.find(q));//砸墙
				directly[Pi][q] = 1;
				directly[q][Pi] = 1;
					break;
			}
		}

	}
	//输出路径
	int r = d.find(Start);  //找出入口所在的并查集
	s.push(Start);
	cnt++;
	path[cnt] = s.top();
	int tmp1 = Start;       //tmp1是当前走到的格子序号
	visited[Start] = true;  //入口已经访问
	int q1, q2, q3, q4;     //当前格子四个方向的格子的序号
	int rs = rowOfNum(tmp1); //入口的行数
	while (tmp1 != End)   //没走到出口
	{
		int min, min1, min2, min3, min4; //用于输出字典序最小的路径
		min = min1 = min2 = min3 = min4 = n * (n + 1)/2 + 1;
		int rs = rowOfNum(tmp1);//当前格子的行数
		int cs = tmp1 - rs * (rs - 1) / 2;//当前格子的列数
		if (cs != 1)//不是第一列
		{
			q1 = (rs - 1) * (rs - 2) / 2 + cs - 1;//左上格子序号
			if (q1 == End)
			{
				for (int i = 1; i <= cnt; ++i)
					cout << path[i] << ' ';
				printf("%d ", q1); return 0;
			}
			if (!visited[q1] && d.find(q1) == r && directly[tmp1][q1]== 1)
			{
				min1 = min1 > q1 ? q1 : min1;
			}
		}
		if (cs < rs)//不是最后一列
		{
			q2 = (rs - 1) * (rs - 2) / 2 + cs;//右上格子序号
			if (q2 == End)
			{
				for (int i = 1; i <= cnt; ++i)
					cout << path[i] << ' ';
				printf("%d ", q2); return 0;
			}
			if (!visited[q2] && d.find(q2) == r && directly[tmp1][q2] == 1)
			{
				min2 = min2 > q2 ? q2 : min2;
			}
		}
		if (rs < n)//不是最后一行
		{
			q3 = rs * (rs + 1) / 2 + cs;//左下格子序号
			if (q3 == End)
			{
				for (int i = 1; i <= cnt; ++i)
					cout << path[i] << ' ';
				printf("%d ", q3); return 0;
			}
			if ( !visited[q3] && d.find(q3) == r && directly[tmp1][q3] == 1)
			{
				min3 = min3 > q3 ? q3 : min3;
			}
		}
		if (rs < n)//不是最后一行
		{
			q4 = rs * (rs + 1) / 2 + cs + 1;//右下格子序号
			if (q4 == End)
			{
				for (int i = 1; i <= cnt; ++i)
					cout << path[i] << ' ';
				printf("%d ", q4); return 0;
			}
			if (!visited[q4] && d.find(q4) == r && directly[tmp1][q4] == 1)
			{
				min4 = min4 > q4 ? q4 : min4;
			}
		}
		min = minum(minum(min1, min2), minum(min3, min4));
		if (min == n * (n + 1) / 2 + 1)
		{
			int top;
			top = s.top();
			s.pop();
			cnt--;
			directly[s.top()][top] = 0;
			directly[top][s.top()] = 0;
			if (top > s.top())
				rs -= 1;
			else
				rs += 1;
			tmp1 = s.top();
		}
		else
		{
			if (min == min1 || min == min2)
				rs -= 1;
			else
				rs += 1;
			s.push(min);
			cnt++;
			path[cnt] = s.top();
			visited[min] = true;
			tmp1 = min;
		}
	}

	return 0;
}

int rowOfNum(int x)
{
	for (int i = sqrt(x);; ++i)
	{
		if (i * (i - 1) / 2 < x && x <= i * (i + 1) / 2)
			return i;
	}
}

int minum(int a, int b)
{
	return (a > b) ? b : a;
}
