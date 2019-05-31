#ifndef LINK
#define LINK

#pragma once
#include "Stack.h"
template<class elemType>
class linkStack :public Stack<elemType>
{
private:
	struct Node {
		elemType x;
		Node* next;
		Node(elemType a,Node* p):x(a),next(p){}
		Node():next(NULL){}
	};
	Node* top;
	int size;
	void clear();
public:
	linkStack();
	void push(const elemType &x);
	elemType pop();
	bool isEmpty()const { return size == 0; }
	elemType showtop()const;
	~linkStack();
};

template<class elemType>
linkStack<elemType>::linkStack():top(nullptr),size(0) {}

template<class elemType>
void linkStack<elemType>::push(const elemType &x) {
	Node* p = new Node(x, top);
	top = p;
	++size;
}

template<class elemType>
elemType linkStack<elemType>::pop() {
	Node* tmp = top;
	elemType s = tmp->x;
	top = top->next;
	delete tmp;
	--size;
	return s;
}

template<class elemType>
elemType linkStack<elemType>::showtop()const{
	return top->x;
}

template<class elemType>
void linkStack<elemType>::clear() {
	Node* p = top;
	while (p != nullptr) {
		Node* q = p->next;
		delete p;
		p = q;
	}
}

template<class elemType>
linkStack<elemType>::~linkStack() { clear(); }
#endif // !LINK

