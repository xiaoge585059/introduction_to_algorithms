
#include <iostream>
#include "tools.h"
#include "my_random.h"
using namespace std;

/**
 * 将数组分为两部分，并返回分割数组的元素索引
 * 前半部分的元素都小于分割数组的元素，后半部分的元素都大于等于分割元素
 */
int partition(int a[], int left, int right) {
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

/* 快速排序（升序） */
void quick_sort(int a[], int left, int right) {
	if (left < right) {
		int p = partition(a, left, right);
		quick_sort(a, left, p - 1);
		quick_sort(a, p + 1, right);
	}
}

/* 快速排序辅助函数 */
void quick_sort(int a[], int a_len) {
	quick_sort(a, 0, a_len - 1);
}

/* 测试 quick_sort 函数 */
void test_quick_sort() {
	int a[12] = { 13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11 };
	print_array(a, 12, "排序前：");
	quick_sort(a, 12);
	print_array(a, 12, "排序后：");
}

/**
 * 快速排序划分数组的随机化版本
 * 随机选取划分数组的元素（主元，pivot element）
 */
int randomized_partition(int a[], int left, int right) {
	int r = uniform(left, right + 1);
	int temp = a[r];
	a[r] = a[right];
	a[right] = temp;

	return partition(a, left, right);
}

/**
 * 快速排序的随机化版本
 * 随机选取划分数组的元素（主元，pivot element）
 */
void randomized_quick_sort(int a[], int left, int right) {
	if (left < right) {
		int p = randomized_partition(a, left, right);
		randomized_quick_sort(a, left, p - 1);
		randomized_quick_sort(a, p + 1, right);
	}
}

/* 快速排序的随机化版本的辅助函数 */
void randomized_quick_sort(int a[], int a_len) {
	randomized_quick_sort(a, 0, a_len - 1);
}

/* 测试 randomized_quick_sort 函数 */
void test_randomized_quick_sort() {
	int a[12] = { 13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11 };
	print_array(a, 12, "排序前：");
	randomized_quick_sort(a, 12);
	print_array(a, 12, "排序后：");
}


/* 测试 */
/*
int main() {
	// test_quick_sort();
	test_randomized_quick_sort();

	return 0;
}
//*/
