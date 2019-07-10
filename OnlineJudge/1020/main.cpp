#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstdio>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d=", n);
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			int tmp = 0;
			while (n % i == 0) {
				n /= i;
				tmp++;
			}
			printf("%d(%d)", i, tmp);
		}
	}
	if (n != 1) printf("%d(1)", n);
	printf("\n");
	return 0;
}
