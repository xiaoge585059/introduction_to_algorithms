
#include <iostream>
#include "tools.h"
using namespace std;

/**
 * @brief 找出跨越中点的最大连续子数组 \n
 * find_maximum_subarray 函数的辅助函数，
 * 找出给定范围内跨越中点的和最大的连续子数组
 *
 * @param a: int[], 要查找最大子数组的目标数组
 * @param low: int, 要查找范围的最左边元素的索引
 * @param mid: int, 要查找范围的中间元素的索引
 * @param high: int, 要查找范围的最右边元素的索引
 * @return: int[], 返回一个包含三个元素的整型数组，
 *   第一个元素是跨越中点的最大子数组的最左边元素索引，
 *   第二个元素是这个子数组的最右边元素索引，
 *   第三个元素是这个子数组的所有元素之和。
 */
int* find_max_crossing_subarray(int a[], int low, int mid, int high) {
	int left_sum = INT_MIN;
	int sum = 0;
	int max_left = 0;
	for (int i = mid; i >= low; --i) {  // 找出中点往左的最大子数组（包含中点）
		sum = sum + a[i];
		if (sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = INT_MIN;
	sum = 0;
	int max_right = 0;
	for (int i = mid + 1; i <= high; ++i) {  // 找出中点往右的最大子数组
		sum = sum + a[i];
		if (sum > right_sum) {
			right_sum = sum;
			max_right = i;
		}
	}

	int* result = new int[3]{ max_left, max_right, left_sum + right_sum };
	return result;
}

/**
 * @brief 找出数组中的最大连续子数组 \n
 * 用分治法找出数组中的最大连续子数组
 *
 * @param a: int[], 要查找最大子数组的目标数组
 * @param low: int, 要查找范围的最左边元素的索引
 * @param high: int, 要查找范围的最右边元素的索引
 * @return: int[], 返回一个包含三个元素的整型数组，
 *   第一个元素是最大子数组的最左边元素索引，
 *   第二个元素是最大子数组的最右边元素索引，
 *   第三个元素是最大子数组的所有元素之和。
 */
int* find_maximum_subarray(int a[], int low, int high) {
	if (low == high) {  // base case: only one element
		int* result = new int[3]{ low, high, a[low] };
		return result;
	} else {
		int mid = (low + high) / 2;
		int* left_result = find_maximum_subarray(a, low, mid);
		int* right_result = find_maximum_subarray(a, mid + 1, high);
		int* cross_result = find_max_crossing_subarray(a, low, mid, high);

		if (left_result[2] >= right_result[2] && left_result[2] >= cross_result[2]) {
			delete[] right_result, cross_result;
			return left_result;
		} else if (right_result[2] >= left_result[2] && right_result[2] >= cross_result[2]) {
			delete[] left_result, cross_result;
			return right_result;
		} else {
			delete[] left_result, right_result;
			return cross_result;
		}
	}
}

/* 测试 find_maximum_subarray 函数 */
void test_find_maximum_subarray() {
	int a[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int* result1 = find_maximum_subarray(a, 0, 15);
	print_array(result1, 3);
	int b[5] = {-5, -1, -3, -4, -2};
	int* result2 = find_maximum_subarray(b, 0, 4);
	print_array(result2, 3);

	delete[] result1, result2;
}

/* 找出数组中的最大连续子数组（暴力算法） */
int* find_maximum_subarray_by_brute_force(int a[], int a_len) {
	int max_sum = INT_MIN;
	int sum = 0;
	int low = 0, high = 0;
	for (int i = 0; i < a_len; ++i) {
		sum = 0;
		for (int j = i; j < a_len; ++j) {
			sum += a[j];
			if (sum > max_sum) {
				max_sum = sum;
				low = i;
				high = j;
			}
		}
	}

	int* result = new int[3]{ low, high, max_sum };
	return result;
}

/* 测试 find_maximum_subarray_by_brute_force 函数 */
void test_find_maximum_subarray_by_brute_force() {
	int a[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int* result1 = find_maximum_subarray_by_brute_force(a, 16);
	print_array(result1, 3);
	int b[5] = { -5, -1, -3, -4, -2 };
	int* result2 = find_maximum_subarray_by_brute_force(b, 5);
	print_array(result2, 3);

	delete[] result1, result2;
}

/**
 * 线性复杂度的寻找数组中的最大连续子数组算法
 *
 * [0, i + 1] 中的最大连续子数组是 max{[0, i] 中的最大连续子数组, 元素之和最大的 [x, i + 1]}
 * 要取得最大的 [x, i + 1]，则
 *   如果 [x_previous, i] 元素之和 >= 0, 则 [x, i + 1] 取 [x_previous, i + 1]
 *   如果 [x_prevoius, i] 元素之和 < 0, 则 [x, i + 1] 取 [i + 1, i + 1]（即只有 i + 1 索引的一个元素）
 */
int* find_maximum_subarray_theta_n(int a[], int a_len) {
	int max_sum = INT_MIN;
	int low = 0, high = 0;
	int current_low = 0, current_high = 0;
	int sum = INT_MIN;
	for (int i = 0; i < a_len; ++i) {
		current_high = i;
		if (sum > 0) {
			sum += a[i];
		} else {
			current_low = i;
			sum = a[i];
		}

		if (sum > max_sum) {
			max_sum = sum;
			low = current_low;
			high = current_high;
		}
	}

	int* result = new int[3]{ low, high, max_sum };
	return result;
}

/* 测试 find_maximum_subarray_theta_n 函数 */
void test_find_maximum_subarray_theta_n() {
	int a[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int* result1 = find_maximum_subarray_theta_n(a, 16);
	print_array(result1, 3);
	int b[5] = { -5, -1, -3, -4, -2 };
	int* result2 = find_maximum_subarray_theta_n(b, 5);
	print_array(result2, 3);

	delete[] result1, result2;
}


/* 测试 */
/*
int main() {
	// test_find_maximum_subarray();
	// test_find_maximum_subarray_by_brute_force();
	test_find_maximum_subarray_theta_n();

	return 0;
}
//*/
