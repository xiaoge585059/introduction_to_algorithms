
#include <iostream>
#include "tools.h"
using namespace std;

/* ��ȡ����ĳ���ڵ� i �ĸ��ڵ㣨�ٶ� i ��Ϊ���ڵ㣬�� i > 0�� */
inline int parent(int i) {
	return ((i + 1) >> 1) - 1;  // ���Ʋ����൱�ڳ��� 2����Ч�ʱȳ�����
}

/* ��ȡ����ĳ���ڵ� i �����ӽڵ㣨�ٶ� i ������һλ������������� */
inline int left(int i) {
	return (i << 1) + 1;  // ���Ʋ����൱�ڳ��� 2����Ч�ʱȳ˷���
}

/* ��ȡ����ĳ���ڵ� i �����ӽڵ㣨�ٶ� i ������һλ������������� */
inline int right(int i) {
	return (i << 1) + 2;
}

/* ������������ parent, left, right */
void test_parent_child() {
	for (int i = 0; i < 5; ++i) {
		cout << "left child of " << i << ": " << left(i) << endl;
		cout << "parent of " << left(i) << ": " << parent(left(i)) << endl;
		cout << "right child of " << i << ": " << right(i) << endl;
		cout << "parent of " << right(i) << ": " << parent(right(i)) << endl;
		cout << endl;
	}
}

/**
 * ά�����ѵ����ʣ���ĳ���ڵ��ֵ���ڵ����������ӽڵ�
 * ���ĳ���ڵ����ӽڵ��н���������ά����Ӧ�ӽڵ����������
 */
void max_heapify(int a[], int heap_size, int node_i) {
	int i = -1;
	int l = 0, r = 0;
	int largest = node_i;
	int temp = 0;
	while (i != largest) {
		i = largest;  // ��һ��ѭ����ʱ�� i ȡֵΪ node_i
		l = left(i);
		r = right(i);
		if (l < heap_size && a[l] > a[i]) {
			largest = l;
		}
		if (r < heap_size && a[r] > a[largest]) {
			largest = r;
		}

		// ȷ�����ڵ���������ӽڵ�
		if (i != largest) {
			temp = a[i];
			a[i] = a[largest];
			a[largest] = temp;
		}
	}
}

/**
 * �������Ͻ�������
 * Ҷ�ӽڵ���ֻ��һ���ڵ��������Ȼ������
 * ��Ҷ�ӽڵ㿪ʼ����ڵ�һ��㽨������
 */
void build_max_heap(int a[], int a_len) {
	int heap_size = a_len;  // �ѵĴ�С��һ�������鳤��
	for (int i = heap_size / 2 - 1; i >= 0; --i) {
		max_heapify(a, heap_size, i);
	}
}

/**
 * �������㷨������
 *   1.�������ѣ����ѵĸ�Ԫ��Ϊ��������Ԫ�أ�
 *   2.�����ѵĸ��ڵ������һ���ڵ㽻��������ӵ�еĽڵ�����һ�����½�������
 *   3.�ظ��� 2 ����ֱ����ֻ��һ���ڵ㣬�㷨�������
 */
void heap_sort(int a[], int a_len) {
	build_max_heap(a, a_len);

	int heap_size = a_len;
	int temp = 0;
	for (int i = a_len - 1; i >= 1; --i) {
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		heap_size -= 1;
		max_heapify(a, heap_size, 0);  // �ָ���������
	}
}

/* ���� heap_sort ���� */
void test_heap_sort() {
	int a[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	print_array(a, 10);
	heap_sort(a, 10);
	print_array(a, 10);
}

/* ��ȡ�����е����ֵ�������ѵ�һ��Ԫ�� */
int heap_maximum(int a[], int heap_size) {
	return a[0];
}

/* ��ȡ�����е����ֵ���������������ȡ��, heap_size ��һ */
int heap_extract_max(int a[], int heap_size) {
	if (heap_size < 1) {
		return INT_MIN;  // �˴�Ӧ�ñ���"heap underflow"
	}

	int max = a[0];
	a[0] = a[heap_size - 1];
	max_heapify(a, heap_size - 1, 0);

	return max;
}

/* ������ i �ڵ��ֵ����Ϊ key(key ������ڵ��� i �ڵ�ԭ�ȵ�ֵ����ά�����ѵ�����) */
void heap_increase_key(int a[], int i, int key) {
	if (key < a[i]) {
		return;  // �˴�Ӧ����"new key is smaller than current key"
	}

	a[i] = key;
	int temp = 0;
	/*
	while (i > 0 && a[parent(i)] < a[i]) {
		temp = a[i];
		a[i] = a[parent(i)];
		a[parent(i)] = temp;

		i = parent(i);
	} */

	// ����Ч�����Ԫ�ؽ�������
	while (i > 0 && a[parent(i)] < key) {
		a[i] = a[parent(i)];
		i = parent(i);
	}
	a[i] = key;
}

/* �� key ֵ�������ѣ��ѵ�Ԫ������һ����ά���������� */
void max_heap_insert(int a[], int heap_size, int key) {
	heap_size += 1;
	a[heap_size - 1] = INT_MIN;
	heap_increase_key(a, heap_size - 1, key);
}

/* ��������ɾ�� i �ڵ㣬��ά���������ʣ��� heap_size ��һ */
void heap_delete(int a[], int heap_size, int i) {
	if (a[i] > a[heap_size - 1]) {
		a[i] = a[heap_size - 1];
		max_heapify(a, heap_size, i);
	} else {
		heap_increase_key(a, i, a[heap_size - 1]);
	}

	// heap_size -= 1;
}

/* �������ȶ��е���غ��� */
void test_priority_queue() {
	int a[11] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1, 0 };
	int heap_size = 10;
	print_array(a, heap_size, "ԭ���ѣ�");
	heap_increase_key(a, 8, 15);
	print_array(a, heap_size, "�� a[8] �ڵ����ӵ� 15 ��");
	max_heap_insert(a, 10, 13);
	heap_size += 1;
	print_array(a, heap_size, "��ֵΪ 13 �Ľڵ���뵽���Ѻ�");
	int max = heap_extract_max(a, heap_size);
	heap_size -= 1;
	print_array(a, heap_size, "�����������ֵ�Ƴ���");
	cout << "���ֵΪ��" << max << endl;

	cout << endl << "delete: " << endl;
	int b[7] = { 15, 7, 9, 1, 2, 3, 8 };
	int heap_size_b = 7;
	print_array(b, heap_size_b, "ԭ���ѣ�");
	heap_delete(a, heap_size_b, 4);
	heap_size_b -= 1;
	print_array(b, heap_size_b, "ɾ���� 5 ��Ԫ�غ�");
}


/* ���� */
/*
int main() {
	// test_parent_child();
	// test_heap_sort();
	test_priority_queue();

	return 0;
}
//*/
