#pragma once
#ifndef AATREE
#define AATREE
#include<assert.h>
#include<iostream>
using namespace std;
template<class type>
class AA_tree
{
private:
	struct Node {
		type data;
		Node* left;
		Node* right;
		int level;
		Node(const type &x):data(x),left(nullptr),right(nullptr),level(1){}
	};
	Node* root;
	bool search(const type &x, Node* p) const {
		if (p == nullptr)
			return false;
		if (x == p->data)
			return true;
		else {
			if (x < p->data)
				return search(x, p->left);
			else
				return search(x, p->right);
		}
	}
	Node* LL(Node* p) {
		assert(p->left != nullptr&&p->left->level == p->level);
		Node* l = p->left;
		p->left = l->right;
		l->right = p;
		return l;
	}
	Node* RR(Node* p) {
		assert(p->right != nullptr&&p->right->right != nullptr&&p->right->level == p->right->right->level&&p->right->level == p->level);
		Node* r = p->right;
		p->right = r->left;
		r->left = p;
		r->level += 1;
		return r;
	}
	void insert(const type &x, Node* &p) {
		if (p == nullptr) {
			p = new Node(x);
			return;
		}
		if (x < p->data) {
			insert(x, p->left);
			if (p->left->level == p->level) {
				p = LL(p);
				if (p->right != nullptr&&p->right->right != nullptr&&p->right->level == p->right->right->level&&p->right->level == p->level) {
					p = RR(p);
				}
			}
		}
		if (x > p->data) {
			insert(x, p->right);
			if (p->right->right != nullptr&&p->right->level == p->right->right->level&&p->right->level == p->level) {
				p = RR(p);
			}
		}
	
	}
	int remove(const type &x, Node* &p) {
		if (p == nullptr) {
			cout << "No element:\t" << x << endl;
			return -1;
		}
		if (x < p->data) { 
			if (p->level - remove(x, p->left) == 2) {
				if (p->level > p->right->level) {
					p->level -= 1;
					if (p->right->right != nullptr&&p->right->level == p->right->right->level)
						p = RR(p);
				}
				else {
					p->level -= 1;
					p->right->level -= 1;
					p->right = LL(p->right);
					if (p->right->right->left != nullptr&&p->right->right->left->level == p->right->right->level)
						p->right->right = LL(p->right->right);
					p = RR(p);
					if (p->right->right->right != nullptr&&p->right->right->right->level == p->right->level)
						p->right = RR(p->right);
				}
			}
			return p->level;
		}
		else
			if (x > p->data) { 
				if (p->level - remove(x, p->right) == 2) {
					p->level -= 1;
					p = LL(p);
					if (p->right->left != nullptr&&p->right->left->level == p->right->level) {
						p->right = LL(p->right);
						p = RR(p);
					}
				}
				return p->level;
			}
			else {
				if (p->left != nullptr) {	// level != 1
					Node* pt = p->left;
					while (pt->right != nullptr)
						pt = pt->right;
					p->data = pt->data;
					if (p->level - remove(p->data, p->left) == 2) {
						if (p->level > p->right->level) {
							p->level -= 1;
							if (p->right->right != nullptr&&p->right->level == p->right->right->level)
								p = RR(p);
						}
						else {
							p->level -= 1;
							p->right->level -= 1;
							p->right = LL(p->right);
							if (p->right->right->left != nullptr&&p->right->right->left->level == p->right->right->level)
								p->right->right = LL(p->right->right);
							p = RR(p);
							if (p->right->right->right != nullptr&&p->right->right->right->level == p->right->level)
								p->right = RR(p->right);
						}
					}
					return p->level;
				}
				else {						// level == 1
					Node* pt = p;
					p = p->right;
					delete pt;
					return 0;
				}
			}
	}
public:
	AA_tree():root(nullptr){}
	bool search(const type &x) const;
	void remove(const type &x);
	void insert(const type &x);
	~AA_tree();
};

template<class type>
bool AA_tree<type>::search(const type &x) const {
	return search(x, root);
}

template<class type>
void AA_tree<type>::insert(const type &x) {
	insert(x, root);
}

template<class type>
void AA_tree<type>::remove(const type &x) {
	remove(x, root);
}

template<class type>
AA_tree<type>::~AA_tree() {
	while (root != nullptr)
		remove(root->data);
}
#endif // !AATREE