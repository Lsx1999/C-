#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
using namespace std;

void insertSort(char arr[][31], int length)
{
	int i, j;
	char* tmp = new char[31];
	for (i = 1; i < length; ++i)
	{
		strcpy(tmp, arr[i]);

		for (j = i - 1; j >= 0 && strcmp(arr[j], tmp) > 0; --j)
		{
			strcpy(arr[j + 1], arr[j]);

		}
		strcpy(arr[j + 1], tmp);

	}
}
int main()
{
	char str[31][31];
	char ch;
	int i = 1, j, cnt;

	cin >> ch;
	cin.get();
	cin.getline(str[0], 31);
	while (str[i - 1][0] != '@')
		cin.getline(str[i++], 31);
	if (str[0][0] == '@')
		return 0;
	int num = i - 1;
	for (i = 0; i < num; ++i)
	{
		j = 0;
		cnt = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == ch)
				cnt++;
			j++;
		}
		while (cnt > 0)
		{
			j = 0;
			while ( str[i][j] != '\0' && str[i][j] != ch)
				j++;
			++j;
			while (str[i][j] != '\0')
			{
				str[i][j - 1] = str[i][j];
				++j;
			}
			str[i][j - 1] = '\0';
			cnt--;
		}
	}
	insertSort(str, num);
	cout << str[num - 1];
	for (i = num - 2; i >= 0; i--)
		cout << endl << str[i];
	return 0;
}

