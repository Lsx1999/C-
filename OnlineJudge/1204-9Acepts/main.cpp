#include <iostream>
#include<cstring>
using namespace std;

char s[100][2001];
int line = 0;
int main()
{
    void list(int,int);
    void ins(int,int,const char*);
    void del(int,int,int);
    void quit();
    char* content,*order,*str;
    int n1,n2,i,j,num,raw;
    cin.getline(content,2002);
    while(strcmp(content,"******") != 0)
    {
        strcpy(s[i],content);
        line++;
        cin.getline(content,2002);
    }
   /* cin.getline(order,6,' ');
    while(strcmp(order,"quit") != 0)
    {
        if(strcmp(order,"list") == 0)
        {
            cin>>n1>>n2;
            list(n1,n2);
        }
        if(strcmp(order,"ins") == 0)
        {
            cin>>i>>j;
            cin.getline(str,101);
            ins(i,j,str);
        }
        if(strcmp(order,"del") == 0)
        {
            cin>>i>>j>>num;
            del(i,j,num);
        }
        cin.getline(order,6,' ');
    }
    if(strcmp(order,"quit") == 0)
    {
        for(i = 0;i < line;++i)
            cout<<s[i]<<endl;
    }*/

    return 0;
}
/*
void list(int n1,int n2)
{
    if(n1 < 0 || n2 < n1 || n1 >line || n2 > line)
    {
      cout<<"Error!"<<endl;
      return;
    }
    for(int i = n1-1;i < n2-1;++i)
    {
        cout<<s[i]<<endl;
    }
}

void ins(int i,int j,const char* str)
{
    if(i < 0 || i > line)
    {
        cout<<"Error!"<<endl;
        return;
    }
    if(j < 0 || j > strlen(s[i-1])+1)
    {
        cout<<"Error!"<<endl;
        return;
    }
    if(strlen(str) > 100)
    {
        cout<<"Error!"<<endl;
        return;
    }
    char tmp[2001];
    int m = j-1+strlen(str);
    int n = 0;
    for(std::size_t k = j-1;k < strlen(s[i-1]);++k)
    {
        tmp[k-j+1] = s[i-1][k];
    }
    for(std::size_t k = j-1;k < j-1+strlen(str);++k)
    {
        s[i-1][k] = str[k-j+1];
    }
    while(tmp[n])
    {
        s[i-1][m] = tmp[n];
        m++;
        n++;
    }
    s[i-1][m] = '\0';
}

void del(int i,int j,int num)
{
     if(i < 0 || i > line)
    {
        cout<<"Error!"<<endl;
        return;
    }
    if(j < 0 || j+num > strlen(s[i-1]))
    {
        cout<<"Error!"<<endl;
        return;
    }
    int k;
    for(k = j+num-1;s[i-1][k];++k)
    {
        s[i-1][k-num] = s[i-1][k];
    }
    s[i-1][k] = '\0';
}

void quit()
{
    for(int i = 0;i < line;++i)
    {
        cout<<s[i]<<endl;
    }
}
*/
