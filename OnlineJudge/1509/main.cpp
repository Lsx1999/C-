#include <cstdio>
#include <iostream>
using namespace std;

int a, b, c, y1, y2, y;

bool judge(int y) //返回真值则为闰年
{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) return true;
	return false;
}

int d[13] = { 0,31,0,31,30,31,30,31,31,30,31,30,31 };//0下标不用，第一下标到第十二下标表示每个月的天数，其中第二个月的天数要看年份决定

int main()
{
	while (cin >> a >> b >> c >> y1 >> y2)
	{
		c--;
		int sum = 1;  //因为1850年1月1日是周二

		//从1850年到最后一个不需要输出的年份，过了多少天
		for (int y = 1850; y < y1; y++)
		{
			if (judge(y)) sum += 366;
			else sum += 365;

			sum = sum % 7; //这些年1月1号是周几
		}

		for (int y = y1; y <= y2; y++)
		{

			if (judge(y)) d[2] = 29;
			else d[2] = 28;

			for (int i = 1; i <= 12; i++)
			{
				if (i == a)
				{
					int tmp = 0;
					if (sum > c)
						tmp = 7 - sum + c + 1 + (b - 1) * 7;
					else
						tmp = c - sum + 1 + (b - 1) * 7;
					if (tmp > d[i])
						puts("none");
					else
						printf("%d/%02d/%02d\n", y, a, tmp);
				}

				sum = (sum + d[i]) % 7;
			}
		}
	}
	return 0;
}
