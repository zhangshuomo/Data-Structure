#pragma once
#ifndef AVL_tree
#define AVL_tree
#include<iostream>
#include<assert.h>
using namespace std;

template<class type>
class AVL {
private:
	struct Node {
		type data;
		Node* left;
		Node* right;
		int balence_factor;
		Node(const type &x):data(x),left(nullptr), right(nullptr), balence_factor(0) {}
		Node(const type &x, Node* l, Node r, int b):data(x), left(l), right(r), balence_factor(b) {}
	};
	Node* root;
	Node* search(const type &x, Node* p)const {
		if (p == nullptr || p->data == x)
			return p;
		if (p->data > x)
			return search(x, p->left);
		if (p->data < x)
			return search(x, p->right);
	}
	Node* rotation(Node* p) {
		if (p->balence_factor == -2) {	
			Node* right_son = p->right;
			switch(right_son->balence_factor){
			case -1:	// RR单旋转
				p->right = p->right->left;
				right_son->left = p;
				right_son->balence_factor = 0;
				p->balence_factor = 0;
				return right_son;
			case 0:	// RR单旋转，只有删除时才出现的情况
				p->right = right_son->left;
				right_son->left = p;
				p->balence_factor = -1;
				right_son->balence_factor = 1;
				return right_son;
			case 1:	// RL双旋转
				Node* grandson = right_son->left;
				p->right = grandson->left;
				right_son->left = grandson->right;
				grandson->left = p;
				grandson->right = right_son;
				switch (grandson->balence_factor) {
				case 1:
					grandson->balence_factor = 0;
					p->balence_factor = 0;
					right_son->balence_factor = -1;
					break;
				case 0: 
					grandson->balence_factor = p->balence_factor = right_son->balence_factor = 0;
					break;
				case -1:
					grandson->balence_factor = 0;
					p->balence_factor = 1;
					right_son->balence_factor = 0;
					break;
				}
				return grandson;
			}
		}
		else {
			Node* left_son = p->left;
			switch(left_son->balence_factor){
			case 1: 	// LL单旋转
				p->left = left_son->right;
				left_son->right = p;
				p->balence_factor = 0;
				left_son->balence_factor = 0;
				return left_son;
			case 0:		//LL单旋转，只在删除时出现
				p->left = left_son->right;
				left_son->right = p;
				left_son->balence_factor = -1;
				p->balence_factor = 1;
				return left_son;
			case -1:	// LR双旋转
				Node* grandson = left_son->right;
				left_son->right = grandson->left;
				p->left = grandson->right;
				grandson->left = left_son;
				grandson->right = p;
				switch(grandson->balence_factor){
				case 1: 
					grandson->balence_factor = 0;
					left_son->balence_factor = 0;
					p->balence_factor = -1;
					break;
				case 0:	
					grandson->balence_factor = left_son->balence_factor = p->balence_factor = 0;
					break;
				case -1:
					grandson->balence_factor = 0;
					left_son->balence_factor = 1;
					p->balence_factor = 0;
					break;
				}
				return grandson;
			}
		}
	}
	int insert(Node* n, Node* p) {
		if (p->data > n->data && p->left == nullptr) {
			p->left = n;
			if (p->right == nullptr) {
				p->balence_factor = 1;
				return 1;
			}
			else {
				p->balence_factor = 0;
				return 0;
			}
		}
		if (p->data < n->data && p->right == nullptr) {
			p->right = n;
			if (p->left == nullptr) {
				p->balence_factor = -1;
				return -1;
			}
			else {
				p->balence_factor = 0;
				return 0;
			}
		}
		if (p->data > n->data) {
			int x = insert(n, p->left);
			switch(x) {
			case 1: case -1:
					p->balence_factor += 1;
					return p->balence_factor;
			case 2: case -2:
					p->left = rotation(p->left);
			case 0:
					return 0;
			}
		}
		if (p->data < n->data) {
				int x = insert(n, p->right);
				switch(x) {
				case 1: case -1:
					p->balence_factor -= 1;
					return p->balence_factor;
				case 2: case -2:
					p->right = rotation(p->right);
				case 0:
					return 0;
				}
		}
		if (p->data == n->data)
			return 0;
}
	int delete_substitute(Node* &p, type &s) {
		assert(p != nullptr);	// 要保证p不是空指针
		if (p->left != nullptr) {
			if(p->left->left == nullptr){
				Node* substitute = p->left;
				s = substitute->data;
				p->left = substitute->right;
				delete substitute;
				p->balence_factor -= 1;
				return p->balence_factor;
			}
			else {
				int i = delete_substitute(p->left, s);
				switch (i) {
				case -1:
					return i;
				case -2:
					p->left = rotation(p->left);
					if (p->left->balence_factor != 0)//在情况（1）下停止调整
						return -1;
				case 0:	//包含case -2 时的第（2）（3）种情况
					p->balence_factor -= 1;
					return p->balence_factor;
				}
			}
		}
		else {
				Node* substitute = p;
				s = substitute->data;
				p = p->right;
				delete substitute;
				return 0;	//告诉上一层，自己的高度减少了1
		}
	}
	int remove(const type &x, Node* &p) {
		if (p == nullptr){
			cout << "No element: "<<x<<'!'<< endl;
			return -1;
		}
		if (p->data == x && p->right != nullptr) {
			type y;
			int i = delete_substitute(p->right, y);
			p->data = y;
			switch (i) {
			case -1:
				return -1;
			case -2:
				p->right = rotation(p->right);
				if (p->right->balence_factor != 0)	//在情况（1）下停止调整
					return -1;
			case 0:
				p->balence_factor += 1;
				return p->balence_factor;
			}
		}
		if (p->data == x && p->right == nullptr) {
			Node* s = p;
			p = p->left;
			delete s;
			return 0;
		}
		if (p->data > x) {
			int i = remove(x, p->left);
			switch(i){
			case -1:case 1:
				return i;
			case -2:case 2:
				p->left = rotation(p->left);
				if (p->left->balence_factor != 0)	//在情况（1）下停止调整
					return -1;
			case 0:
				p->balence_factor -= 1;
				return p->balence_factor;
			}
		}
		if (p->data < x) {
			int i = remove(x, p->right);
			switch(i){
			case -1:case 1:
				return i;
			case -2:case 2:
				p->right = rotation(p->right);
				if (p->right->balence_factor != 0)
					return 1;
			case 0:
				p->balence_factor += 1;
				return p->balence_factor;
			}
		}
	}
public:
	AVL():root(nullptr){}
	void insert(const type &x);
	bool search(const type &x) const;
	void remove(const type &x);
	~AVL();
};

template<class type>
void AVL<type>::insert(const type &x) {
	Node* n = new Node(x);
	if (root == nullptr)
		root = n;
	else{
		int x = insert(n, root);
		if (x == -2 || x == 2)
			root = rotation(root);
	}
}

template<class type>
bool AVL<type>::search(const type &x) const{
	Node* p = search(x, this->root);
	return p != nullptr;
}

template<class type>
void AVL<type>::remove(const type &x) {
	int i = remove(x, root);
	if (i == 2 || i == -2) {
		root = rotation(root);
	}
}

template<class type>
AVL<type>::~AVL() {
	while (root != nullptr) {
		remove(root->data);
	}
}
#endif