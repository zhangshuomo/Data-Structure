#pragma once
#ifndef RedBlack
#define RedBlack
#include "linkStack.h"
#include<iostream>
#include<assert.h>
using namespace std;

template <class type>
class RedBlackTree
{
private:
	enum color { black, red };
	struct Node {
		Node* left;
		Node* right;
		type data;
		color c;
		Node(type x,color c,Node* l,Node* r):data(x),c(c),left(l),right(r){}
		Node(type x):data(x),c(red),left(nullptr),right(nullptr){}
	};
	Node* root;
	enum state { pend, alter, fine };
	Node* rotation(Node* p, Node* pt) {
		assert(pt == p->left || pt == p->right);
		if(pt==p->left)
			if (pt->right != nullptr&&pt->right->c == red) {
				Node* grandson = pt->right;
				pt->right = grandson->left;
				p->left = grandson->right;
				grandson->left = pt;
				grandson->right = p;
				// modifying the color;
				grandson->c = p->c;
				p->c = pt->c;
				//
				return grandson;
			}
			else {
				p->left = pt->right;
				pt->right = p;
				//modifying the color
				color c = p->c;
				p->c = pt->c;
				pt->c = c;
				pt->left->c = pt->right->c;
				//
				return pt;
			}
		else
			if (pt->left != nullptr&&pt->left->c == red) {
				Node* grandson = pt->left;
				p->right = grandson->left;
				pt->left = grandson->right;
				grandson->left = p;
				grandson->right = pt;
				// modifying color
				grandson->c = p->c;
				p->c = pt->c;
				//
				return grandson;
			}
			else {
				p->right = pt->left;
				pt->left = p;
				//modifying color
				color c = p->c;
				p->c = pt->c;
				pt->c = c;
				pt->right->c = p->c;
				//
				return pt;
			}
	}
	bool search(const type &x, Node* p) const  {
		if (p == nullptr)
			return false;
		if (p->data == x)
			return true;
		if (p->data > x)
			return search(x, p->left);
		if (p->data < x)
			return search(x, p->right);
	}
	state insert(const type &x, Node* &p) {
		if (p == nullptr) {
			p = new Node(x);
			return pend;
		}
		if (x < p->data) {
			state s = insert(x, p->left);
			switch (s) {
			case pend:
				if (p->c == red)
					return alter;
				else
					return fine;
			case alter:
				if (p->right != nullptr && p->right->c == red) {
					p->right->c = black;
					p->left->c = black;
					p->c = red;
					return pend;
				}
				else{
					p = rotation(p, p->left);
					return fine;
					}
			case fine:
				return fine;
			}
		}
		if(x > p->data){
			state s = insert(x, p->right);
			switch (s) {
			case pend:
				if (p->c == red)
					return alter;
				else
					return fine;
			case alter:
				if (p->left != nullptr&&p->left->c == red) {
					p->left->c = black;
					p->right->c = black;
					p->c = red;
					return pend;
				}
				else {
					p = rotation(p, p->right);
					return fine;
				}
			case fine:
				return fine;
			}
		}
		if (x == p->data)
			return fine;

	}
	bool removeBlack(Node* &pt, Node* p, bool del) {
		assert(p == pt->left || p == pt->right);
		if (p == pt->left) {
			Node* another = pt->right;
			if (del) {
				Node* de = pt->left;
				pt->left = nullptr;
				delete de;
			}
			if (another->c == black) {
				if ((another->left != nullptr&&another->left->c == red) ||
					(another->right != nullptr&&another->right->c == red)){	// case(2),(3),(4)
					pt = rotation(pt, another);
					return true;
				}
				else {	// case(1)
					another->c = red;
					if (pt->c == red){
						pt->c = black;
						return true;
					}
					else{
						return false;
					}
				}
			}
			else {	// case(5)
				pt = rotation(pt, another);
				assert(pt->right->c == red);
				pt->right->c = black;
				return removeBlack(pt->left, pt->left->left, false);
				}
		}
		else {
			Node* another = pt->left;
			if (del) {
				Node* de = pt->right;
				pt->right = nullptr;
				delete de;
			}
			if (another->c == black) {
				if ((another->left != nullptr&&another->left->c == red) || 
					(another->right != nullptr&&another->right->c == red)) {
					pt = rotation(pt, another);
					return true;
				}
				else {
					another->c = red;
					if (pt->c == red) {
						pt->c = black;
						return true;
					}
					else {
						return false;
					}
				}
			}
			else {
				pt = rotation(pt, another);
				pt->left->c = black;
				return removeBlack(pt->right, pt->right->right, false);
			}
		}
	}

public:
	RedBlackTree():root(nullptr){}
	bool search(const type &x) const;
	void insert(const type &x);
	void remove(const type &x);
	~RedBlackTree();
};

template<class type>
void RedBlackTree<type>::insert(const type &x) {
	state s = insert(x, root);
	if (s == pend)
		root->c = black;
	if (s == alter)
		if (root->left->c == red)
			root = rotation(root, root->left);
		else
			root = rotation(root, root->right);
}

template<class type>
bool RedBlackTree<type>::search(const type &x) const {
	return search(x, root);
}

template<class type>
void RedBlackTree<type>::remove(const type &x) {
	linkStack<Node*> pointerStack;
	Node* pt = root;
	while (pt != nullptr && (*pt).data != x) {
		pointerStack.push(pt);
		if (pt->data < x)
			pt = pt->right;
		else
			pt = pt->left;
	}
	if (pt == nullptr) {
		cout << "No such element:" << x << endl;
		return;
	}
	pointerStack.push(pt);
	// 当前pt指向数据的是要删除的数据
	Node* p = pt->right;
	while (p != nullptr) {
		pointerStack.push(p);
		p = p->left;
	}
	// 当前p指向空结点
	p = pointerStack.pop();	// p指向的是要删除的替代结点
	pt->data = p->data;
	if (pointerStack.isEmpty()) {	// p（要删除的替代结点）就是根结点
		assert(p == root);
		root = p->left;
		if (root != nullptr)
			root->c = black;
		delete p;
		return;
	}
	// 回溯开始
	pt = pointerStack.pop();
	if (p == pt->left) {
		if (p->c == red) {
			pt->left = nullptr;
			delete p;
		}
		else {
			if (p->right != nullptr||p->left!=nullptr) {
				if(p->right!=nullptr){
					p->right->c = black;
					pt->left = p->right;
				}
				else {
					p->left->c = black;
					pt->left = p->left;
				}
				delete p;
			}
			else {
				bool deleteOrNot = true;
				bool end = false;
				while(!end){
					if(!pointerStack.isEmpty()){
						Node* pointer = pointerStack.pop();
						if (pt == pointer->left) {
							end = removeBlack(pt, p, deleteOrNot);
							pointer->left = pt;
						}
						else {
							end = removeBlack(pt, p, deleteOrNot);
							pointer->right = pt;
						}
						p = pt;
						pt = pointer;
						deleteOrNot = false;
					}
					else {	// pt就是根结点
						removeBlack(pt, p, deleteOrNot);
						root = pt;
						end = true;
					}
				}
			}

		}
	}
	else {
		if (p->c == red) {
			pt->right = nullptr;
			delete p;
		}
		else {
			if (p->right != nullptr||p->left!=nullptr) {
				if (p->right != nullptr) {
					p->right->c = black;
					pt->right = p->right;
				}
				else {
					p->left->c = black;
					pt->right = p->left;
				}
				delete p;
			}
			else {
				bool deleteOrNot = true;
				bool end = false;
				while (!end) {
					if(!pointerStack.isEmpty()){
						Node* pointer = pointerStack.pop();
						if (pt == pointer->left) {
							end = removeBlack(pt, p, deleteOrNot);
							pointer->left = pt;
						}
						else {
							end = removeBlack(pt, p, deleteOrNot);
							pointer->right = pt;
						}
						deleteOrNot = false;
						p = pt;
						pt = pointer;
					}
					else {
						removeBlack(pt, p, deleteOrNot);
						root = pt;
						end = true;
					}
				}
			}

		}
	}
}

template<class type>
RedBlackTree<type>::~RedBlackTree() {
	while (root != nullptr) {
		type x = root->data;
		remove(x);
	}
}

#endif