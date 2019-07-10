#include <iostream>
#include<iomanip>
using namespace std;

int main()
{
	int n, m, k,*a,i;
	int cnt1 = 0, cnt2 = 1,out;
	cin >> n >> m >> k;
	a = new int[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = i + 1;
	}
	for (i = 1; ; ++i)
	{
		if (i > n)
			i = i % n;
		if (a[i - 1] != 0)
		{
			if (cnt2 == m)
			{
				a[i - 1] = 0;
				cnt1++;
				cnt2 = 1;
			}
			else
				cnt2++;
			if (cnt1 == k)
			{
				out = i;
				break;
			}
		}
	}
	cout << out;
}
