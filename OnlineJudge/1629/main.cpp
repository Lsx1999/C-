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
	int* Max = new int[n + 1];
	for(int i = 0;i <= n;++i)
    {
        Max[i] = -1;
    }
	for (int i = 1; i <= n; ++i)
	{

		for (node* p = head[i]->next; p != NULL; p = p->next)
		{
			if (p->id == father[i])
			{
				if (Max[i] < (n - cnt[i]))
					Max[i] = (n - cnt[i]);
			}
			else
			{
				if (Max[i] < cnt[p->id])
					Max[i] = cnt[p->id];
			}
		}
	}
	int min = 10000;
	int min_index = 10000;
	for(int i = 1;i <= n;++i)
    {
        if(min > Max[i])
        {
            min = Max[i];
            min_index = i;
        }
        else
        {
            if(min == Max[i] && min_index > i)
                min_index = i;
        }
    }
    cout<<min_index<<' '<<min;
	return 0;
}

