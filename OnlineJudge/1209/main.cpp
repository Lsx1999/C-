#include <iostream>

using namespace std;

int main()
{
    int *a,n,i,tmp,cnt = 0;

    cin>>n;
    a = new int[n];
    for(i = 0;i < n;++i)
        cin>>a[i];

    for(i = 0;i < n;++i)
    {
        tmp = a[i];
        while(tmp != 0)
        {
            if(tmp % 2 == 1)
            {
                cnt++;
                tmp /= 2;
            }
            else
                tmp /= 2;
        }
    }
    cout<<cnt;
    return 0;
}
