#include<iostream>
using namespace std;

struct node
{
	int id;
	node* next;
	node(int _id, node* _next = NULL) :id(_id), next(_next) {}
};

int n;
int* father, * cnt;
node** head;

void traverse(int x)
{
	for (node* p = head[x]->next; p != NULL; p = p->next)
	{
		if (father[p->id] == 0 && p->id != 1)
		{
			father[p->id] = x;
			traverse(p->id);
			cnt[x] += cnt[p->id];
		}
	}
	++cnt[x];
}
int main()
{
	cin >> n;
	father = new int[n + 1]{ 0 };
	cnt = new int[n + 1]{ 0 };
	head = new node * [n + 1];
	for (int i = 1; i <= n; ++i)
	{
		head[i] = new node(0);
	}
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		node* temp;
		temp = new node(v, head[u]->next);
		head[u]->next = temp;
		temp = new node(u, head[v]->next);
		head[v]->next = temp;
	}

	traverse(1);

	for (int i = 1; i <= n; ++i)
	{
		bool check = true;
		for (node* p = head[i]->next; p != NULL; p = p->next)
		{
			if (p->id == father[i])
			{
				if (cnt[i] < n / 2)
					check = false;
			}
			else
			{
				if (cnt[p->id] > n / 2)
					check = false;
			}
		}
		if (check)
			cout << i << endl;
	}
	return 0;
}
