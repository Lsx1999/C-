#include <cstdio>
#include <iostream>
using namespace std;

int a, b, c, y1, y2, y;

bool judge(int y) //������ֵ��Ϊ����
{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) return true;
	return false;
}

int d[13] = { 0,31,0,31,30,31,30,31,31,30,31,30,31 };//0�±겻�ã���һ�±굽��ʮ���±��ʾÿ���µ����������еڶ����µ�����Ҫ����ݾ���

int main()
{
	while (cin >> a >> b >> c >> y1 >> y2)
	{
		c--;
		int sum = 1;  //��Ϊ1850��1��1�����ܶ�

		//��1850�굽���һ������Ҫ�������ݣ����˶�����
		for (int y = 1850; y < y1; y++)
		{
			if (judge(y)) sum += 366;
			else sum += 365;

			sum = sum % 7; //��Щ��1��1�����ܼ�
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
