#include <stdio.h>
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
int a[1000000];
int main()
{
    int n,i;
    scanf("%d",&n);
    for(i = 0;i < n;++i)
    {
        scanf("%d",&a[i]);
    }
    quickSort(a,n);
    printf("%d",a[0]);
    for(int i = 1;i < n;++i)
        printf(" %d",a[i]);
    return 0;
}
