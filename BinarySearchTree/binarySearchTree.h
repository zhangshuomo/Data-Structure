#pragma once
#pragma once
#ifndef BST
#define BST
#include <iostream>
using namespace std;

template<class type>
class BinarySearchTree {
private:
	struct Node {
		type data;
		Node* left;
		Node* right;
		Node(const type &x) :data(x), left(nullptr), right(nullptr) {}
		Node(const type &x, Node* l, Node* r) :data(x), left(l), right(r) {}
	};
	Node* root;
	Node*& search(const type &x, Node* &p) const {
		if (p == nullptr || p->data == x) return p;
		else {
			if (p->data > x) return search(x, p->left);
			else return search(x, p->right);
		}
	}
	Node*& find_substitute(Node* &p) const {
		if (p->left == nullptr) return p;
		else return find_substitute(p->left);
	}

public:
	BinarySearchTree();
	bool search(const type &x) const;
	bool insert(const type &x);
	bool remove(const type &x);
	~BinarySearchTree();
};

template<class type>
BinarySearchTree<type>::BinarySearchTree() :root(nullptr) {}

template<class type>
bool BinarySearchTree<type>::search(const type &x)const {
	Node* p = root;				//  Why???
	Node* ptr = search(x, p);
	if (ptr == nullptr) return false;
	else return true;
}

template<class type>
bool BinarySearchTree<type>::insert(const type &x) {
	Node* &ptr = search(x, root);
	if (ptr == nullptr) {
		ptr = new Node(x);
		return true;
	}
	else {
		cout << "Element already exists." << endl;
		return false;
	}
}

template <class type>
bool BinarySearchTree<type>::remove(const type &x) {
	Node* &ptr = search(x, root);
	if (ptr == nullptr) {
		cout << "The element does not exist." << endl;
		return false;
	}
	Node* obj = ptr;
	if (ptr->right == nullptr)
		ptr = ptr->left;
	else
		if (ptr->left == nullptr)
			ptr = ptr->right;
		else {
			Node* &p = find_substitute(ptr->right);
			Node* np = p->right;
			p->left = ptr->left;
			p->right = ptr->right;
			ptr = p;
			p = np;
		}
		delete obj;
		return true;
}

template<class type>
BinarySearchTree<type>::~BinarySearchTree() {
	while (root != nullptr) {
		type x = root->data;
		remove(x);
	}
}
#endif