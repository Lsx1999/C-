#include <iostream>
using namespace std;

class outOfBound{};
class illegal{};

template<class elemType>
class queue
{
public:
    virtual void enqueue(const elemType& x) = 0;
    virtual void dequeue() = 0;
    virtual bool isEmpty()const = 0;
    virtual elemType getHead()const = 0;
    virtual ~queue(){}
};

template<class T>
class linkQueue: public queue<T>
{
private:
    struct node
    {
        T data;
        node* next;

        node(const T& x,node* n = NULL):data(x),next(n){}
        node():next(NULL){}
        ~node(){}
    };
    node* front,*rear;
public:
    linkQueue();
    ~linkQueue();
    void enqueue(const T& x);
    void dequeue();
    bool isEmpty()const;
    T getHead()const;
} ;

template<class T>
linkQueue<T> :: linkQueue()
{
    front = rear = NULL;
}

template<class T>
linkQueue<T> :: ~linkQueue()
{
    node* tmp;
    while(front)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template<class T>
bool linkQueue<T> :: isEmpty()const
{
    return rear == NULL;
}

template<class T>
void linkQueue<T> :: enqueue(const T& x)
{
    if(rear == NULL)
        front = rear = new node(x);
    else
    {
        rear->next = new node(x);
        rear = rear->next;
    }
}

template<class T>
void linkQueue<T> :: dequeue()
{
    if(rear == NULL)
        throw outOfBound();
    node* tmp = front;
    front = front->next;
    if(!front) rear = NULL;
    delete tmp;
}

template<class T>
T linkQueue<T> :: getHead()const
{
    if(front == NULL)
        throw outOfBound();
    return front->data;
}
//****************************************************************************************************************************************************************
template<class TypeOfVer,class TypeOfEdge>
class adjListGraph
{
private:
    int Vers;
    int Edges;

    struct edgeNode
    {
        int end;
        TypeOfEdge weight;
        edgeNode* next;
        edgeNode(int e,TypeOfEdge w,edgeNode* n = NULL):end(e),weight(w),next(n){}
    };

    struct verNode
    {
        TypeOfVer ver;
        edgeNode* head;
        verNode(edgeNode* h = NULL):head(h){}
    };
    verNode* verList;
    int find(TypeOfVer v)const
    {
        for(int i = 0;i < Vers;++i)
        {
            if(verList[i].ver == v)
                return i;
        }
        throw outOfBound();
    }
    void dfs(int start,bool visited[]);
public:
    adjListGraph(int vSize,const TypeOfVer d[]);
    ~adjListGraph();
    void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w);
    void remove(TypeOfVer x,TypeOfVer y);
    bool exist(TypeOfVer x,TypeOfVer y)const;
    int numOfVer()const{return Vers;}
    int numOfEdge()const{return Edges;}
    void dfs()const;
    void bfs()const;
    int TopSort()const;
};

template<class TypeOfVer,class TypeOfEdge>
int adjListGraph<TypeOfVer,TypeOfEdge>:: TopSort()const
{
    linkQueue<int> q1,q2;
    edgeNode* p;
    int current,sem = 1;
    int *inDegree = new int[Vers];

    for(int i = 0;i < Vers;++i)
        inDegree[i] = 0;
    for(int i = 0;i < Vers;++i)
    {
        for(p = verList[i].head;p != NULL;p = p->next)
        {
            ++inDegree[p->end];
        }
    }

    for(int i = 0;i < Vers;++i)
        if(inDegree[i] == 0)
        q1.enqueue(i);

    while(true)
    {
        while(!q1.isEmpty())
        {
            current = q1.getHead();
            q1.dequeue();
            for(p = verList[current].head;p !=  NULL;p = p->next)
            {
                if(--inDegree[p->end] == 0)
                    q2.enqueue(p->end);
            }
        }

        if(q2.isEmpty())
            break;
        ++sem;
        while(!q2.isEmpty())
        {
            current = q2.getHead();
            q2.dequeue();
            for(p = verList[current].head;p !=  NULL;p = p->next)
            {
                if(--inDegree[p->end] == 0)
                    q1.enqueue(p->end);
            }
        }
        if(q1.isEmpty())
            break;
        ++sem;
    }
    return sem;
}



template<class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>:: adjListGraph(int vSize,const TypeOfVer d[])
{
    Vers = vSize;
    Edges = 0;
    verList = new verNode[vSize];
    for(int i = 0;i < vSize;++i)
    {
        verList[i].ver = d[i];
    }
}

template<class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>:: ~adjListGraph()
{
    edgeNode *p;
    for(int i = 0;i < Vers;++i)
    {
        while((p = verList[i].head) != NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
    }
    delete[] verList;
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>:: insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w)
{
    int v = find(y);
    int u = find(x);
    verList[u].head = new edgeNode(v,w,verList[u].head);
    ++Edges;
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>:: remove(TypeOfVer x,TypeOfVer y)
{
    int u = find(x);
    int v = find(y);
    edgeNode *p,*q = NULL;
    p = verList[u].head;
    if(!p)
        return;
    if(p->end == v)
    {
        verList[u].head = p->next;
        delete p;
        --Edges;
        return;
    }
    while(p->next != NULL && p->next->end != v)
        p = p->next;
    if(p->next)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        --Edges;
    }
}

template<class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>:: exist(TypeOfVer x,TypeOfVer y)const
{
    int u = find(x);
    int v = find(y);
    edgeNode* p;
    p = verList[u].head;
    while(p)
    {
        if(p->end == v)
            return true;
        else
            p = p->next;
    }
    return false;
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>:: dfs()const
{
    bool *visited = new bool[Vers];

    for(int i = 0;i < Vers;++i)
        visited[i] = false;

    for(int i = 0;i < Vers;++i)
    {
        if(visited[i] == true)
           continue;
        dfs(i,visited);
    }
}


template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>:: dfs(int start,bool visited[])
{
    edgeNode* p = verList[start].head;

    cout<<verList[start].ver<<' ';
    visited[start] = true;

    while(p)
    {
        if(visited[p->end] == false)
            dfs(p->end,visited);
        p = p->next;
    }
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>:: bfs()const
{
    bool *visited = new bool[Vers];
    int currentNode;
    linkQueue<int> q;
    edgeNode* p;

    for(int i = 0;i < Vers;++i)
        visited[i] = false;

    for(int i = 0;i < Vers;++i)
    {
        if(visited[i] == true)
            continue;
        q.enqueue(i);
        while(!q.isEmpty())
        {
            currentNode = q.getHead();
            q.dequeue();

            if(visited[currentNode] == true)
                continue;
            cout<<verList[currentNode].ver<<' ';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while(p)
            {
                if(visited[p->end] == false)
                    q.enqueue(p->end);
                p = p->next;
            }
        }
    }
}


int main()
{
    int n,m,a,b,* data;
    cin>>n>>m;
    data = new int[n];
	for (int i = 0; i < n; ++i)
	{
		data[i] = i;
	}
	adjListGraph<int, int> graph(n, data);
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b;
		graph.insert(a - 1, b - 1, 1);
	}
	cout<<graph.TopSort();
    return 0;
}
