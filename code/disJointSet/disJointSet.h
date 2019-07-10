#ifndef DISJOINTSET_H_INCLUDED
#define DISJOINTSET_H_INCLUDED
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
};


#endif // DISJOINTSET_H_INCLUDED
