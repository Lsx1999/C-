#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	bool isPrime(int n);
	int n, gap, num1, num2;
	cin >> n;
	if (isPrime(n))
	{
		cout << 0;
		return 0;
	}
	for (int i = n + 1;; ++i)
	{
		if (isPrime(i))
		{
			num1 = i;
			break;
		}
	}

	for (int j = n - 1;; --j)
	{
		if (isPrime(j))
		{
			num2 = j;
			break;
		}
	}
	gap = num1 - num2;
	cout << gap;
	return 0;
}

bool isPrime(int n)
{
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	int limit = sqrt(n) + 1;
	for (int i = 3; i <= limit; i += 2)
		if (n % i == 0) return false;
	return true;
}
