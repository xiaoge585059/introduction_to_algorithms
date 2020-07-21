
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
 * @brief �鲢���������������� \n
 * ����������������������������鲿�֣�������������飬���ν���С���������Ҵ���ԭ����
 * 
 * @param a: int[], ����������飬�� middle Ϊ���޷ֳ����������֣�
     ���������־����ź�����벿�ְ��� middle ����Ԫ�أ�
 * @param left: int, �����򲿷���С��Ԫ������
 * @param middle: int, ������������ֵķֽ磬middle ������������벿��
 * @param right: int, �����򲿷�����Ԫ������
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
 * @brief �鲢�������� \n
 * ���η���
 *   1.�ֽ⣺��������� n ��Ԫ�ط�Ϊ����������
 *   2.�����ʹ�ù鲢����ݹ����������������
 *   3.�ϲ���ʹ�� merge �����ϲ������������������
 *
 * @param a: ��Ҫ���������
 * @param start: �����򲿷ֵ���С����
 * @param end: �����򲿷ֵ��������
 */
void merge_sort(int a[], int start, int end) {
	if (start < end) {  // ���ֻ��һ�������Ԫ�أ���ֱ�ӷ��أ��ݹ���ֹ������
		int middle = (start + end) / 2;
		merge_sort(a, start, middle);
		merge_sort(a, middle + 1, end);
		merge(a, start, middle, end);
	}
}

/**
 * @brief ���ֲ��ҷ� \n
 * �����������в���Ԫ��ʱ��ֻ����δ�Ƚϲ����м��ֵ���бȽϣ�ÿ�αȽ���������������ų�һ���Ԫ��
 *
 * @param key: int, Ҫ���ҵ�Ԫ�ص�ֵ
 * @param a: int[], �� a �����в���ֵ
 * @param a_len: int, ���� a �ĳ���
 * @return: int, Ҫ���ҵ�Ԫ���������е�����
 *   ���Ԫ�ز��������У��򷵻� -1
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
 * @brief ���Ҽ������Ƿ��������Ԫ�أ����ǵĺ�Ϊ x \n
 * �ȶ�������й鲢�����ٱ������飬����ͨ�����ֲ��ҷ������Ƿ����Ԫ�أ��뵱ǰԪ��֮��Ϊ x
 *
 * @param a: int[], ��������Ԫ�ص�Ŀ������
 * @param a_len: int, ���鳤��
 * @param x: int, �Ƿ��������Ԫ��֮��Ϊ x
 * @return: bool, ����Ҫ�ҵ�����Ԫ���Ƿ����
 *    ���ڷ��� true, ���򷵻� false
 */
bool find_sum_of_two_elements_is_x(int a[], int a_len, int x) {
	merge_sort(a, 0, a_len - 1);  // �ȶ������������ԭ������
	for (int i = 0; i != a_len - 1; ++i) {
		int x2 = x - a[i];
		if (x2 == a[i]) {  // ��������Ԫ�ؿ�����ȵ����
			return a[i + 1] == x2;
		}
		int result = -1;
		if (binary_search(x2, a, 10) != -1) {  // ���Ҷ�Ӧ��Ԫ���Ƿ����
			return true;
		}
	}
	return false;
}

/* ���� test_find_sum_of_two_elements_is_x ���� */
void test_find_sum_of_two_elements_is_x(int a[], int a_len) {
	cout << find_sum_of_two_elements_is_x(a, a_len, 5) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 100) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 10) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, -1) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 20) << endl;
	cout << find_sum_of_two_elements_is_x(a, a_len, 14) << endl;
}

/* ð������ */
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

/* count_inversions �����ĸ�������(ģ�¹鲢����) */
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

/* �����е����������ѯ(ͬʱ��ԭ�ض����������) */
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

/* ���� count_inversions */
void test_count_inversions() {
	int a[5] = {2, 3, 8, 6, 1};
	cout << count_inversions(a, 0, 4) << endl;
}


/* ���� */
/*
int main() {
	const int a_len = 10;
	int a[a_len] = { 10, 1, 2, 7, 7, 6, 4, 5, 3, 9 };
	// print_array(a, a_len, "����ǰ��");

	// insertion_sort(a, a_len);  // ���Բ�������
	// selection_sort(a, a_len);  // ����ѡ������

	// ���Թ鲢����ĸ������� merge
	// int m[8] = { 2, 4, 5, 7, 1, 2, 3, 6 };
	// merge(m, 0, 3, 7);
	// print_array<int>(m, 8);

	// merge_sort(a, 0, 9);  // ���Թ鲢����

	// print_array<int>(a, a_len, "�����");
	// cout << binary_search(7, a, a_len) << endl;
	// cout << binary_search(11, a, a_len) << endl;

	// test_find_sum_of_two_elements_is_x(a, a_len);  // ���� test_find_sum_of_two_elements_is_x ����

	// bubble_sort(a, a_len);  // ����ð������
	// print_array<int>(a, a_len, "�����");

	test_count_inversions();

	return 0;
}  //*/
