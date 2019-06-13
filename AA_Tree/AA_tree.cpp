#include "AA_tree.h"
#include<iostream>
using namespace std;
int main() {
	AA_tree<double> tree;
	for (double i = 0; i <= 1000; i+=1)
		tree.insert(i);
	for (double i = 100; i <= 1500; i += 1){
		cout << tree.search(i) << '\t';
	}
	system("Pause");
	return 0;
}