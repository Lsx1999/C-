#include"sort.h"
#include<iostream>
template<class KEY,class OTHER>
void insertSort(SET<KEY,OTHER> arr[],int length)
{
    int i,j;
    SET<KEY,OTHER> tmp;
    for(i = 1;i < length;++i) //最开始认为下标为0的元素是有序的，故从下标为1开始插入
    {
        tmp = arr[i];
        for(j = i - 1;j >= 0 && arr[j].key > tmp.key;--j)//插入的时候是与待插入元素前面的已经有序的数组元素进行比较
        {
            arr[j+1] = arr[j];
        }
        arr[j+1] = tmp;
    }
}

template<class KEY,class OTHER>
void shellSort(SET<KEY,OTHER> arr[],int length)
{
    int i,j,gap;
    SET<KEY,OTHER> tmp;

    for(gap = length/2;gap > 0;gap /= 2)
    {
        for(i = gap;i < length;++i)
        {
            tmp = arr[i];
            for(j = i - gap;j >= 0 && arr[j].key > tmp.key;j -= gap)
            {
                arr[j+gap] = arr[j];
            }
            arr[j+gap] = tmp;
        }
    }
}

template<class KEY,class OTHER>
void selectSort(SET<KEY,OTHER> arr[],int length)
{
    int min,i,j;
    SET<KEY,OTHER> tmp;
    for(i = 0;i < length;++i)
    {
        min = i;
        for(j = i;j < length;++j)
        {
            if(arr[j].key < arr[min].key)
                min = j;
        }
        tmp = arr[i];arr[i] = arr[min];arr[min] = tmp;
    }
}


template<class KEY,class OTHER>
void bubbleSort(SET<KEY,OTHER> arr[],int length)
{
    int i,j;
    SET<KEY,OTHER> tmp;
    bool flag;
    for(i = 1;i < length;++i)
    {
        flag = false;
        for(j = 0;j < length - i;++j)
        {
            if(arr[j].key > arr[j+1].key)
            {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                flag = true;
            }
        }
        if(!flag)break;
    }
}

template<class KEY,class OTHER>
void buildHeap(SET<KEY,OTHER> arr[],int length,int i)//建堆函数，前两个参数给出数组的信息，第三个参数表示的是需要调整的位置（下标）
{
    SET<KEY,OTHER> tmp;
    int largest = i;    //largest记录i和它的两个孩子中有key最大值的元素的下标
    int l = 2 * i + 1;  //计算i左孩子的下标
    int r = 2 * i + 2;  //计算i右孩子的下标

    if(l < length && arr[l].key > arr[largest].key)//如果左孩子存在且key值比i大
        largest = l;
    if(r < length && arr[r].key > arr[largest].key)//如果右孩子存在且key值比当前最大值大
        largest = r;                               //两轮下来，largest已经是最大key值的下标了
    if(largest != i)//如果i就是最大值，说明不用再向下调整了，否则交换位置，继续调整
   {
     tmp = arr[i];arr[i] = arr[largest];arr[largest] = tmp;
     buildHeap(arr,length,largest);
   }
}

template<class KEY,class OTHER>
void heapSort(SET<KEY,OTHER> arr[],int length)
{
    SET<KEY,OTHER> tmp;
    for(int i = length/2 -1;i >= 0;--i)//建堆从下标最大的非叶子节点开始
    {
        buildHeap(arr,length,i);
    }

    for(int i = length - 1;i > 0;--i)
    {
        tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        buildHeap(arr,i,0);
    }
}

template<class KEY,class OTHER>
int divide(SET<KEY,OTHER> arr[],int low,int high)
{
    SET<KEY,OTHER> tmp = arr[low];
    do
    {
        while(low < high && arr[high].key >= tmp.key)
            --high;
        if(low < high)
        {arr[low] = arr[high];low++;}
        while(low < high && arr[low].key <= tmp.key)
            ++low;
        if(low < high)
        {arr[high] = arr[low];--high;}
    }while(low != high);
    arr[low] = tmp;
    return low;
}
template<class KEY,class OTHER>
void quickSort(SET<KEY,OTHER> arr[],int low,int high)
{
    if(low >= high)
        return;
    int mid = divide(arr,low,high);
    quickSort(arr,low,mid-1);
    quickSort(arr,mid+1,high);
}

template<class KEY,class OTHER>
void quickSort(SET<KEY,OTHER> arr[],int length)
{
    quickSort(arr,0,length-1);
}

template<class KEY,class OTHER>
void merge(SET<KEY,OTHER> arr[],int l,int m,int r)
{
    SET<KEY,OTHER>* tmp = new SET<KEY,OTHER>[r - l + 1];
    int i = l,j = m,k = 0;
    while(i < m && j <= r)
    {
        if(arr[i].key < arr[j].key)
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }
    while(i < m)
    {
        tmp[k++] = arr[i++];
    }
    while(j <= r)
    {
        tmp[k++] = arr[j++];
    }
    for(i = 0,k = l;k <= r;)
        arr[k++] = tmp[i++];
    delete tmp;
}

template<class KEY,class OTHER>
void mergeSort(SET<KEY,OTHER> arr[],int l,int r)
{
    if(l == r)
        return;
    int mid = (l + r)/2;
    mergeSort(arr,l,mid);
    mergeSort(arr,mid+1,r);
    merge(arr,l,mid + 1,r);
}

template<class KEY,class OTHER>
void mergeSort(SET<KEY,OTHER> arr[],int length)
{
    mergeSort(arr,0,length - 1);
}


template<class OTHER>
struct node
{
    SET<int,OTHER> data;
    node* next;

    node():next(NULL){}
    node(SET<int,OTHER> d):data(d),next(NULL){}
};

template<class OTHER>
void bucketSort(node<OTHER>*& p)
{
    node<OTHER>* bucket[10],*last[10],*tail;
    int i,j,k,base = 1,max = 0,len = 0;

    for(tail = p;tail != NULL;tail = tail->next)
    {
        if(tail->data.key > max)
            max = tail->data.key;
    }
    if(max == 0)
        len = 0;
    else
    {
        while(max > 0)
        {
            ++len;
            max /= 10;
        }
    }

    for(i = 1;i <= len;++i)
    {
        for(j = 0;j <= 9;++j)
        {
            bucket[j] = last[j] = NULL;
        }
        while(p)
        {
            k = p->data.key / base%10;
            if(bucket[k] == NULL)
                bucket[k] = last[k] = p;
            else
                last[k] = last[k]->next = p;
            p = p->next;
        }
        p = NULL;
        for(j = 0;j <= 9;++j)
        {
            if(bucket[j] == NULL)
                continue;
            if(p == NULL)
                p = bucket[j];
            else
                tail->next = bucket[j];
            tail = last[j];
        }
        tail->next = NULL;
        base *= 10;
    }
}
