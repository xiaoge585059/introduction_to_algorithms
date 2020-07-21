
#include <iostream>
#include "tools.h"
using namespace std;

/**
 * @brief �ҳ���Խ�е��������������� \n
 * find_maximum_subarray �����ĸ���������
 * �ҳ�������Χ�ڿ�Խ�е�ĺ���������������
 *
 * @param a: int[], Ҫ��������������Ŀ������
 * @param low: int, Ҫ���ҷ�Χ�������Ԫ�ص�����
 * @param mid: int, Ҫ���ҷ�Χ���м�Ԫ�ص�����
 * @param high: int, Ҫ���ҷ�Χ�����ұ�Ԫ�ص�����
 * @return: int[], ����һ����������Ԫ�ص��������飬
 *   ��һ��Ԫ���ǿ�Խ�е�����������������Ԫ��������
 *   �ڶ���Ԫ�����������������ұ�Ԫ��������
 *   ������Ԫ������������������Ԫ��֮�͡�
 */
int* find_max_crossing_subarray(int a[], int low, int mid, int high) {
	int left_sum = INT_MIN;
	int sum = 0;
	int max_left = 0;
	for (int i = mid; i >= low; --i) {  // �ҳ��е��������������飨�����е㣩
		sum = sum + a[i];
		if (sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = INT_MIN;
	sum = 0;
	int max_right = 0;
	for (int i = mid + 1; i <= high; ++i) {  // �ҳ��е����ҵ����������
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
 * @brief �ҳ������е�������������� \n
 * �÷��η��ҳ������е��������������
 *
 * @param a: int[], Ҫ��������������Ŀ������
 * @param low: int, Ҫ���ҷ�Χ�������Ԫ�ص�����
 * @param high: int, Ҫ���ҷ�Χ�����ұ�Ԫ�ص�����
 * @return: int[], ����һ����������Ԫ�ص��������飬
 *   ��һ��Ԫ�������������������Ԫ��������
 *   �ڶ���Ԫ�����������������ұ�Ԫ��������
 *   ������Ԫ������������������Ԫ��֮�͡�
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

/* ���� find_maximum_subarray ���� */
void test_find_maximum_subarray() {
	int a[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int* result1 = find_maximum_subarray(a, 0, 15);
	print_array(result1, 3);
	int b[5] = {-5, -1, -3, -4, -2};
	int* result2 = find_maximum_subarray(b, 0, 4);
	print_array(result2, 3);

	delete[] result1, result2;
}

/* �ҳ������е�������������飨�����㷨�� */
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

/* ���� find_maximum_subarray_by_brute_force ���� */
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
 * ���Ը��Ӷȵ�Ѱ�������е���������������㷨
 *
 * [0, i + 1] �е���������������� max{[0, i] �е��������������, Ԫ��֮������ [x, i + 1]}
 * Ҫȡ������ [x, i + 1]����
 *   ��� [x_previous, i] Ԫ��֮�� >= 0, �� [x, i + 1] ȡ [x_previous, i + 1]
 *   ��� [x_prevoius, i] Ԫ��֮�� < 0, �� [x, i + 1] ȡ [i + 1, i + 1]����ֻ�� i + 1 ������һ��Ԫ�أ�
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

/* ���� find_maximum_subarray_theta_n ���� */
void test_find_maximum_subarray_theta_n() {
	int a[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int* result1 = find_maximum_subarray_theta_n(a, 16);
	print_array(result1, 3);
	int b[5] = { -5, -1, -3, -4, -2 };
	int* result2 = find_maximum_subarray_theta_n(b, 5);
	print_array(result2, 3);

	delete[] result1, result2;
}


/* ���� */
/*
int main() {
	// test_find_maximum_subarray();
	// test_find_maximum_subarray_by_brute_force();
	test_find_maximum_subarray_theta_n();

	return 0;
}
//*/
