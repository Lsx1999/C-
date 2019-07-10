#include"adjMatrixGraph.h"

template<class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>:: adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag)
{
    Vers = vSize;
    Edges = 0;
    noEdge = noEdgeFlag;
    ver = new TypeOfVer[vSize];
    for(int i = 0;i < vSize;++i)
    {
        ver[i] = d[i];
    }
    edge = new TypeOfEdge*[vSize];
    for(int i = 0;i < vSize;++i)
    {
        edge[i] = new TypeOfEdge[vSize];
        for(int j = 0;j < vSize;++j)
        {
            edge[i][j] = noEdge;
        }
        edge[i][i] = 0;
    }
}

template<class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>:: ~adjMatrixGraph()
{
    delete[] ver;
    for(int i = 0;i < Vers;++i)
    {
        delete[] edge[i];
    }
    delete[] edge;
}

template<class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>:: insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w)//添加一条从x指向y的弧，且使得其权值为w
{
    int u,v;
    u = find(x);
    v = find(y);
    edge[u][v] = w;
    ++Edges;
}

template<class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>:: remove(TypeOfVer x,TypeOfVer y)
{
    int u,v;
    u = find(x);
    v = find(y);
    if(u == v)
        throw outOfBound();
    edge[u][v] = noEdge;
    --Edges;
}

template<class TypeOfVer,class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer,TypeOfEdge>:: exist(TypeOfVer x,TypeOfVer y)const
{
    int u,v;
    u = find(x);
    v = find(y);
    if(u == v)
        return false;
    if(edge[u][v] == noEdge)
        return false;
    return true;
}
