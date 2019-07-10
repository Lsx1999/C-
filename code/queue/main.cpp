#include <iostream>
#include"queue.h"
#include"queue.cpp"

using namespace std;

int main()
{

  linkQueue <int> s;
  for (int i=0; i<10; ++i) s.enqueue(2*i);
  while (!s.isEmpty())
  {
      cout<<s.getHead()<<' ';
      s.dequeue();
  }
  cout << endl;
  for (int i=0; i<15; ++i) s.enqueue(i);
  while (!s.isEmpty())
  {
      cout<<s.getHead()<<' ';
      s.dequeue();
  }
  cout << endl;

  return 0;
}
