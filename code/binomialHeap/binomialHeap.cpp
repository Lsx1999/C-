#include"binomialHeap.h"

template<class Type>
binomialHeap<Type>::binomialHeap()
{
	head = NULL;
}

template<class Type>
binomialHeap<Type>:: ~binomialHeap()
{
	clear(head);
}

template<class Type>
void binomialHeap<Type>::clear(node* h)
{
	if (!h)
		return;
	clear(h->child);
	clear(h->sibling);
	delete h;
	h = NULL;
}

template<class Type>
void binomialHeap<Type>::enqueue(const Type& x)
{
	node* tmp = new node(x);
	head = merge(head, tmp);
}

template<class Type>
bool binomialHeap<Type>::isEmpty()const
{
	return (head == NULL);
}

template<class Type>
Type binomialHeap<Type>::getHead()const
{
	return head->data;
}

template<class Type>
Type binomialHeap<Type>::getMin()const
{
		node* p = head;
		node* x = NULL;
		node* x_prev = NULL;
		node* p_prev = NULL;
		Type min;
		if (p == NULL)
			return -1;
		x = p;
		min = p->data;
		p_prev = p;
		p = p->sibling;
		while (p)
		{
			if (p->data < min)
			{
				x_prev = p_prev;
				x = p;
				min = p->data;
			}
			p_prev = p;
			p = p->sibling;
		}
		return x->data;
	}


	template<class Type>
	void binomialHeap<Type>::dequeue()
	{
		node* p = head;
		node* x = NULL;
		node* x_prev = NULL;
		node* p_prev = NULL;
		Type min;
		if (p == NULL)
			return;
		x = p;
		min = p->data;
		p_prev = p;
		p = p->sibling;
		while (p)
		{
			if (p->data < min)
			{
				x_prev = p_prev;
				x = p;
				min = p->data;
			}
			p_prev = p;
			p = p->sibling;
		}
		if (x == head)
		{
			head = x->sibling;
		}
		else
		{
			if (!x->sibling)
				x_prev->sibling = NULL;
			else
				x_prev->sibling = x->sibling;
		}

		node* child_x = x->child;
		if (child_x)
		{
			node* h1;
			h1 = child_x;
			p = child_x->sibling;
			child_x->sibling = NULL;
			while (p != NULL) {
				p_prev = p;
				p = p->sibling;
				p_prev->sibling = h1;
				h1 = p_prev;
			}
			head = merge(head, h1);
		}

	}

template<class Type>
void binomialHeap<Type>:: merge(node* other)
{
    merge(head,other);
}
