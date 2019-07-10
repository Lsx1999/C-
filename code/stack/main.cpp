#include <iostream>
#include"stack.h"
#include"stack.cpp"

using namespace std;

int main()
{
    linkStack<int> s;
    for(int i = 0;i<10;++i)
        s.push(2*i);
    while(!s.isEmpty())
    {
        cout<<s.top()<<' ';
         s.pop();
    }

    return 0;
}
