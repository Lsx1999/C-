#include <iostream>

using namespace std;

int main()
{
	int budget[12], put = 0, rest = 0;
	for (int i = 0; i < 12; ++i)
		cin >> budget[i];
	for (int i = 0; i < 12; ++i)
	{
		rest = rest + 300 - budget[i];
		if (rest < 0)
		{
			cout << -(i + 1);
			return 0;
		}
		else
		{
			put += rest / 100;
			rest -= 100 * (rest / 100);
		}
	}
	cout << (put * 100) * 1.2 + rest;
	return 0;
}
