#ifndef STACK
#define STACK
#pragma once
template<class elemType>
class Stack
{
public:
	virtual void push(const elemType &x) = 0;
	virtual elemType pop() = 0;
	virtual bool isEmpty()const = 0;
	virtual elemType showtop()const = 0;
	virtual ~Stack() {};
};
#endif // !STACK

