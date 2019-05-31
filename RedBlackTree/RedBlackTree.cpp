#include "RedBlackTree.h"
#include<iostream>
#include"linkStack.h"
using namespace std;
int main(int argc, char* argv) {
	RedBlackTree<int> tree;
	for (int i = 10001; i >= 5001; --i) {
		tree.insert(i);
		tree.insert(10001 - i);
	}
	return 0;
} 