#include <iostream>
using namespace std;

int  a[100001], b[100001], c[100001];

class outOfBound {};
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
	return parent[x] = find(parent[x]);
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


void swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void quickSort(int s, int t, int a[], int b[], int c[])
{
	if (s >= t) return;
	int i = s, j = t, mid = a[(s + t) >> 1];
	while (i <= j)
	{
		while (a[i] < mid) ++i;
		while (a[j] > mid) --j;
		if (i <= j)
		{
			swap(a[i], a[j]); swap(b[i], b[j]); swap(c[i], c[j]);
			++i;
			--j;
		}
	}
	quickSort(s, j, a, b, c);
	quickSort(i, t, a, b, c);
}

int main()
{
	disJointSet ds(100001);
	int i, n, m, u, v, result = 0, current_edge = 0;
	cin >> n >> m;
	for (i = 1; i <= m; ++i)
	{
		cin >> a[i] >> b[i] >> c[i];
	}
	quickSort(1, m, c, a, b);
	i = 1;
	while (current_edge < n - 1)
	{
		u = ds.find(a[i]);
		v = ds.find(b[i]);
		if (u == v) ++i;
		else {
			ds.Union(u, v);
			result += c[i];
			++i;
			++current_edge;
		}
	}
	cout << result << endl;
}
