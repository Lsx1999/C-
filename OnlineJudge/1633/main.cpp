#include <iostream>
using namespace std;

class outOfBound{};
class disJointSet
{
private:
    int* parent;
    int size;
public:
    disJointSet(int s);
    ~disJointSet(){delete[] parent;}
    int find(int x)const;
    void Union(int root1,int root2);
    int visit(int x)
    {
        int num = -parent[find(x)];
        return num;
    }
};
disJointSet:: disJointSet(int s)
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
}

int main()
{
    int n,m,k,tmp,*data;
    cin>>n>>m;
    disJointSet ds(n);
    for(int i = 1;i <= m;++i)
    {
        cin>>k;
        data = new int[k];
        for(int j = 0;j < k;++j)
        {
            cin>>data[j];
        }
        for(int j = 0;j < k - 1;++j)
        {
            ds.Union(ds.find(data[j]),ds.find(data[j + 1]));
        }
    }
    cout<<ds.visit(0);
    return 0;
}
