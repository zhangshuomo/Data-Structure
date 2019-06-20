#include<iostream>
#include "sort.h"
using namespace std;

int main() {
	int a[] = { 77,-12,89,-45,40,27,11,6,7,100,54,0,40,-19 };
	heapSort(a, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << a[i] << '\t';
	cout << endl;
	//-------------------------------------------------------
	int b[] = { 77,-12,89,-45,40,27,11,6,7,100,54,0,40,-19 };
	quickSort(b, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << b[i] << '\t';
	cout << endl;
	//-------------------------------------------------------
	int c[] = { 77,-12,89,-45,40,27,11,6,7,100,54,0,40,-19 };
	mergeSort(c, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << c[i] << '\t';
	cout << endl;
	//-------------------------------------------------------
	int d[] = { 77,-12,89,-45,40,27,11,6,7,100,54,0,40,-19 };
	shellSort(d, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << d[i] << '\t';
	cout << endl;
	//-------------------------------------------------------
	system("Pause");
	return 0;
}