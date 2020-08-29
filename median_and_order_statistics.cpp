
#include <iostream>
#include <utility>
#include "tools.h"
#include "my_random.h"
using namespace std;

/**
 * 同时找出无序数组中的最大值和最小值
 * 成对地取出元素，比较这两个元素，把其中较大的与当前最大值比较，较小的与当前最小值比较
 */
struct pair<int, int> find_max_and_min(int a[], int a_len) {
	pair<int, int> max_and_min(0, 0);
	int max = a[0], min = a[0];
	int i = 0;
	if ((a_len % 2) != 0) {  // 数组含有奇数个元素
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

/* 测试 find_max_and_min 函数 */
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
 * 将数组分为两部分，并返回分割数组的元素索引
 * 前半部分的元素都小于分割数组的元素，后半部分的元素都大于等于分割元素
 */
int partition2(int a[], int left, int right) {
	int x = a[right];  // 用于分割数组的比较元素(主元，pivot element)
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
 * 快速排序划分数组的随机化版本
 * 随机选取划分数组的元素（主元，pivot element）
 */
int randomized_partition2(int a[], int left, int right) {
	int r = uniform(left, right + 1);
	int temp = a[r];
	a[r] = a[right];
	a[right] = temp;

	return partition2(a, left, right);
}

/**
 * 在线性时间内找出第 order_i 小的元素
 * 假定 0 <= order_i <= right - left + 1
 */
int randomized_select(int a[], int left, int right, int order_i) {
	if (left == right) {  // 数组中只有一个元素，直接返回
		return a[left];
	}

	int pivot_position = randomized_partition2(a, left, right);
	// 分割后的左半部分元素数量（小于等于 a[pivot_position]）, 即 a[pivot_position] 是第 left_to_pivot_num 小的元素
	int left_to_pivot_num = pivot_position - left + 1;
	if (order_i == left_to_pivot_num) {
		return a[pivot_position];
	} else if (order_i < left_to_pivot_num) {
		return randomized_select(a, left, pivot_position - 1, order_i);
	} else {
		return randomized_select(a, pivot_position + 1, right, order_i - left_to_pivot_num);
	}
}

/* 测试 randomized_select 函数 */
void test_randomized_select() {
	int a[10] = { 2, 1, 3, 4, 6, 7, 5, 9, 8, 0 };
	print_array(a, 10);
	cout << randomized_select(a, 0, 9, 3) << endl;
	cout << randomized_select(a, 0, 9, 7) << endl;
}

/* 在线性时间内找出第 order_i 小的元素(非递归版本) */
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

/* 测试 randomized_select_without_recursion 函数 */
void test_randomized_select_without_recursion() {
	int a[10] = { 2, 1, 3, 4, 6, 7, 5, 9, 8, 0 };
	print_array(a, 10);
	cout << randomized_select_without_recursion(a, 0, 9, 3) << endl;
	cout << randomized_select_without_recursion(a, 0, 9, 7) << endl;
}


/* 测试 */
/*
int main() {
	// test_find_max_and_min();
	// test_randomized_select();
	test_randomized_select_without_recursion();

	return 0;
}
//*/

