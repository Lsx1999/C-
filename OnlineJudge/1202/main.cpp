#include <iostream>
#include<cstring>
using namespace std;

 struct node
    {
        int data;
        node* next;

        node(const int x,node* n = NULL):data(x),next(n){}
        node():next(NULL){}
        ~node(){}
    };

class bigint
{
    friend bigint operator+(const bigint& op1,const bigint& op2);
private:
    node* head;
    int currentLength;
public:
    bigint(const char *s = "");
    ~bigint();
    void display();
    void insert(const int x);
    void clear();
    bigint& operator=(const bigint& other);
};

bigint:: bigint(const char* s)
{
    head = new node();
    currentLength = 0;
    while(*s)
    {
        head->next = new node(*s-'0',head->next);
        ++s;
        ++currentLength;
    }
}

void bigint:: clear()
{
    node* p = head;
    node* q;
    while(p)
    {
        q = p;
        p = p->next;
        delete q;
    }
    currentLength = 0;
}
bigint:: ~bigint()
{
    node* p = head;
    node* q;
    while(p)
    {
        q = p;
        p = p->next;
        delete q;
    }
}

void bigint:: display()
{
    node* p = head->next;
    while(p)
    {
        cout<<p->data;
        p = p->next;
    }
}

void bigint:: insert(const int x)
{
    head->next = new node(x,head->next);
}

bigint& bigint:: operator=(const bigint& other)
{
    if(this == &other)
        return *this;
    this->clear();
    head = new node();
    node* p,*tmp,*q;
    tmp = other.head->next;
    p = head;
    while(tmp)
    {
        int x = tmp->data;
        q = new node(x);
        p->next = q;
        ++currentLength;
        p = q;
        tmp = tmp->next;
    }
 return *this;
}
bigint operator+(const bigint& op1,const bigint& op2)
{
    int len1 = op1.currentLength;
    int len2 = op2.currentLength;
    int minLen = (len1 > len2)?len2:len1;
    int carry = 0,result,x,i;
    bigint op3;
    node *p1 = op1.head->next,*p2 = op2.head->next;
    for(i = 0;i < minLen;++i)
    {
        result = p1->data + p2->data + carry;
        x = result % 10;
        op3.insert(x);
        carry = result / 10;
        p1 = p1->next;
        p2 = p2->next;
    }
    while(i < len1 && p1)
    {
        result = p1->data + carry;
        x = result % 10;
        op3.insert(x);
        carry = result / 10;
        p1 = p1->next;
    }
    while(i < len2 && p2)
    {
        result = p2->data + carry;
        x = result % 10;
        op3.insert(x);
        carry = result / 10;
        p2 = p2->next;
    }
    if(carry != 0)
    {
        x = carry;
        op3.insert(x);
    }
    return op3;
}

int main()
{
    char s1[1000001],s2[1000001];
    cin.getline(s1,1000001);
    cin.getline(s2,1000001);
    bigint op1(s1),op2(s2),op3;
    op3 = (op2+op1);
    op3.display();


    return 0;
}
