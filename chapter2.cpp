
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
 * @brief 归并排序辅助函数（升序） \n
 * 以两个新数组存入两个已排序数组部分，按序遍历两数组，依次将较小数从左至右存入原数组
 * 
 * @param a: int[], 需排序的数组，以 middle 为界限分成左右两部分，
     左右两部分均已排好序（左半部分包含 middle 索引元素）
 * @param left: int, 需排序部分最小的元素索引
 * @param middle: int, 需排序的两部分的分界，middle 索引包含于左半部分
 * @param right: int, 需排序部分最大的元素索引
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
			if (a_left[l_current] <= a_right[r_current]) {
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
 * @param a: 需要排序的数组
 * @param start: 需排序部分的最小索引
 * @param end: 需排序部分的最大索引
 */
void merge_sort(int a[], int start, int end) {
	if (start < end) {  // 如果只有一个或零个元素，则直接返回（递归终止条件）
		int middle = (start + end) / 2;
		merge_sort(a, start, middle);
		merge_sort(a, middle + 1, end);
		merge(a, start, middle, end);
	}
}

/**
 * @brief 二分查找法 \n
 * 从有序数组中查找元素时，只需与未比较部分中间的值进行比较，每次比较如果不相等则可以排除一半的元素
 *
 * @param key: int, 要查找的元素的值
 * @param a: int[], 从 a 数组中查找值
 * @param a_len: int, 数组 a 的长度
 * @return: int, 要查找的元素在数组中的索引
 *   如果元素不在数组中，则返回 -1
 */
int binary_search(int key, int a[], int a_len) {
	int left = 0, right = a_len;
	int middle = 0;
	while (left < right) {
		middle = (left + right) / 2;
		if (key > a[middle]) {
			left = middle + 1;
		} else if (key < a[middle]) {
			right = middle - 1;
		} else {
			return middle;
		}
	}

	return -1;
}

/**
 * @brief 查找集合中是否存在两个元素，它们的和为 x \n
 * 先对数组进行归并排序，再遍历数组，依次通过二分查找法查找是否存在元素，与当前元素之和为 x
 *
 * @param a: int[], 查找两个元素的目标数组
 * @param a_len: int, 数组长度
 * @param x: int, 是否存在两个元素之和为 x
 * @return: bool, 所需要找的两个元素是否存在
 *    存在返回 true, 否则返回 false
 */
bool find_sum_of_two_elements_is_x(int a[], int a_len, int x) {
	merge_sort(a, 0, a_len - 1);  // 先对数组进行排序，原地排序
	for (int i = 0; i != a_len - 1; ++i) {
		int x2 = x - a[i];
		if (x2 == a[i]) {  // 处理两个元素可能相等的情况
			return a[i + 1] == x2;
		}
		int result = -1;
		if (binary_search(x2, a, 10) != -1) {  // 查找对应的元素是否存在
			return true;
		}
	}
	return false;
}

/* 测试 test_find_sum_of_two_elements_is_x 函数 */
void test_find_sum_of_two_elements_is_x(int a[], int a_len) {
	cout << find_sum_of_two_elements_is_x(a, a_len, 5) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 100) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 10) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, -1) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 20) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 14) << endl;
}

/* 冒泡排序法 */
void bubble_sort(int a[], int a_len) {
	int temp = 0;
	for (int i = a_len - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}

/* count_inversions 函数的辅助函数(模仿归并排序) */
int merge_inversions(int a[], int left, int middle, int right) {
	int n_left = middle - left + 1;
	int n_right = right - middle;
	int* a_left = new int[n_left] { 0 };
	int* a_right = new int[n_right] { 0 };
	for (int i = 0; i != n_left; ++i) {
		a_left[i] = a[left + i];
	}
	for (int i = 0; i != n_right; ++i) {
		a_right[i] = a[middle + 1 + i];
	}

	int inversions = 0;
	int l_current = 0, r_current = 0;
	for (int i = left; i <= right; ++i) {
		if (l_current < n_left && r_current < n_right) {
			if (a_left[l_current] <= a_right[r_current]) {
				a[i] = a_left[l_current++];
			} else {
				a[i] = a_right[r_current++];
				inversions += n_left - l_current;
			}
		} else if (l_current < n_left) {
			a[i] = a_left[l_current++];
		} else {
			a[i] = a_right[r_current++];
		}
	}

	delete[] a_left, a_right;
	return inversions;
}

/* 数组中的逆序对数查询(同时会原地对其进行排序) */
int count_inversions(int a[], int left, int right) {
	int inversions = 0;
	if (left < right) {
		int middle = (left + right) / 2;
		int l_inversions = count_inversions(a, left, middle);
		int r_inversions = count_inversions(a, middle + 1, right);
		inversions = merge_inversions(a, left, middle, right) + l_inversions + r_inversions;
	}

	return inversions;
}

/* 测试 count_inversions */
void test_count_inversions() {
	int a[5] = {2, 3, 8, 6, 1};
	cout << count_inversions(a, 0, 4) << endl;
}


/* 测试 */
/*
int main() {
	const int a_len = 10;
	int a[a_len] = { 10, 1, 2, 7, 7, 6, 4, 5, 3, 9 };
	// print_array(a, a_len, "排序前：");

	// insertion_sort(a, a_len);  // 测试插入排序
	// selection_sort(a, a_len);  // 测试选择排序

	// 测试归并排序的辅助函数 merge
	// int m[8] = { 2, 4, 5, 7, 1, 2, 3, 6 };
	// merge(m, 0, 3, 7);
	// print_array<int>(m, 8);

	// merge_sort(a, 0, 9);  // 测试归并排序

	// print_array<int>(a, a_len, "排序后：");
	// cout << binary_search(7, a, a_len) << endl;
	// cout << binary_search(11, a, a_len) << endl;

	// test_find_sum_of_two_elements_is_x(a, a_len);  // 测试 test_find_sum_of_two_elements_is_x 函数

	// bubble_sort(a, a_len);  // 测试冒泡排序
	// print_array<int>(a, a_len, "排序后：");

	test_count_inversions();

	return 0;
}  //*/
