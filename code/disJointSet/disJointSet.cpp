#include"disJointSet.h"
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
