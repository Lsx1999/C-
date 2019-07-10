#ifndef SKEWHEAP_H_INCLUDED
#define SKEWHEAP_H_INCLUDED
template<class Type>
class skewHeap
{
private:
    struct node
    {
        Type data;
        node *left,*right;

        node(const Type& x):data(x),left(NULL),right(NULL){}
        node():left(NULL),right(NULL){}
        ~node(){}
    };
node* root;
void clear(node* r);
public:
    skewHeap();
    ~ skewHeap();
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
    }
    else
        if(r->left && r->right)
    {
            tmp = r->left;
            r->left = r->right;
            r->right = tmp;
    }
    return r;
    }
};


#endif // SKEWHEAP_H_INCLUDED
