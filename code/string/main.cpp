#include <iostream>
#include"String.h"
#include<cstring>
using namespace std;

char s[100][2001];
int line = 0;
int main()
{
	void list(int, int);
	void ins(int, int, const char*);
	void del(int, int, int);
	void quit();
	char content[2001], str[101];
	string order;
	int n1, n2, i, j, num;
	cin.getline(content, 2002);
	while (strcmp(content, "******") != 0)
	{
		strcpy(s[line], content);
		line++;
		cin.getline(content, 2002);
	}
	cin>>order;
	while (order != "quit")
	{
		if (order == "list")
		{
			cin >> n1 >> n2;
			list(n1, n2);
		}
		if (order == "ins")
		{
			cin >> i >> j;
			cin.get();
			cin.getline(str, 101);
			ins(i, j, str);
		}
		if (order == "del")
		{
			cin >> i >> j >> num;
			del(i, j, num);
		}
		cin>>order;
	}
	if (order == "quit")
	{
		quit();
	}

	return 0;
}

void list(int n1, int n2)
{
	if (line == 0)
	{
		cout << "Error!" << endl;
		return;
	}
	if (n1 < 0 || n2 < n1 || n1 >line || n2 > line)
	{
		cout << "Error!" << endl;
		return;
	}
	for (int i = n1 - 1; i < n2 ; ++i)
	{
		cout << s[i] << endl;
	}
}

void ins(int i, int j, const char* str)
{
	if (line == 0 && i == 0 && j == 0)
	{
		cout << "Error!" << endl;
		return;
		//strcpy(s[line], str);
		//line++; return;
	}
	if ((line == 0 && i > 0) || (line == 0 && j > 0))
	{
		cout << "Error!" << endl;
		return;
	}
	if (i < 0 || i > line)
	{
		cout << "Error!" << endl;
		return;
	}
	if (j < 0 || j > strlen(s[i - 1]) + 1)
	{
		cout << "Error!" << endl;
		return;
	}
	if (strlen(str) > 100)
	{
		cout << "Error!" << endl;
		return;
	}
	char tmp[2001];
	std::size_t k;
	for ( k = j - 1; k < strlen(s[i - 1]); ++k)         //插入点后面的字符拷贝到tmp中
	{
		tmp[k - j + 1] = s[i - 1][k];
	}
	tmp[k - j + 1] = '\0';
	for ( k = j - 1; k < j - 1 + strlen(str); ++k)     //
	{
		s[i - 1][k] = str[k - j + 1];
	}
	for ( k = j - 1 + strlen(str); k < j - 1 + strlen(str) + strlen(tmp); ++k)
	{
		s[i - 1][k] = tmp[k - j + 1 - strlen(str)];
	}
	s[i - 1][k] = '\0';
}

void del(int i, int j, int num)
{
	if (line == 0)
	{
		cout << "Error!" << endl;
		return;
	}
	if (i < 0 || i > line)
	{
		cout << "Error!" << endl;
		return;
	}
	if (j < 0 || j + num > strlen(s[i - 1]))
	{
		cout << "Error!" << endl;
		return;
	}
	int k;
	for (k = j + num - 1; s[i - 1][k] != '\0'; ++k)
	{
		s[i - 1][k - num] = s[i - 1][k];
	}
	s[i - 1][k - num] = '\0';
}

void quit()
{
	for (int i = 0; i < line; ++i)
	{
		cout << s[i] << endl;
	}
}
