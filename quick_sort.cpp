
#include <iostream>
#include "tools.h"
#include "my_random.h"
using namespace std;

/**
 * �������Ϊ�����֣������طָ������Ԫ������
 * ǰ�벿�ֵ�Ԫ�ض�С�ڷָ������Ԫ�أ���벿�ֵ�Ԫ�ض����ڵ��ڷָ�Ԫ��
 */
int partition(int a[], int left, int right) {
	int x = a[right];  // ���ڷָ�����ıȽ�Ԫ��(��Ԫ��pivot element)
	int i = left - 1;
	int temp = 0;
	for (int j = left; j < right; ++j) {
		if (a[j] < x) {
			i += 1;
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	i += 1;
	a[right] = a[i];
	a[i] = x;

	return i;
}

/* ������������ */
void quick_sort(int a[], int left, int right) {
	if (left < right) {
		int p = partition(a, left, right);
		quick_sort(a, left, p - 1);
		quick_sort(a, p + 1, right);
	}
}

/* �������������� */
void quick_sort(int a[], int a_len) {
	quick_sort(a, 0, a_len - 1);
}

/* ���� quick_sort ���� */
void test_quick_sort() {
	int a[12] = { 13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11 };
	print_array(a, 12, "����ǰ��");
	quick_sort(a, 12);
	print_array(a, 12, "�����");
}

/**
 * �������򻮷������������汾
 * ���ѡȡ���������Ԫ�أ���Ԫ��pivot element��
 */
int randomized_partition(int a[], int left, int right) {
	int r = uniform(left, right + 1);
	int temp = a[r];
	a[r] = a[right];
	a[right] = temp;

	return partition(a, left, right);
}

/**
 * ���������������汾
 * ���ѡȡ���������Ԫ�أ���Ԫ��pivot element��
 */
void randomized_quick_sort(int a[], int left, int right) {
	if (left < right) {
		int p = randomized_partition(a, left, right);
		randomized_quick_sort(a, left, p - 1);
		randomized_quick_sort(a, p + 1, right);
	}
}

/* ���������������汾�ĸ������� */
void randomized_quick_sort(int a[], int a_len) {
	randomized_quick_sort(a, 0, a_len - 1);
}

/* ���� randomized_quick_sort ���� */
void test_randomized_quick_sort() {
	int a[12] = { 13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11 };
	print_array(a, 12, "����ǰ��");
	randomized_quick_sort(a, 12);
	print_array(a, 12, "�����");
}


/* ���� */
/*
int main() {
	// test_quick_sort();
	test_randomized_quick_sort();

	return 0;
}
//*/
