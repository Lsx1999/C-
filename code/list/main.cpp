#include <iostream>
#include"list.h"
#include"list.cpp"
using namespace std;

int main()
{
	linkList<char> chlist;
	char ctemp;
	int i, n;
	cout << "number of the elements:"<< endl;
    cin >> n;
    cin.get(ctemp);	//  将 Enter 抛弃。
	cout << "input the elements:\n" << endl;

	// 将字符逐个输入到表chlist中，并依次插入到表尾。
	for ( i=0; i<=n-1; i++)
		{ cin.get ( ctemp);  chlist.insert( i, ctemp); }
	ctemp = chlist.visit(0); //获得首结点.
	chlist.remove(0);
	chlist.insert(chlist.length( )/2, ctemp);
	 // 将删除的首结点插入到中间。

	cout << "output the elements:\n"<< endl;
     	for ( i=0; i<chlist.length( ); i++)
		cout.put(chlist.visit(i));
		// 读取第i个结点的值并输出。
     cout << '\n';

    return 0;
}
