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
    cin.get(ctemp);	//  �� Enter ������
	cout << "input the elements:\n" << endl;

	// ���ַ�������뵽��chlist�У������β��뵽��β��
	for ( i=0; i<=n-1; i++)
		{ cin.get ( ctemp);  chlist.insert( i, ctemp); }
	ctemp = chlist.visit(0); //����׽��.
	chlist.remove(0);
	chlist.insert(chlist.length( )/2, ctemp);
	 // ��ɾ�����׽����뵽�м䡣

	cout << "output the elements:\n"<< endl;
     	for ( i=0; i<chlist.length( ); i++)
		cout.put(chlist.visit(i));
		// ��ȡ��i������ֵ�������
     cout << '\n';

    return 0;
}
