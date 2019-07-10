#include <iostream>
#include<stdio.h>
using namespace std;

int a[300000];
int main()
{
    int n,cnt = 0;
    scanf("%d",&n);
    for(int i = 0;i < n;++i)
    {
        scanf("%d",&a[i]);
    }

    for(int i = 0;i < n;++i)
    {
        for(int j = i+1; j < n;++j)
        {
            if(a[i] > a[j])
                cnt++;
        }
    }
    printf("%d",cnt);
    return 0;
}
