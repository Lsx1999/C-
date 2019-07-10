#ifndef ADJMATRIXGRAPH_H_INCLUDED
#define ADJMATRIXGRAPH_H_INCLUDED

class outOfBound{};

template<class TypeOfVer,class TypeOfEdge>
class adjMatrixGraph
{
private:
    int Vers;
    int Edges;
    TypeOfVer* ver;
    TypeOfEdge** edge;
    TypeOfEdge noEdge;
    int find(TypeOfVer v)const
    {
        for(int i = 0;i < Vers;++i)
            if(ver[i] == v)
            return i;
        throw outOfBound();
    }
public:
    adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag);
    ~adjMatrixGraph();
    int numOfVer()const{return Vers;}
    int numOfEdge()const{return Edges;}
    void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w);
    void remove(TypeOfVer x,TypeOfVer y);
    bool exist(TypeOfVer x,TypeOfVer y)const;
};


#endif // ADJMATRIXGRAPH_H_INCLUDED
