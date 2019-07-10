#ifndef BINOMIALHEAP_H_INCLUDED
#define BINOMIALHEAP_H_INCLUDED
#include<iostream>
using namespace std;

template<class Type>
class binomialHeap
{
private:
	struct node
	{
		Type data;
		node* child, * sibling;
		int degree;

		node(const Type& x, node* c = NULL, node* b = NULL, const int& d = 0) :data(x), child(c), sibling(b), degree(d) {}
		node() :child(NULL), sibling(NULL), degree(0) {}
		~node() {}
	};
	node* head;
	void clear(node* h);
	node* merge(node* h1, node* h2)
	{
		node* h = NULL;
		node* p = NULL;
		node* p1 = h1;
		node* p2 = h2;
		if (!p1 || !p2)
		{
			h = (p1) ? p1 : p2;
			return h;
		}
		if (p1->degree < p2->degree)
		{
			h = p1;
			p = p1;
			p1 = p1->sibling;
		}
		else
		{
			h = p2;
			p = p2;
			p2 = p2->sibling;
		}
		while (p1 && p2)
		{
			if (p1->degree < p2->degree)
			{
				p->sibling = p1;
				p = p1;
				p1 = p1->sibling;
			}
			else
			{
				p->sibling = p2;
				p = p2;
				p2 = p2->sibling;
			}
		}
		if (p1)
			p->sibling = p1;
		else
			p->sibling = p2;
		if (!h)
			return h;

		node* x = h, * next_x = h->sibling, * prev_x = NULL;
		while (next_x)
		{
			if (x->degree != next_x->degree || (next_x->sibling && x->degree == next_x->sibling->degree))
			{
				prev_x = x;
				x = next_x;
			}
			else
			{
				if (x->data < next_x->data)
				{
					x->sibling = next_x->sibling;
					next_x->sibling = x->child;
					x->child = next_x;
					x->degree++;
				}
				else
				{
					if (!prev_x)
						h = next_x;
					else
						prev_x->sibling = next_x;
					x->sibling = next_x->child;
					next_x->child = x;
					next_x->degree++;
					x = next_x;
				}
			}
			next_x = x->sibling;
		}
		return h;
	}
public:
	binomialHeap();
	~binomialHeap();
	void enqueue(const Type& x);
	void dequeue();
	bool isEmpty()const;
	Type getHead()const;
	Type getMin()const;
	void merge(node* other);
};
#endif // BINOMIALHEAP_H_INCLUDED
