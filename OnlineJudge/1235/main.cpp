
#include<iostream>
using namespace std;
#define N 30001
#define M 300001
#define Q 3000001
#define MAX 99999999
int head[N] = { 0 }, dist[N], q[Q], n, m, s, t, op = 1, cl = 0,Prev[N],hop[N];
bool mark[N] = { 0 };



struct
{
	int a, b, p;
	int next;
}e[M];


void printPath(int start, int End, int prev[])
{
	if (start == End)
	{
		cout << start;
		return;
	}
	printPath(start, prev[End], prev);
	cout << " " << End;

}


bool EnQueue(int i)
{
	if (mark[i] == true)
		return false;

	cl++;
	q[cl] = i;
	mark[i] = true;

	return true;

}

void Init()
{
	for (int i = 1; i <= n; i++)
	{
		dist[i] = MAX;
		hop[i] = 0;
	}
	dist[s] = 0;
	EnQueue(s);
}

void Spfa()
{
	int from, to, value, i;
	while (op <= cl)
	{
		from = q[op];
		for (i = head[from]; i != 0; i = e[i].next)
		{
			to = e[i].b;
			value = e[i].p;
			if (dist[to] > dist[from] + value || (dist[to] == dist[from] + value && hop[to] > hop[from] + 1))
			{
				dist[to] = dist[from] + value;
				hop[to] = hop[from] + 1;
				Prev[to] = from;
				EnQueue(to);
			}
		}
		op++;
		mark[from] = false;
	}
	cout << dist[t] << endl;

}

int main()
{
	int from, to, i, value;

	cin >> n >> m >> s >> t;
	for (i = 1; i <= m; i++)
	{
		cin >> from >> to >> value;
		e[i].a = from;
		e[i].b = to;
		e[i].p = value;
		e[i].next = head[from];
		head[from] = i;
	}

	Init();
	Spfa();

	printPath(s, t, Prev);
	return 0;
}
