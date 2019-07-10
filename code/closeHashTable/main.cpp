#include <iostream>
#include"closeHashTable.h"
#include"closeHashTable.cpp"
using namespace std;

int main()
{
    int n;
    closeHashTable<int,int> h(5,2);
    cout<<"请输入数据数"<<endl;
    cin>>n;
    for(int i = 0;i < n;++i)
    {
        SET<int,int> tmp;
        cin>>tmp.key;
        cin>>tmp.other;
        h.insert(tmp);
    }
    h.remove(17);
    h.remove(23);
    return 0;
}
