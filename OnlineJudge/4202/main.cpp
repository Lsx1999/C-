#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=100005;
int n,ans,a[N][5],f[N][5];
void dp(int k)
{
	memset(f,0,sizeof(f));
	f[1][k]=a[1][k];
	for(int i=2;i<=n;i++)
	{
		f[i][1]=max(f[i-1][3],f[i-1][4])+a[i][1];
		f[i][2]=f[i-1][4]+a[i][2];
		f[i][3]=f[i-1][1]+a[i][3];
		f[i][4]=max(f[i-1][1],f[i-1][2])+a[i][4];
	}
	if(k==1)
		ans=max(ans,max(f[n][3],f[n][4]));
	else if(k==2)
		ans=max(ans,f[n][4]);
	else if(k==3)
		ans=max(ans,f[n][1]);
	else
		ans=max(ans,max(f[n][1],f[n][2]));
}
int main()
{
	cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i][1]>>a[i][2]>>a[i][4];
    	a[i][3]=a[i][2];
	}
    for(int i=1;i<=4;i++)
    	dp(i);
    cout<<ans;
    return 0;
}

