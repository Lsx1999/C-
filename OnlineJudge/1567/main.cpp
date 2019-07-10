#include <iostream>

using namespace std;

int main()
{
    void print(char sy,int dia);
   char s;
   int diagonal;
   cin>>s>>diagonal;
   print(s,diagonal);
   return 0;
}

void print(char sy,int dia)
{
    int i,j,k,mid;
    mid = (dia + 1)/2;
    for(i = 1;i <= mid;++i)
    {
        for(j = 0;j < mid - i;++j)
            cout<<' ';
        for(k = 0;k < 2*i - 1;++k)
            cout<<sy;
        cout<<endl;
    }
    for(i = mid + 1;i <= dia;++i)
    {
        for(j = 0;j < i - mid;++j)
            cout<<' ';
        for(k = 0;k < 4*mid - 2*i - 1;++k)
            cout<<sy;
        cout<<endl;
    }
}
