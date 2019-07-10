#include<iostream>
#include"String.h"

using namespace std;

seqString:: seqString(const char* s)
{
    for(len = 0;s[len] != '\0';++len);
    data = new char[len + 1];
    for(len = 0;s[len] != 0;++len)
    {
        data[len] = s[len];
    }
    data[len] = '\0';
}

seqString:: seqString(const seqString& other)
{
    data = new char[other.len + 1];
    for(len = 0;len <= other.len;++len)
        data[len] = other.data[len];
}

seqString:: ~seqString()
{
    delete data;
}

int seqString:: length()const
{
    return len;
}

seqString& seqString:: operator=(const seqString& other)
{
    if(this == &other)
        return *this;
    delete data;
    data = new char[other.len + 1];
    for(len = 0;len <= other.len;++len)
        data[len] = other.data[len];
    return *this;
}

seqString seqString:: subStr(int start,int num)const
{
    if(start >= len - 1 || start < 0)
        return "";
    seqString tmp;int i;
    tmp.len = (start + num > len) ? len - start : num;  //感觉有问题
    delete tmp.data;
    for(i = 0;i < tmp.len;++i)
        tmp.data[i] = data[start + i];
    tmp.data[i] = '\0';
    return tmp;
}

void seqString:: insert(int start,const seqString& s)
{
    char* tmp = data;
    int i;
    if(start > len || start < 0)    //值得商榷
        return;
    len += s.len;
    data = new char[len + 1];
    for(i = 0;i < start;++i)
        data[i] = tmp[i];
    for(i = 0;i < s.len;++i)
        data[start + i] = s.data[i];
    for(i = start;tmp[i] != '\0';++i)
        data[i + s.len] = tmp[i];
    data[i + s.len] = '\0';
    delete tmp;
}

void seqString:: remove(int start,int num)
{
    if(start >= len -1 || start < 0)
        return;
    if(start + num >= len)
    {
        data[start] = '\0';
        len = start;
    }
    else
    {
        for(len =start;data[len+num] != '\0';++len)
        {
            data[len] = data[len + num];
            data[len] = '\0';
        }
    }
}

seqString operator+(const seqString& s1,const seqString& s2)
{
    seqString tmp;
    int i;
    tmp.len = s1.len + s2.len;
    tmp.data = new char[tmp.len + 1];
    for(i = 0;i < s1.len;++i)
        tmp.data[i] = s1.data[i];
    for(i = 0;i < s2.len;++i)
        tmp.data[s1.len + i] = s2.data[i];
    tmp.data[s1.len + s2.len] = '\0';
    return tmp;
}

bool operator==(const seqString& s1,const seqString& s2)
{
    if(s1.len != s2.len)
        return false;
    for(int i = 0;i < s1.len;++i)
    {
        if(s1.data[i] != s2.data[i])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const seqString& s1,const seqString& s2)
{
    return !(s1 == s2);
}

bool operator>(const seqString& s1,const seqString& s2)
{
    for(int i = 0;i < s1.len;++i)
    {
        if(s1.data[i] > s2.data[i])
            return true;

    else
    {
        if(s1.data[i] < s2.data[i])
            return false;
    }
    }
    return false;
}

bool operator>=(const seqString& s1,const seqString& s2)
{
    return (s1 == s2 || s1 > s2);
}

bool operator<(const seqString& s1,const seqString& s2)
{
    return !(s1 >= s2);
}

bool operator<=(const seqString& s1,const seqString& s2)
{
    return !(s1 > s2);
}

ostream& operator<<(ostream& os,const seqString& s)
{
    os<<s.data;
    return os;
}
