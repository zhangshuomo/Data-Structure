#include "AVL_tree.h"
#include <iostream>
using namespace std;
int main() {
	AVL<double> tree;
	for (double i = 1; i <= 10000; ++i) {
		tree.insert(i);
	}
	for (double j = 1; j <= 2000; ++j) {
		cout << tree.search(j) << endl;
	}
	// system("Pause");
	return 0;
}