#ifndef ADJLISTGRAPH_H_INCLUDED
#define ADJLISTGRAPH_H_INCLUDED
#include<iostream>
using namespace std;

class outOfBound{};
class illegal{};

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
    void display()const
    {
        for(int i = 1;i <=currentSize;++i)
        {
            cout<<array[i]<<" ";
        }
    }
private:
    Type* array;
    int currentSize;
    int maxSize;
    void buildHeap();
    void doubleSpace();
    void percolateDown(int hole);
};


class disJointSet
{
private:
    int* parent;
    int size;
public:
    disJointSet(int s)
    {
          size = s;
          parent = new int[s];
          for(int i = 0;i < s;++i)
          parent[i] = -1;
    }
    ~disJointSet(){delete[] parent;}
    int find(int x)const
    {
        if(x < 0 || x > size - 1)
        throw outOfBound();
        if(parent[x] < 0)
        return x;
        return parent[x] = find(parent[x]);
    }
    void Union(int root1,int root2)
    {
        if(root1 == root2)
        return;
       if(parent[root1] > parent[root2])
       {
        parent[root2] += parent[root1];
        parent[root1] = root2;
       }
       else
       {
        parent[root1] += parent[root2];
        parent[root2] = root1;
       }
    }
};

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

    struct EulerNode
    {
        int NodeNum;
        EulerNode* next;
        EulerNode(int node):NodeNum(node),next(NULL){}
    };

    struct edge
    {
        int beg,end;
        int weight;
       bool operator<(const edge& e){return weight < e.weight;}
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

    verNode* clone()const
    {
        verNode* tmp = new verNode[Vers];
        edgeNode* p;
        for(int i = 0;i < Vers;++i)
        {
            tmp[i].ver = verList[i].ver;
            p = verList[i].head;
            while(p)
            {
                tmp[i].head = new edgeNode(p->end,p->weight,tmp[i].head);
                p = p->next;
            }
        }
        return tmp;
    }

    void printPath(int start,int end,int prev[])
    {
        if(start == end)
           {
              cout<<verList[start].ver;
              return;
           }
        printPath(start,prev[end],prev);
        cout<<"-"<<verList[end].ver;

    }
    void EulerCircuit(int start,EulerNode*& beg,EulerNode*& end);
    void dfs(int start,bool visited[]);
public:

    adjListGraph(int vSize,const TypeOfVer d[]);
    ~adjListGraph();
    void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w);
    void remove(TypeOfVer x,TypeOfVer y);
    void EulerCircuit(TypeOfVer start);
    bool exist(TypeOfVer x,TypeOfVer y)const;
    int numOfVer()const{return Vers;}
    int numOfEdge()const{return Edges;}
    void dfs();
    void bfs()const;
    void topSort()const;
    //void criticalPath()const;
    void Kruskal()const;
    void Prim(TypeOfEdge noEdge)const;
    void unweightedShortDistance(TypeOfVer start,TypeOfEdge noEdge)const;
    void dijkstra(TypeOfVer start,TypeOfEdge noEdge);
};


#endif // ADJLISTGRAPH_H_INCLUDED
