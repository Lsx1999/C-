#include <iostream>

using namespace std;

const int MAX = 1001;
int num[MAX][MAX]; int n;
int maxSum[MAX][MAX];

int main() {
	int i, j;
	cin >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++)
			cin >> num[i][j];
	for (int i = 1; i <= n; ++i)
		maxSum[n][i] = num[n][i];
	for (int i = n - 1; i >= 1; --i)
		for (int j = 1; j <= i; ++j)
    {
        int bigger = maxSum[i + 1][j] > maxSum[i + 1][j + 1] ? maxSum[i + 1][j]:maxSum[i + 1][j + 1];
        maxSum[i][j] = bigger + num[i][j];

    }
    cout << maxSum[1][1];
    return 0;
}
