
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief ����������� \n
 */
void set_random_seed() {
	srand((int)time(0));
}

/**
 * @brief ������� [0, 1) ֮��� double ֵ \n
 *
 * @return: double, [0, 1) ֮������������
 */
double random() {
	return rand() / (double)(RAND_MAX + 1);
}

/**
 * @brief ������� [a, b) ֮���һ�� double ֵ \n
 *
 * @param a: double, ���ص���������½磨������
 * @param b: double, ���ص���������Ͻ磨��������
 * @return: double, [a, b) ֮������������
 */
double uniform(double a, double b) {
	return a + random() * (b - a);
}

/**
 * @brief ������� [0, N) ֮���һ�� int ֵ \n
 *
 * @param N: int, ���ص���������Ͻ죨��������
 * @return: int, [0, N) ֮����������
 */
int uniform(int N) {
	return (int)(random() * N);
}

/* @brief ������� [lo, hi) ֮���һ�� int ֵ \n
 *
 * @param lo: int, ���ص���������½磨������
 * @param hi: int, ���ص���������Ͻ磨��������
 * @return: int, [a, b) ֮����������
 */
int uniform(int lo, int hi) {
	return lo + uniform(hi - lo);
}

/**
 * @brief ������ɢ���ʷ��� int ֵ \n
 * ���� i �ĸ���Ϊ a[i]
 *
 * @param a: int[], i �ĸ��ʷֲ���a[] �и�Ԫ��֮�ͱ������ 1
 * @param a_len: int, ���� a �ĳ���
 * @return: int, ���� i �ĸ��ʷֲ�������� int ֵ����Χ [0, a_len)
 *   ����������Ϲ淶����ܷ��� -1
 */
int discrete(double a[], int a_len) {
	double r = random();
	double sum = 0.0;
	for (int i = 0; i < a_len; ++i) {
		sum = sum + a[i];
		if (sum >= r) return i;
	}

	return -1;
}

/**
 * @brief ����� double �����е�Ԫ�����д��� \n
 *
 * @param a: double[], ��Ҫ�������е����飨ԭ�ظı����飩
 * @param a_len, int, ���鳤��
 */
void shuffle(double a[], int a_len) {
	for (int i = 0; i < a_len; ++i) {
		// �� a[i] �� a[i..a_len-1] ������һ��Ԫ�ؽ���
		int r = i + uniform(a_len - i);
		double temp = a[i];
		a[i] = a[r];
		a[r] = temp;
	}
}
