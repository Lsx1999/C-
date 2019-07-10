#include"sort.h"
#include<iostream>
template<class KEY,class OTHER>
void insertSort(SET<KEY,OTHER> arr[],int length)
{
    int i,j;
    SET<KEY,OTHER> tmp;
    for(i = 1;i < length;++i) //�ʼ��Ϊ�±�Ϊ0��Ԫ��������ģ��ʴ��±�Ϊ1��ʼ����
    {
        tmp = arr[i];
        for(j = i - 1;j >= 0 && arr[j].key > tmp.key;--j)//�����ʱ�����������Ԫ��ǰ����Ѿ����������Ԫ�ؽ��бȽ�
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
void buildHeap(SET<KEY,OTHER> arr[],int length,int i)//���Ѻ�����ǰ�������������������Ϣ��������������ʾ������Ҫ������λ�ã��±꣩
{
    SET<KEY,OTHER> tmp;
    int largest = i;    //largest��¼i������������������key���ֵ��Ԫ�ص��±�
    int l = 2 * i + 1;  //����i���ӵ��±�
    int r = 2 * i + 2;  //����i�Һ��ӵ��±�

    if(l < length && arr[l].key > arr[largest].key)//������Ӵ�����keyֵ��i��
        largest = l;
    if(r < length && arr[r].key > arr[largest].key)//����Һ��Ӵ�����keyֵ�ȵ�ǰ���ֵ��
        largest = r;                               //����������largest�Ѿ������keyֵ���±���
    if(largest != i)//���i�������ֵ��˵�����������µ����ˣ����򽻻�λ�ã���������
   {
     tmp = arr[i];arr[i] = arr[largest];arr[largest] = tmp;
     buildHeap(arr,length,largest);
   }
}

template<class KEY,class OTHER>
void heapSort(SET<KEY,OTHER> arr[],int length)
{
    SET<KEY,OTHER> tmp;
    for(int i = length/2 -1;i >= 0;--i)//���Ѵ��±����ķ�Ҷ�ӽڵ㿪ʼ
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
