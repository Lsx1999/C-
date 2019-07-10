#include <iostream>

using namespace std;

int main()
{
    int *arr,*dif,i,n,ave,step = 0,sum = 0,sum1 = 0;
    cin>>n;
    arr = new int[n];
    dif = new int[n];
    for(i = 0;i < n;++i)
    {
        cin>>arr[i];
        sum += arr[i];
    }
    ave = sum / n;

    for(i = 0;i < n;++i)
    {
        dif[i] = arr[i] - ave;
    }

    for(i = 0;i < n;++i)
    {
        sum1 += dif[i];
        if(sum1 != 0)
            step++;
    }
    cout<<step;
    return 0;
}
