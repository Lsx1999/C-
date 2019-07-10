#ifndef HFTREE_H_INCLUDED
#define HFTREE_H_INCLUDED
#include<iostream>
#include<string>
using namespace std;

template<class elemType>
class hfTree
{
private:
    struct node
    {
        elemType value;
        int weight;
        int parent,left,right;
    };
    node* elem;
    int length;
public:
    struct hfCode
    {
        elemType data;
        string code;
    };
    hfTree(elemType* x,int* w,int size);
    void getCode();
    ~hfTree(){delete elem;}
    void getcode(hfCode result[])
    {
        int size = length/2;
        int p,s;
        for(int i = size;i < length;++i)
        {
            result[i - size].data = elem[i].value;
            result[i - size].code = "";
            p = elem[i].parent;
            s = i;
            while(p)
            {
                if(elem[p].left == s)
                    result[i - size].code = '0' + result[i-size].code;
                else
                    result[i-size].code = '1'+ result[i-size].code;;
                s = p;
                p = elem[p].parent;
            }
        }
    }
};


#endif // HFTREE_H_INCLUDED
