#include <iostream>
#include"sort.h"
#include"sort.cpp"
using namespace std;

int main()
{
    SET<int,int> a[10];
    for(int i = 0;i < 10;++i)
        {
            cin>>a[i].key;
            a[i].other = 0;
        }
    quickSort(a,10);
    for(int i = 0;i < 10;++i)
        cout<<a[i].key<<' ';
    return 0;
}
