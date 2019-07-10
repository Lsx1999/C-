#include<iostream>
#include<string>
#include"hfTree.h"
#include"stack.h"
#include"stack.cpp"

using namespace std;

template<class elemType>
hfTree<elemType>::hfTree(elemType* x, int* w, int size)
{
	const int MAX_INT = 32767;
	elem = new node[2 * size];
	length = 2 * size;
	int min1, min2, index1, index2;

	for (int i = size; i < 2 * size; ++i)
	{
		elem[i].value = x[i - size];
		elem[i].weight = w[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}

	for (int i = size - 1; i > 0; --i)
	{
		min1 = min2 = MAX_INT;
		index1 = index2 = 0;
		for (int j = i + 1; j < 2 * size; ++j)
		{
			if (elem[j].parent == 0)
			{
				if (elem[j].weight < min1)
				{
					min2 = min1;
					min1 = elem[j].weight;
					index2 = index1;
					index1 = j;
				}
				else
				{
					if (elem[j].weight < min2)
					{
						min2 = elem[j].weight;
						index2 = j;
					}
				}
			}

		}
		elem[i].weight = min1 + min2;
		elem[i].left = index1;
		elem[i].right = index2;
		elem[i].parent = 0;
		elem[index1].parent = i;
		elem[index2].parent = i;
	}
}

template<class elemType>
void hfTree<elemType>:: getCode()
 {
     int size = length/2;
     linkStack<int> s;
     for(int i = size;i < 2*size;++i)
     {
         int j = i;
         while(elem[j].parent != 0)
         {
             int k = elem[j].parent;
             if(elem[k].left == j)
                s.push(0);
             if(elem[k].right == j)
                s.push(1);
             j = k;
         }
         cout<<elem[i].value<<"µÄ¹þ·òÂü±àÂëÊÇ£º";
         while(!s.isEmpty())
         {
             cout<<s.top();
             s.pop();
         }
         cout<<endl;
     }
 }

