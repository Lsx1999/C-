#include<iostream>
#include"adjListGraph.h"
using namespace std;


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


/*disJointSet:: disJointSet(int s)
{
    size = s;
    parent = new int[s];
    for(int i = 0;i < s;++i)
        parent[i] = -1;
}

int disJointSet:: find(int x)const
{
    if(x < 0 || x > size - 1)
        throw outOfBound();
    if(parent[x] < 0)
        return x;
    return parent[x] = find(parent[x]);
}

void disJointSet:: Union(int root1,int root2)
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
}*/

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
void adjListGraph<TypeOfVer,TypeOfEdge>:: dfs()
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

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge> ::EulerCircuit(int start,EulerNode*& beg,EulerNode*& end)
{
    int nextNode;
    beg = end = new EulerNode(start);
    while(verList[start].head)
    {
        nextNode = verList[start].head->end;
        remove(verList[start].ver,verList[nextNode].ver);
        remove(verList[nextNode].ver,verList[start].ver);
        start = nextNode;
        end->next = new EulerNode(start);
        end = end->next;
    }
}
template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge> :: EulerCircuit(TypeOfVer start)
{
    EulerNode *beg,*end,*p,*q,*tb,*te;
    verNode* tmp;
    edgeNode* r;
    int numOfDegree,i;

    //检查欧拉回路的存在性
    for(int i = 0;i < Vers;++i)
    {
        numOfDegree = 0;
        r = verList[i].head;
        //假设是无向图。没有出度和入度的区别
        //对于一个节点，顺着它对应的单链表数即可
        while(r)
        {
            ++numOfDegree;
            r = r->next;
        }
        //任何一个节点的度为奇数，都不存在欧拉回路
        if(numOfDegree % 2)
            return;
    }
    //如果存在欧拉回路：
    i = find(start);
    tmp = clone();

    EulerCircuit(i,beg,end);
    while(true)
    {
        p = beg;
        while(p->next)
       {
         if(verList[p->next->NodeNum].head)
            break;
         else
            p = p->next;
       }
       if(!p->next)
        break;
       q = p->next;
       EulerCircuit(q->NodeNum,tb,te);
       te->next = q->next;
       p->next = tb;
       delete q;
    }

    delete[] verList;
    verList = tmp;

    while(beg)
        {
            cout<<verList[beg->NodeNum].ver<<'\t';
            p = beg;
            beg = beg->next;
            delete p;
        }

    cout<<endl;

}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge> :: topSort()const
{
    linkQueue<int> q;
    int inDegree[Vers] = {0};
    edgeNode* p;
    int tmp;

    //计算每个节点的入度
    for(int i = 0;i < Vers;++i)
    {
       p = verList[i].head;
       while(p)
       {
           ++inDegree[p->end];
           p = p->next;
       }
    }

    for(int i = 0;i < Vers;++i)
    {
        if(!inDegree[i])
            q.enqueue(i);
    }

    while(!q.isEmpty())
    {
        tmp = q.getHead();
        cout<<verList[tmp].ver<<'\t';
        q.dequeue();
        p = verList[tmp].head;
        while(p)
        {
            --inDegree[p->end];
            if(!inDegree[p->end])
                q.enqueue(p->end);
            p = p->next;
        }
    }
    cout<<endl;
}

/*template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge> :: criticalPath()const
{
    TypeOfEdge *ee = new TypeOfEdege[Vers],*le = new TypeOfEdge[Vers];
    int *top = new int[Vers];
    int inDegree[Vers] = {0};
    linkQueue<int> q;
    int i;
    edgeNode* p;
    edge* edgeEL;

    for(i = 0;i <Vers;++i)
    {
        for(p = verList[i].head;p != NULL;p = p->next)
        {
            ++inDegree[p->end];
        }
    }

    for(int i = 0;i < Vers;++i)
    {
        if(!inDegree[i])
            q.enqueue(i);
    }
    i = 0;
    while(!q.isEmpty())
    {
        top[i] = q.getHead();
        q.dequeue();
        for(p = verList[top[i]].head;p != NULL;p = p->next)
        {
            if(--inDegree[p->end] == 0)
                q.enqueue(p->end);
        }
         ++i;
    }

    //找顶点的最早发生时间
    for(i = 0;i < Vers;++i)
        ee[i] = 0;

    for(i = 0;i < Vers;++i)
    {
        for(p = verList[top[i]].head;p != NULL;p = p->next)
            if(ee[p->end] < ee[top[i]] + p->weight)
            ee[p->end] = ee[ptop[i]] + p->weight;
    }

    //找最晚发生时间
    for(i = 0;i < Vers;++i)
        le[i] = ee[Vesr - 1];
    for(i = Vers - 1;i >= 0;--i)
    {
        for(p = verList[top[i]].head;p != NULL;p = p->next)
        {
            if(le[p->end] - p->weight < le[top[i]])
                le[top[i]] = le[p->end] - p->weight;
        }
    }

    //找活动的最早和最迟发生时间


}
*/

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge> :: Kruskal()const
{
    disJointSet ds(Vers);
    priorityQueue<edge> pq;
    edgeNode* p;
    edge tmp;
    int u,v,cnt = 0;

    //建立优先级队列
    for(int i = 0;i < Vers;++i)
    {
        p = verList[i].head;
        while(p)
        {
            if(i < p->end)
            {
                tmp.beg = i;
                tmp.end = p->end;
                tmp.weight = p->weight;
                pq.enqueue(tmp);
            }
            p = p->next;
        }
    }

    //开始选择边
    while(!pq.isEmpty())
    {
        if(cnt < Vers - 1)
       {
           tmp = pq.getHead();
           pq.dequeue();
           u = ds.find(tmp.beg);
           v = ds.find(tmp.end);
           if(u != v)
          {
            cnt++;
            ds.Union(u,v);
            cout<<"("<<verList[tmp.beg].ver<<","<<verList[tmp.end].ver<<")"<<'\t';
          }
       }
       else
        break;
    }
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge> :: Prim(TypeOfEdge noEdge)const
{
    bool* flag = new bool[Vers];//标志每个节点是否已经在最小生成树中
    TypeOfEdge* lowCost = new TypeOfEdge[Vers];//记录每个节点距离最小生成树的距离
    int* startNode = new int[Vers];//记录每个节点到最小生成树的距离是从最小生成树中的哪个节点出发得到的

    edgeNode* p;
    int start;
    TypeOfEdge min;
    for(int i = 0;i < Vers;++i)
    {
        flag[i] = false;
        lowCost[i] = noEdge;
    }

    start = 0;
    for(int i = 1;i < Vers;++i)
    {
        for(p = verList[start].head;p != NULL;p = p->next)
        {
            if(!flag[p->end] && lowCost[p->end] > p->weight)
            {
                lowCost[p->end] = p->weight;
                startNode[p->end] = start;
            }
        }
        flag[start] = true;

        min = noEdge;
        for(int j = 0;j < Vers;++j)
        {
            if(lowCost[j] < min)
            {
                min = lowCost[j];
                start = j;
            }
        }
        cout<<"("<<verList[startNode[start]].ver<<","<<verList[start].ver<<")"<<'\t';
        lowCost[start] = noEdge;
    }
    delete[] flag;
    delete[] lowCost;
    delete[] startNode;
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge> :: unweightedShortDistance(TypeOfVer start,TypeOfEdge noEdge)const
{
    linkQueue<int> q;
    TypeOfEdge* distance = new TypeOfEdge[Vers];
    int* prev = new int[Vers];
    int u,sNo;
    edgeNode* p;

    for(int i = 0;i < Vers;++i)
    {
        distance[i] = noEdge;
    }

    sNo = find(start);
    distance[sNo] = 0;
    prev[sNo] = sNo;
    q.enqueue(sNo);

    while(!q.isEmpty())
    {
        u = q.getHead();
        q.dequeue();
        for(p = verList[u].head;p != NULL;p = p->next)
        {
            if(distance[p->end] == noEdge)
            {
                distance[p->end] = distance[u] + 1;
                prev[p->end] = u;
                q.enqueue(p->end);
            }
        }
    }

    for(int i = 0;i < Vers;++i)
    {
        printPath(sNo,i,prev);
        cout<<endl;
    }
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::dijkstra(TypeOfVer start,TypeOfEdge noEdge)
{
    TypeOfEdge* distance = new TypeOfEdge[Vers];
    bool* known = new bool[Vers];
    int* prev = new int[Vers];

    edgeNode* p;
    int sNo,v;
    TypeOfEdge min;

    for (int i = 0; i < Vers; i++)
    {
        distance[i] = noEdge;
        known[i] = false;
    }

    sNo = find(start);
    distance[sNo] = 0;
    prev[sNo] = sNo;

    for(int i = 0;i < Vers;++i)
    {
        min = noEdge;
        for(int j = 0;j < Vers;++j)
        {
            if(!known[j] && distance[j] < min)
            {
                min = distance[j];
                v = j;
            }
        }
        known[v] = true;
        p = verList[v].head;
        while(p)
        {
            if(!known[p->end] && distance[p->end] > min + p->weight)
            {
                distance[p->end] = min + p->weight;
                prev[p->end] =  v;
            }
            p = p->next;
        }
    }


    for(int i = 0;i < Vers;++i)
    {
        printPath(sNo,i,prev);
        cout<<'\t'<<distance[i]<<endl;
    }
}
