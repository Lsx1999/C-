#include<stdio.h>
using namespace std;

int divide(int arr[],int low,int high)
{
    int tmp = arr[low];
    do
    {
        while(low < high && arr[high] >= tmp)
            --high;
        if(low < high)
        {arr[low] = arr[high];low++;}
        while(low < high && arr[low] <= tmp)
            ++low;
        if(low < high)
        {arr[high] = arr[low];--high;}
    }while(low != high);
    arr[low] = tmp;
    return low;
}

void quickSort(int arr[],int low,int high)
{
    if(low >= high)
        return;
    int mid = divide(arr,low,high);
    quickSort(arr,low,mid-1);
    quickSort(arr,mid+1,high);
}

void quickSort(int arr[],int length)
{
    quickSort(arr,0,length-1);
}
int a[2000001];
int main()
{
    int n,i,cnt = 1;
    scanf("%d",&n);
    for(i = 0;i < n;++i)
    {
        scanf("%d",&a[i]);
    }
    quickSort(a,n);
    for (i = 1; i <= n - 1; ++i)
    {
        if (a[i]!=a[i-1]) ++cnt;
    }
    printf("%d",cnt);
    return 0;
}
