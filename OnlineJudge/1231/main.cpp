#include <iostream>
using namespace std;

int main()
{
    int n,x,y,i,temp1,temp2,tmp1,tmp2,p;
    int cnt1 = 0,cnt2 = 0;
    int* parent,*x_parent,*y_parent;
    cin>>n>>x>>y;
    parent = new int[n + 1];
    x_parent = new int[n];
    y_parent = new int[n];
    for(i = 0;i < n+1;++i)
        parent[i] = -1;
    for(i = 1;i <= n;++i)
    {
        cin>>temp1>>temp2;
        if(temp1 != 0)
            parent[temp1] = i;
        if(temp2 != 0)
            parent[temp2] = i;
    }
    tmp1 = x;
    tmp2 = y;
    while(tmp1 != 1)
    {
        x_parent[cnt1++] = tmp1;
        tmp1 = parent[tmp1];
    }
    x_parent[cnt1] = 1;
     while(tmp2 != 1)
    {
        y_parent[cnt2++] = tmp2;
        tmp2 = parent[tmp2];
    }
    y_parent[cnt2] = 1;
    while(cnt1 >= 0 && cnt2 >= 0 && x_parent[cnt1] == y_parent[cnt2])
    {
        p = x_parent[cnt1];
        cnt1--;cnt2--;
    }
    cout<<p;
    return 0;
}
