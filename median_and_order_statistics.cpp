
#include <iostream>
#include <utility>
#include "tools.h"
#include "my_random.h"
using namespace std;

/**
 * ͬʱ�ҳ����������е����ֵ����Сֵ
 * �ɶԵ�ȡ��Ԫ�أ��Ƚ�������Ԫ�أ������нϴ���뵱ǰ���ֵ�Ƚϣ���С���뵱ǰ��Сֵ�Ƚ�
 */
struct pair<int, int> find_max_and_min(int a[], int a_len) {
	pair<int, int> max_and_min(0, 0);
	int max = a[0], min = a[0];
	int i = 0;
	if ((a_len % 2) != 0) {  // ���麬��������Ԫ��
		i = 1;
	}

	int bigger = 0, smaller = 0;
	for (; i < a_len; i += 2) {
		if (a[i] < a[i + 1]) {
			smaller = a[i];
			bigger = a[i + 1];
		} else {
			smaller = a[i + 1];
			bigger = a[i];
		}

		if (smaller < min) {
			min = smaller;
		}
		if (bigger > max) {
			max = bigger;
		}
	}

	max_and_min.first = max;
	max_and_min.second = min;
	return max_and_min;
}

/* ���� find_max_and_min ���� */
void test_find_max_and_min() {
	int a1[10] = { 2, 1, 3, 4, 6, 7, 5, 9, 8, 0 };
	pair<int, int> p1 = find_max_and_min(a1, 10);
	int a2[9] = { 2, 1, 3, 4, 6, 7, 5, 9, 8 };
	pair<int, int> p2 = find_max_and_min(a2, 9);

	print_array(a1, 10, "a1: ");
	cout << "max: " << p1.first << ", min: " << p1.second << endl;
	print_array(a2, 9, "a1: ");
	cout << "max: " << p2.first << ", min: " << p2.second << endl;
}

/**
 * �������Ϊ�����֣������طָ������Ԫ������
 * ǰ�벿�ֵ�Ԫ�ض�С�ڷָ������Ԫ�أ���벿�ֵ�Ԫ�ض����ڵ��ڷָ�Ԫ��
 */
int partition2(int a[], int left, int right) {
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

/**
 * �������򻮷������������汾
 * ���ѡȡ���������Ԫ�أ���Ԫ��pivot element��
 */
int randomized_partition2(int a[], int left, int right) {
	int r = uniform(left, right + 1);
	int temp = a[r];
	a[r] = a[right];
	a[right] = temp;

	return partition2(a, left, right);
}

/**
 * ������ʱ�����ҳ��� order_i С��Ԫ��
 * �ٶ� 0 <= order_i <= right - left + 1
 */
int randomized_select(int a[], int left, int right, int order_i) {
	if (left == right) {  // ������ֻ��һ��Ԫ�أ�ֱ�ӷ���
		return a[left];
	}

	int pivot_position = randomized_partition2(a, left, right);
	// �ָ�����벿��Ԫ��������С�ڵ��� a[pivot_position]��, �� a[pivot_position] �ǵ� left_to_pivot_num С��Ԫ��
	int left_to_pivot_num = pivot_position - left + 1;
	if (order_i == left_to_pivot_num) {
		return a[pivot_position];
	} else if (order_i < left_to_pivot_num) {
		return randomized_select(a, left, pivot_position - 1, order_i);
	} else {
		return randomized_select(a, pivot_position + 1, right, order_i - left_to_pivot_num);
	}
}

/* ���� randomized_select ���� */
void test_randomized_select() {
	int a[10] = { 2, 1, 3, 4, 6, 7, 5, 9, 8, 0 };
	print_array(a, 10);
	cout << randomized_select(a, 0, 9, 3) << endl;
	cout << randomized_select(a, 0, 9, 7) << endl;
}

/* ������ʱ�����ҳ��� order_i С��Ԫ��(�ǵݹ�汾) */
int randomized_select_without_recursion(int a[], int left, int right, int order_i) {
	while (true) {
		if (left == right) {
			return a[left];
		}

		int pivot_position = randomized_partition2(a, left, right);
		int left_to_pivot_num = pivot_position - left + 1;
		if (order_i == left_to_pivot_num) {
			return a[pivot_position];
		} else if (order_i < left_to_pivot_num) {
			right = pivot_position - 1;
		} else {
			left = pivot_position + 1;
			order_i = order_i - left_to_pivot_num;
		}
	}
}

/* ���� randomized_select_without_recursion ���� */
void test_randomized_select_without_recursion() {
	int a[10] = { 2, 1, 3, 4, 6, 7, 5, 9, 8, 0 };
	print_array(a, 10);
	cout << randomized_select_without_recursion(a, 0, 9, 3) << endl;
	cout << randomized_select_without_recursion(a, 0, 9, 7) << endl;
}


/* ���� */
/*
int main() {
	// test_find_max_and_min();
	// test_randomized_select();
	test_randomized_select_without_recursion();

	return 0;
}
//*/

