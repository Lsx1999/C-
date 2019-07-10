#include<iostream>

using namespace std;

class outOfBound {};
class illegal {};
//***************************************************************************list**************************************************************
template<class elemType>
class list
{
public:
	virtual void insert(int i, const elemType& x) = 0;
	virtual void remove(int i) = 0;
	virtual int search(const elemType& x)const = 0;
	virtual elemType visit(int i)const = 0;
	virtual void traverse()const = 0;
	virtual void clear() = 0;
	virtual int length()const = 0;
	virtual ~list() {}
};

template<class elemType>
class seqList : public list<elemType>
{
private:
	elemType* elem;
	int maxSize, currentLength;
	void doubleSpace();
public:
	seqList(int init = 10);
	~seqList() { delete[] elem; }
	void insert(int i, const elemType& x);
	void remove(int i);
	void clear();
	int length()const;
	elemType visit(int i)const;
	int search(const elemType& x)const;
	void traverse()const;
};

template<class elemType>
class linkList : public list<elemType>
{
private:
	struct node
	{
		elemType data;
		node* next;

		node(const elemType& x, node* n = NULL) :data(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};
	node* head;
public:
	linkList();
	~linkList() { clear(); delete head; }
	void clear();
	void insert(int i, const elemType& x);
	void remove(int i);
	int length()const;
	int search(const elemType& x)const;
	elemType visit(int i)const;
	void traverse()const;
};
template<class elemType>
seqList<elemType>::seqList(int init)
{
	elem = new elemType[init];
	maxSize = init;
	currentLength = 0;
}

template<class elemType>
void seqList<elemType>::clear()
{
	currentLength = 0;
}

template<class elemType>
int seqList<elemType>::length()const
{
	return currentLength;
}

template<class elemType>
elemType seqList<elemType>::visit(int i)const
{
	if (i < 0 || i > currentLength - 1)
		throw outOfBound();
	return elem[i];
}

template<class elemType>
int seqList<elemType>::search(const elemType & x)const
{
	int i;
	for (i = 0; i < currentLength; ++i)
	{
		if (elem[i] == x)
			return i;
	}
	return -1;
}

template<class elemType>
void seqList<elemType>::traverse()const
{
	for (int i = 0; i < currentLength; ++i)
	{
		cout << elem[i] << ' ';
	}
	cout << endl;
}

template<class elemType>
void seqList<elemType>::remove(int i)
{
	if (i < 0 || i > currentLength - 1)
		throw outOfBound();
	for (int j = i; j < currentLength - 1; ++j)
	{
		elem[j] = elem[j + 1];
	}
	currentLength--;
}

template<class elemType>
void seqList<elemType>::insert(int i, const elemType & x)
{
	if (i < 0 || i > currentLength)
		throw outOfBound();
	if (currentLength == maxSize)
		doubleSpace();
	for (int j = currentLength - 1; j >= i; --j)
	{
		elem[j + 1] = elem[j];
	}
	elem[i] = x;
	currentLength++;
}

template<class elemType>
void seqList<elemType>::doubleSpace()
{
	elemType* tmp = elem;
	elem = new elemType[2 * maxSize];
	for (int i = 0; i < currentLength; ++i)
	{
		elem[i] = tmp[i];
	}
	delete[] tmp;
	maxSize *= 2;
}




template<class elemType>
linkList<elemType>::linkList()
{
	head = new node();
}

template<class elemType>
void linkList<elemType>::clear()
{
	node* p = head->next, * q;
	head->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		delete q;
	}
}

template<class elemType>
void linkList<elemType>::insert(int i, const elemType & x)
{
	if (i < 0)
		throw outOfBound();
	node* p = head;
	for (int j = 0; j < i && p; ++j)
	{
		p = p->next;
	}
	if (!p)
		throw outOfBound();
	p->next = new node(x, p->next);
}

template<class elemType>
void linkList<elemType>::remove(int i)
{
	if (i < 0)
		throw outOfBound();
	node* p = head, * tmp;
	for (int j = 0; j < i && p; ++j)
	{
		p = p->next;
	}
	if (!p || !(p->next))
		throw outOfBound();
	tmp = p->next;
	p->next = tmp->next;
	delete tmp;
}

template<class elemType>
int linkList<elemType>::length()const
{
	int i = 0;
	node* p = head->next;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

template<class elemType>
int linkList<elemType>::search(const elemType & x)const
{
	node* p = head->next;
	int i = 0;
	while (p && p->data != x)
	{
		i++;
		p = p->next;
	}
	if (!p)
		return -1;
	return i;
}

template<class elemType>
elemType linkList<elemType>::visit(int i)const
{
	if (i < 0)
		throw outOfBound();
	node* p = head->next;
	for (int j = 0; j < i && p; ++j)
	{
		p = p->next;
	}
	if (!p)
		throw outOfBound();
	return p->data;
}

template<class elemType>
void linkList<elemType>::traverse()const
{
	node* p = head->next;
	while (p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
}
//**********************************************************************************************************************************************
//****************************************************************************linkStack****************************************************************************
template<class T>
class linkStack
{
private:
	struct node
	{
		T data;
		node* next;

		node(const T& x, node* n = NULL) :data(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};
	node* Top;
public:
	linkStack();
	~linkStack();
	void push(const T& x);
	void pop();
	bool isEmpty()const;
	T top()const;
};

template<class T>
linkStack<T>::linkStack()
{
	Top = NULL;
}

template<class T>
linkStack<T>:: ~linkStack()
{
	node* tmp;
	while (Top)
	{
		tmp = Top;
		Top = Top->next;
		delete tmp;
	}
}

template<class T>
void linkStack<T>::push(const T & x)
{
	Top = new node(x, Top);
}

template<class T>
void linkStack<T>::pop()
{
	if (isEmpty())
		throw outOfBound();
	node* tmp = Top;
	Top = Top->next;
	delete tmp;
}

template<class T>
T linkStack<T>::top()const
{
	if (isEmpty())
		throw outOfBound();
	return Top->data;
}

template<class T>
bool linkStack<T>::isEmpty()const
{
	return Top == NULL;
}

//*****************************************************************************************************************************************************************
//***************************************************************************linkQueue*****************************************************************************
template<class T>
class linkQueue
{
private:
	struct node
	{
		T data;
		node* next;

		node(const T& x, node* n = NULL) :data(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};
	node* front, * rear;
public:
	linkQueue();
	~linkQueue();
	void enqueue(const T& x);
	void dequeue();
	bool isEmpty()const;
	T getHead()const;
	T getTail()const;
};

template<class T>
linkQueue<T> ::linkQueue()
{
	front = rear = NULL;
}

template<class T>
linkQueue<T> :: ~linkQueue()
{
	node* tmp;
	while (front)
	{
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template<class T>
bool linkQueue<T> ::isEmpty()const
{
	return rear == NULL;
}

template<class T>
void linkQueue<T> ::enqueue(const T & x)
{
	if (rear == NULL)
		front = rear = new node(x);
	else
	{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template<class T>
void linkQueue<T> ::dequeue()
{
	if (rear == NULL)
		throw outOfBound();
	node * tmp = front;
	front = front->next;
	if (!front) rear = NULL;
	delete tmp;
}

template<class T>
T linkQueue<T> ::getHead()const
{
	if (front == NULL)
		throw outOfBound();
	return front->data;
}

template<class T>
T linkQueue<T> ::getTail()const
{
	if (rear == NULL)
		throw outOfBound();
	return rear->data;
}
//*****************************************************************************************************************************************************************
//********************************************************************小顶堆的优先级队列***************************************************************************
template<class Type>
class priorityQueue
{
public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[],int size);
    ~priorityQueue();
    void enqueue(const Type& x);
    void dequeue();
    Type getHead()const;
    bool isEmpty()const;
private:
    Type* array;
    int currentSize;
    int maxSize;
    void buildHeap();
    void doubleSpace();
    void percolateDown(int hole);
};

template<class Type>
priorityQueue<Type>:: priorityQueue(int capacity)
{
    array = new Type[capacity];
    currentSize = 0;
    maxSize = capacity;
}

template<class Type>
priorityQueue<Type>:: priorityQueue(const Type data[],int size)
{
    maxSize = size + 10;
    currentSize = size;
    array = new Type[maxSize];
    for(int i = 0;i < size;++i)
    {
        array[i+1] = data[i];
    }
    buildHeap();
}

template<class Type>
priorityQueue<Type>:: ~priorityQueue()
{
    delete[] array;
}

template<class Type>
void priorityQueue<Type>:: enqueue(const Type& x)
{
    if(currentSize == maxSize - 1)
        doubleSpace();
    int hole = ++currentSize;
    for(;hole > 1 && x < array[hole/2];hole/=2)
    {
        array[hole] = array[hole/2];
    }
    array[hole] = x;
}

template<class Type>
void priorityQueue<Type>:: dequeue()
{
    array[1] = array[currentSize--];
    percolateDown(1);
}

template<class Type>
Type priorityQueue<Type>:: getHead()const
{
    return array[1];
}

template<class Type>
bool priorityQueue<Type>:: isEmpty()const
{
    return currentSize == 0;
}

template<class Type>
void priorityQueue<Type>:: percolateDown(int hole)
{
    int child;
    Type tmp = array[hole];
    for(;hole * 2 <= currentSize;hole = child)
    {
        child  = 2 * hole;
        if(child != currentSize && array[child+1] < array[child])
            child++;
        if(array[child] < tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>:: buildHeap()
{
    for(int i = currentSize/2;i > 0;--i)
        percolateDown(i);
}

template<class Type>
void priorityQueue<Type>:: doubleSpace()
{
    Type* tmp = array;
    array = new Type[2*maxSize];
    for(int i = 0;i < currentSize;++i)
    {
        array[i] = tmp[i];
    }
    maxSize *= 2;
    delete[] tmp;
}
//**********************************************************************************************************************************************
//********************************************************************AvlTree********************************************************************
template<class Type>
class AvlTree
{
private:
    struct node
    {
        Type data;
        node *left,*right;
        int height;

        node(const Type& x,node* l = NULL,node* r = NULL,int& h = 0):data(x),left(l),right(r),height(h){}
        node():left(NULL),right(NULL),height(0){}
        ~node(){}
    };
    node* root;
public:
    AvlTree();
    ~AvlTree();
    bool find(const Type& x)const;
    void insert(const Type& x);
    void remove(const Type& x);
private:
    void clear(node* t);
    void LL(node*& t);
    void LR(node*& t);
    void RL(node*& t);
    void RR(node*& t);
    void insert(const Type& x,node*& t);
    bool remove(const Type& x,node*& t);
    bool adjust(node*& t,int subTree);
    int max(int a,int b){return(a > b)?a:b;}
    int height(node* t){return(t == NULL)?0:t->height;}
};

template<class Type>
AvlTree<Type>:: AvlTree()
{
    root = NULL;
}

template<class Type>
AvlTree<Type>:: ~AvlTree()
{
    clear(root);
}

template<class Type>
void AvlTree<Type>:: clear(node* t)
{
    if(t == NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template<class Type>
bool AvlTree<Type>:: find(const Type& x)const
{
    node* tmp = root;
    while(tmp)
    {
        if(x == tmp->data)return true;
        if(x < tmp->data)tmp = tmp->left;
        else tmp = tmp->right;
    }
    return false;
}

template<class Type>
void AvlTree<Type>:: LL(node*& t)
{
    node* tmp = t->left;     //����ָ��ָ��
    t->left = tmp->right;
    tmp->right = t;
    t->height = max(height(t->right),height(t->left)) + 1;   //���¼���߶�
    tmp->height = max(height(t),height(tmp->left)) + 1;   //������eight()��������ֱ�������ݳ�Աheight������Ϊt->right��Щ��������Ϊ��
    t = tmp;   //ͨ�����ô��ݽ����ڵ����ӽڵ���������
}

template<class Type>
void AvlTree<Type>:: LR(node*& t)
{
    RR(t->left);
    LL(t);
}

template<class Type>
void AvlTree<Type>:: RL(node*& t)
{
    LL(t->right);
    RR(t);
}

template<class Type>
void AvlTree<Type>:: RR(node*& t)
{
    node* tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t->height = max(height(t->left),height(t->right)) + 1;
    tmp->height = max(height(t),height(tmp->right)) + 1;
    t = tmp;
}

template<class Type>
void AvlTree<Type>:: insert(const Type& x)
{
    insert(x,root);
}

template<class Type>
void AvlTree<Type>:: insert(const Type& x,node*& t)
{
    if(!t)
    {
        t = new node(x);
        return;
    }
    if(x < t->data)
    {
        insert(x,t->left);
        if(height(t->left) - height(t->right) == 2)
           {
             if(x < t->left->data)
               LL(t);
             else
               LR(t);
           }
    }
    else
    {
        if(x > t->data)
        {
            insert(x,t->right);
            if(height(t->right) - height(t->left) == 2)
               {
                 if(x > t->right->data)
                    RR(t);
                 else
                    RL(t);
               }
        }
    }
    t->height = max(height(t->left),height(t->right)) + 1;
}

template<class Type>
void AvlTree<Type>:: remove(const Type& x)
{
    remove(x,root);
}

template<class Type>
bool AvlTree<Type>:: remove(const Type& x,node*& t)
{
    if(!t)
        return false;
    if(x == t->data)
    {
        if(!t->left || !t->right)  //ɾ��Ҷ�ӽڵ����ֻ��һ�����ӵĽڵ�
        {
            node* tmp = t;
            t = (t->left)?t->left:t->right;
            delete tmp;
            return false;
        }
        else
        {
            node* tmp = t->right;
            while(tmp)
                tmp = tmp->left;
            t->data = tmp->data;
            if(remove(tmp->data,t->right))
                return true;
            return adjust(t,1);
        }
    }
    if(x < t->data)
    {
        if(remove(x,t->left))
            return true;
        return adjust(t,0);
    }
    else
    {
        if(remove(x,t->right))
            return true;
        return adjust(t,1);
    }
}

template<class Type>
bool AvlTree<Type>::adjust(node*& t,int subTree)
{
    if(subTree)  //ɾ��������t����������
    {
        if(height(t->left) - height(t->right) == 1)
            return true;
        if(height(t->left) == height(t->right))
           {
               --t->height;
              return false;
           }
        if(height(t->left->right) > height(t->left->left))
        {
            LR(t);
            return false;
        }
        LL(t);
        if(height(t->right) == height(t->left))
            return false;
        else
            return true;
    }
    else
    {
        if(height(t->right) - height(t->left) == 1)
            return true;
        if(height(t->left) == height(t->right))
           {
               --t->height;
              return false;
           }
        if(height(t->right->right) > height(t->right->left))
        {
            RL(t);
            return false;
        }
        RR(t);
        if(height(t->right) == height(t->left))
            return false;
        else
            return true;
    }
}
//********************************************************************************************************************************************
int main()
{

    return 0;
}
