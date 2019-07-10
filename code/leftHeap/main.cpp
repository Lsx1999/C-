#include <iostream>
#include"leftHeap.h"
#include"leftHeap.cpp"

using namespace std;

int main()
{
    leftHeap<int> q;
    char s[10];
    int M,num1,i;
    cin>>M;
    for(i = 0;i < M;++i)
    {
        cin>>s;
        if (s[0] == 'i')
		{
			cin >> num1;
			q.enqueue(num1);
		}
		if (s[0] == 'm')
			cout << q.getHead() << endl;
		if (s[0] == 'd')
		{
			q.dequeue();
		}
    }
    return 0;
}
