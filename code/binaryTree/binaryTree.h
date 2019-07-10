#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

template<class elemType>
class bTree
    {
    public:
        virtual void clear() = 0;
        virtual bool isEmpty()const = 0;
        virtual elemType Root(elemType flag)const = 0;
        virtual elemType parent(elemType x,elemType flag)const = 0;
        virtual elemType lchild(elemType x,elemType flag)const = 0;
        virtual elemType rchild(elemType x,elemType flag)const = 0;
        virtual void delLeft(elemType x) = 0;
        virtual void delRight(elemType x) = 0;
        virtual void preOrder()const = 0;
        virtual void midOrder()const = 0;
        virtual void postOrder()const = 0;
        virtual void levelOrder()const = 0;
    };

template<class elemType>
class binaryTree: public bTree<elemType>
{
private:
    struct node
    {
        elemType data;
        node *left,*right;

        node():left(NULL),right(NULL){}
        node(const elemType x,node* l = NULL,node* r = NULL):data(x),left(l),right(r){}
        ~node(){}
    };
    node* root;
public:
    binaryTree(){root = NULL;}
    binaryTree(const elemType x){root = new node(x);}
    ~binaryTree(){clear(root);}
    void clear();
    bool isEmpty()const;
    elemType Root(elemType flag)const;
    elemType parent(elemType x,elemType flag)const{return flag;}
    elemType lchild(elemType x,elemType flag)const;
    elemType rchild(elemType x,elemType flag)const;
    void delLeft(elemType x);
    void delRight(elemType x);
    void creatTree(elemType flag);
    void preOrder()const;
    void midOrder()const;
    void postOrder()const;
    void levelOrder()const;
private:
    void clear(node* t);
    node* find(const elemType x,node * t)const
    {
        if(!t)
            return NULL;
        node* tmp = NULL;
        if(x == t->data)
            return t;
        if(tmp == find(x,t->left))
            return tmp;
        else
            return find(x,t->right);
    }

};

#endif // BINARYTREE_H_INCLUDED
