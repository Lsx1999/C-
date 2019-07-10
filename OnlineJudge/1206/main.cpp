#include<iostream>
#include<cstring>
using namespace std;

class outOfBound {};
class illegal {};

template<class T>
class linkStack
{
private:
	struct node
	{
		T data;
		node* next;

		node(const T& x, node* n = NULL) :data(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};
	node* Top;
public:
	linkStack();
	~linkStack();
	void push(const T& x);
	void pop();
	bool isEmpty()const;
	T top()const;
};

template<class T>
linkStack<T>::linkStack()
{
	Top = NULL;
}

template<class T>
linkStack<T>:: ~linkStack()
{
	node* tmp;
	while (Top)
	{
		tmp = Top;
		Top = Top->next;
		delete tmp;
	}
}

template<class T>
void linkStack<T>::push(const T& x)
{
	Top = new node(x, Top);
}

template<class T>
void linkStack<T>::pop()
{
	if (isEmpty())
		throw outOfBound();
	node* tmp = Top;
	Top = Top->next;
	delete tmp;
}

template<class T>
T linkStack<T>::top()const
{
	if (isEmpty())
		throw outOfBound();
	return Top->data;
}

template<class T>
bool linkStack<T>::isEmpty()const
{
	return Top == NULL;
}

char s[1000];
int main()
{
    linkStack<char> s1,s2,s3;
    while(cin>>s)
    {
        if(s[0]=='i'&&s[1]=='f'&&strlen(s)==2)
        {
            s1.push('i');
        }
        else if (s[0]=='b'&&s[1]=='e'&&s[2]=='g'&&s[3]=='i'&&s[4]=='n'&&strlen(s)==5)
        {
            s2.push('b');
        }
        else if (s[0]=='e'&&s[1]=='n'&&s[2]=='d'&&strlen(s)==3)
        {
            if (s2.isEmpty()) {cout << "Error!"; return 0;}
            else s2.pop();

        }
        else if (s[0]=='t'&&s[1]=='h'&&s[2]=='e'&&s[3]=='n'&&strlen(s)==4)
        {
           if (s1.isEmpty()) {cout << "Error!"; return 0;}
           else {s1.pop(); s3.push('i');}
        }
        else if (s[0]=='e'&&s[1]=='l'&&s[2]=='s'&&s[3]=='e')
        {
            if (s3.isEmpty()) {cout << "Error!"; return 0;}
            else s3.pop();
        }
    }
    if(!s1.isEmpty() || !s2.isEmpty())
        {cout << "Error!"; return 0;}
    cout<<"Match!";
    return 0;
}
