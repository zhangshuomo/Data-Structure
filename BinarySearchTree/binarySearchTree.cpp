#include <iostream>
#include "binarySearchTree.h"
using namespace std;

int main()
{
	BinarySearchTree<int> bst;
	for (int i = 0; i < 17; ++i)
		bst.insert(i);
	for (int j = 1; j < 20; ++j) {
		cout << j << ':' << (bst.search(j) ? "True" : "False") << endl;
		bst.remove(j);
		cout << j << ':' << (bst.search(j) ? "True" : "False") << endl;
	}
	system("Pause");
	return 0;
}