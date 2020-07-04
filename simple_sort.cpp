
#include <iostream>
#include "tools.h"
using namespace std;

/**
 * @brief ������������ \n
 * �������ұ������飬����ǰԪ�ز���֮ǰ���ź��򲿷ֵ�ǡ��λ��
 *
 * @param a: int[], Ҫ��������飬ԭ������
 * @param a_len: int, ���鳤��
 */
void insertion_sort(int a[], int a_len) {
	// �ӵڶ���Ԫ�ؿ�ʼ��������
	for (int i = 1; i < a_len; ++i) {
		// ����ǰԪ�ز���֮ǰ�����򲿷ֵ�ǡ��λ��
		int current = a[i];
		int j = 0;
		for (j = i - 1; j >= 0 && current < a[j]; --j) {
			a[j + 1] = a[j];
		}
		a[j + 1] = current;
	}
}

/**
 * @brief ѡ���������� \n
 * �������������飬��δ��������ѡ����Сֵ���뵱ǰָ��Ԫ�ؽ���
 *
 * @param a: int[], Ҫ��������飬ԭ������
 * @param a_len: int, ���鳤��
 */
void selection_sort(int a[], int a_len) {
	int min_index = 0, min_value = 0;
	for (int i = 0; i != a_len - 1; ++i) {
		// ��δ�����������ҵ���СԪ�أ��뵱ǰԪ�ؽ���
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
 * @brief �鲢���������� \n
 * ����������������������������鲿�֣�������������飬���ν���С���������Ҵ���ԭ����
 * 
 * @param a: int[], ����������飬�� middle Ϊ���޷ֳ����������֣�
     ���������־����ź�����벿�ְ��� middle ����Ԫ�أ�
 * @param left: int, 
 * @param middle: int, 
 * @param right: int, 
 */
void merge(int a[], int left, int middle, int right) {
	int merge_len = right - left + 1;
	int n_left = middle - left + 1;
	int n_right = right - middle;

	// ��ʼ��������������
	int* a_left = new int[n_left] { 0 };
	int* a_right = new int[n_right] { 0 };
	for (int i = 0; i != n_left; ++i) {
		a_left[i] = a[i + left];
	}
	for (int i = 0; i != n_right; ++i) {
		a_right[i] = a[i + middle + 1];
	}

	// �ϲ������������� -> �µ��������飨�Ż����� a �У�
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
 * @brief �鲢�������� \n
 * ���η���
 *   1.�ֽ⣺��������� n ��Ԫ�ط�Ϊ����������
 *   2.�����ʹ�ù鲢����ݹ����������������
 *   3.�ϲ���ʹ�� merge �����ϲ������������������
 *
 * @param a: 
 * @param start: 
 * @param end: 
 */
void merge_sort(int a[], int start, int end) {
	if (start < end) {  // ���ֻ��һ�������Ԫ�أ���ֱ�ӷ��أ��ݹ���ֹ������
		int middle = (start + end) / 2;
		merge_sort(a, start, middle);
		merge_sort(a, middle + 1, end);
		merge(a, start, middle, end);
	}
}


/* ���� */
//*
int main() {
	const int a_len = 10;
	int a[a_len] = { 10, 1, 2, 7, 7, 6, 4, 5, 3, 9 };
	print_array(a, a_len, "����ǰ��");

	// insertion_sort(a, a_len);  // ���Բ�������
	// selection_sort(a, a_len);  // ����ѡ������
	/* ���Թ鲢����ĸ������� merge
	int m[8] = { 2, 4, 5, 7, 1, 2, 3, 6 };
	merge(m, 0, 3, 7);
	print_array<int>(m, 8);  //*/
	merge_sort(a, 0, 9);

	print_array<int>(a, a_len, "�����");

	return 0;
}  //*/
