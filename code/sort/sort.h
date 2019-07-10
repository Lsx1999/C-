#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
template<class KEY,class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY,class OTHER>
void insertSort(SET<KEY,OTHER> arr[],int length);

template<class KEY,class OTHER>
void shellSort(SET<KEY,OTHER> arr[],int length);

template<class KEY,class OTHER>
void selectSort(SET<KEY,OTHER> arr[],int length);

template<class KEY,class OTHER>
void heapSort(SET<KEY,OTHER> arr[],int length);

template<class KEY,class OTHER>
void bubbleSort(SET<KEY,OTHER> arr[],int length);

template<class KEY,class OTHER>
void quickSort(SET<KEY,OTHER> arr[],int length);

template<class KEY,class OTHER>
void mergeSort(SET<KEY,OTHER> arr[],int length);


#endif // SORT_H_INCLUDED
