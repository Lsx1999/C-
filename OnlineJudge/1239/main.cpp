#include<iostream>
using namespace std;

int main()
{
    int wages,tax,diff;
    cin>>wages;
    diff = wages - 3500;
    if(diff <= 0)
    {
        cout<<0;
        return 0;
    }

    if(diff <= 1500)
    {
        tax = diff * 0.03;
        cout<<tax;
        return 0;
    }

    if(diff <= 4500)
    {
        tax = 45 +  (diff - 1500) * 0.1;
        cout<<tax;
        return 0;
    }

    if(diff <= 9000)
    {
        tax = 345 + (diff - 4500) * 0.2;
        cout<<tax;
        return 0;
    }

    if(diff <= 35000)
    {
        tax = 1245 + (diff - 9000) * 0.25;
        cout<<tax;
        return 0;
    }

    if(diff <= 55000)
    {
        tax = 7745 + (diff - 35000) * 0.3;
        cout<<tax;
        return 0;
    }

    if(diff <= 80000)
    {
        tax = 13745 + (diff - 55000) * 0.35;
        cout<<tax;
        return 0;
    }
    tax = 22495 + (diff - 80000) * 0.45;
    cout<<tax;
    return 0;
}

