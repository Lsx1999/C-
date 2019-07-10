#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include<iostream>
using namespace std;

class outOfBound{};
class illegal{};

template<class elemType>
class list
{
public:
    virtual void insert(int i,const elemType& x) = 0;
    virtual void remove(int i) = 0;
    virtual int search(const elemType& x)const = 0;
    virtual elemType visit(int i)const = 0;
    virtual void traverse()const = 0;
    virtual void clear() = 0;
    virtual int length()const = 0;
    virtual ~list(){}
};

template<class elemType>
class seqList: public list<elemType>
{
private:
    elemType* elem;
    int maxSize,currentLength;
    void doubleSpace();
public:
    seqList(int init = 10);
    ~seqList(){delete[] elem;}
    void insert(int i,const elemType& x);
    void remove(int i);
    void clear();
    int length()const;
    elemType visit(int i)const;
    int search(const elemType& x)const;
    void traverse()const;
};

template<class elemType>
class linkList: public list<elemType>
{
private:
    struct node
    {
        elemType data;
        node* next;

        node(const elemType& x,node* n = NULL):data(x),next(n){}
        node():next(NULL){}
        ~node(){}
    };
    node* head;
public:
    linkList();
    ~linkList(){clear();delete head;}
    void clear();
    void insert(int i,const elemType& x);
    void remove(int i);
    int length()const;
    int search(const elemType& x)const;
    elemType visit(int i)const;
    void traverse()const;
};
#endif // LIST_H_INCLUDED
