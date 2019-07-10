#include<iostream>
using namespace std;

template<class Type>
class leftHeap
{
private:
    struct node
    {
        Type data;
        int npl;
        node *left,*right;

        node(const Type& x):data(x),npl(0),left(NULL),right(NULL){}
        node():npl(0),left(NULL),right(NULL){}
        ~node(){}
    };
node* root;
void clear(node* r);
public:
    leftHeap();
    ~leftHeap();
    void enqueue(const Type& x);
    void dequeue();
    bool isEmpty()const;
    Type getHead()const;
    node* merge(node* r1,node* r2)
    {
        node *r,*tmp;
    if(!r1 || !r2)
        return (r1)?r1:r2;
    if(r1->data < r2->data)
    {
        r = r1;
        r->right = merge(r1->right,r2);
    }
    else
    {
        r = r2;
        r->right = merge(r2->right,r1);
    }
    if(!r->left && r->right)
    {
        r->left = r->right;
        r->right = NULL;
        r->npl = 0;
    }
    else
        if(r->left && r->right)
    {
       if(r->left->npl < r->right->npl)
       {
            tmp = r->left;
            r->left = r->right;
            r->right = tmp;
       }
        r->npl = r->right->npl + 1;
    }
    return r;
    }
};

template<class Type>
leftHeap<Type>:: leftHeap()
{
    root = NULL;
}

template<class Type>
leftHeap<Type>:: ~leftHeap()
{
    clear(root);
}

template<class Type>
void leftHeap<Type>::clear(leftHeap<Type>:: node* r)
{
    if(r == NULL)
        return;
    clear(r->left);
    clear(r->right);
    delete r;
    r = NULL;
}


template<class Type>
void leftHeap<Type>:: enqueue(const Type& x)
{
    node* tmp;
    tmp = new node(x);
    root = merge(root,tmp);
}

template<class Type>
void leftHeap<Type>:: dequeue()
{
    root = merge(root->left,root->right);
}

template<class Type>
Type leftHeap<Type>:: getHead()const
{
    return root->data;
}

template<class Type>
bool leftHeap<Type>:: isEmpty()const
{
    return (root != NULL);
}

int main()
{
    leftHeap<int> q;
    char s[10];
    int M,num1,i;
    cin>>M;
    for(i = 0;i < M;++i)
    {
        cin>>s;
        if (s[0] == 'i')
		{
			cin >> num1;
			q.enqueue(num1);
		}
		if (s[0] == 'm')
			cout << q.getHead() << endl;
		if (s[0] == 'd')
		{
			q.dequeue();
		}
    }
    return 0;
}
