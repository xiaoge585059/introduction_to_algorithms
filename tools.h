#pragma once

#include <iostream>
using namespace std;

template <typename T>
void print_array(T a[], int a_len, string prompt = "") {
	if (prompt != "") {
		cout << prompt << endl;
	}
	for (int i = 0; i != a_len; ++i) {
		cout << a[i] << ' ';
	}
	cout << endl;
}
