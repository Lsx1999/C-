#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include<iostream>
using namespace std;
class seqString
{
    friend seqString operator+(const seqString& s1,const seqString& s2);
    friend bool operator==(const seqString& s1,const seqString& s2);
    friend bool operator!=(const seqString& s1,const seqString& s2);
    friend bool operator>(const seqString& s1,const seqString& s2);
    friend bool operator>=(const seqString& s1,const seqString& s2);
    friend bool operator<(const seqString& s1,const seqString& s2);
    friend bool operator<=(const seqString& s1,const seqString& s2);
    friend ostream& operator<<(ostream& os,const seqString& s);
private:
    char* data;
    int len;
public:
    seqString(const char* s = "");
    ~seqString();
    seqString(const seqString& other);
    seqString& operator=(const seqString& other);
    seqString subStr(int start,int num)const;
    int length()const;
    void insert(int start,const seqString& s);
    void remove(int start,int num);
};


#endif // STRING_H_INCLUDED
