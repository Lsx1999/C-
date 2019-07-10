#include <iostream>
#include<cstring>
#include"hfTree.h"
#include"hfTree.cpp"

using namespace std;

int main()
{
    char c[] = {"aeistdn"};
    int w[] = {10,15,12,3,4,13,1};
    int size = 7;
    hfTree<char>:: hfCode result[7];
    hfTree<char> hf(c,w,size);
    hf.getCode();
    hf.getcode(result);
    for(int i = 0;i < 7;++i)
    {
        cout<<result[i].data<<' '<<result[i].code<<endl;
    }
    return 0;
}
