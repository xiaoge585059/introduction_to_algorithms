
#include <iostream>
#include "tools.h"
using namespace std;

/**
 * @brief 插入排序（升序） \n
 * 从左至右遍历数组，将当前元素插入之前已排好序部分的恰当位置
 *
 * @param a: int[], 要排序的数组，原地排序
 * @param a_len: int, 数组长度
 */
void insertion_sort(int a[], int a_len) {
	// 从第二个元素开始遍历数组
	for (int i = 1; i < a_len; ++i) {
		// 将当前元素插入之前已排序部分的恰当位置
		int current = a[i];
		int j = 0;
		for (j = i - 1; j >= 0 && current < a[j]; --j) {
			a[j + 1] = a[j];
		}
		a[j + 1] = current;
	}
}

/**
 * @brief 选择排序（升序） \n
 * 遍历需排序数组，从未排序区域选择最小值，与当前指向元素交换
 *
 * @param a: int[], 要排序的数组，原地排序
 * @param a_len: int, 数组长度
 */
void selection_sort(int a[], int a_len) {
	int min_index = 0, min_value = 0;
	for (int i = 0; i != a_len - 1; ++i) {
		// 从未排序区域中找到最小元素，与当前元素交换
		min_index = i;
		min_value = a[i];
		for (int j = i + 1; j != a_len; ++j) {
			if (a[j] < min_value) {
				min_index = j;
				min_value = a[j];
			}
		}
		a[min_index] = a[i];
		a[i] = min_value;
	}
}

/**
 * @brief 归并排序辅助函数 \n
 * 以两个新数组存入两个已排序数组部分，按序遍历两数组，依次将较小数从左至右存入原数组
 * 
 * @param a: int[], 需排序的数组，以 middle 为界限分成左右两部分，
     左右两部分均已排好序（左半部分包含 middle 索引元素）
 * @param left: int, 
 * @param middle: int, 
 * @param right: int, 
 */
void merge(int a[], int left, int middle, int right) {
	int merge_len = right - left + 1;
	int n_left = middle - left + 1;
	int n_right = right - middle;

	// 初始化左右两个数组
	int* a_left = new int[n_left] { 0 };
	int* a_right = new int[n_right] { 0 };
	for (int i = 0; i != n_left; ++i) {
		a_left[i] = a[i + left];
	}
	for (int i = 0; i != n_right; ++i) {
		a_right[i] = a[i + middle + 1];
	}

	// 合并两个有序数组 -> 新的有序数组（放回数组 a 中）
	int l_current = 0, r_current = 0;
	for (int i = left; i <= right; ++i) {
		if (l_current < n_left && r_current < n_right) {
			if (a_left[l_current] < a_right[r_current]) {
				a[i] = a_left[l_current++];
			} else {
				a[i] = a_right[r_current++];
			}
		} else if (l_current == n_left) {
			a[i] = a_right[r_current++];
		} else {
			a[i] = a_left[l_current++];
		}
	}

	delete[] a_left, a_right;
}

/**
 * @brief 归并排序（升序） \n
 * 分治法：
 *   1.分解：将待排序的 n 个元素分为两个子序列
 *   2.解决：使用归并排序递归地排序两个子序列
 *   3.合并：使用 merge 函数合并两个已排序的子序列
 *
 * @param a: 
 * @param start: 
 * @param end: 
 */
void merge_sort(int a[], int start, int end) {
	if (start < end) {  // 如果只有一个或零个元素，则直接返回（递归终止条件）
		int middle = (start + end) / 2;
		merge_sort(a, start, middle);
		merge_sort(a, middle + 1, end);
		merge(a, start, middle, end);
	}
}


/* 测试 */
//*
int main() {
	const int a_len = 10;
	int a[a_len] = { 10, 1, 2, 7, 7, 6, 4, 5, 3, 9 };
	print_array(a, a_len, "排序前：");

	// insertion_sort(a, a_len);  // 测试插入排序
	// selection_sort(a, a_len);  // 测试选择排序
	/* 测试归并排序的辅助函数 merge
	int m[8] = { 2, 4, 5, 7, 1, 2, 3, 6 };
	merge(m, 0, 3, 7);
	print_array<int>(m, 8);  //*/
	merge_sort(a, 0, 9);

	print_array<int>(a, a_len, "排序后：");

	return 0;
}  //*/
