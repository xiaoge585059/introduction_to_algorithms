#pragma once

/**
 * @brief ����������� \n
 */
void set_random_seed();

/**
 * @brief ������� [0, 1) ֮��� double ֵ \n
 *
 * @return: double, [0, 1) ֮������������
 */
double random();


/**
 * @brief ������� [a, b) ֮���һ�� double ֵ \n
 *
 * @param a: double, ���ص���������½磨������
 * @param b: double, ���ص���������Ͻ磨��������
 * @return: double, [a, b) ֮������������
 */
double uniform(double a, double b);

/**
 * @brief ������� [0, N) ֮���һ�� int ֵ \n
 *
 * @param N: int, ���ص���������Ͻ죨��������
 * @return: int, [0, N) ֮����������
 */
int uniform(int N);

/* @brief ������� [lo, hi) ֮���һ�� int ֵ \n
 *
 * @param lo: int, ���ص���������½磨������
 * @param hi: int, ���ص���������Ͻ磨��������
 * @return: int, [a, b) ֮����������
 */
int uniform(int lo, int hi);

/**
 * @brief ������ɢ���ʷ��� int ֵ \n
 * ���� i �ĸ���Ϊ a[i]
 *
 * @param a: int[], i �ĸ��ʷֲ���a[] �и�Ԫ��֮�ͱ������ 1
 * @param a_len: int, ���� a �ĳ���
 * @return: int, ���� i �ĸ��ʷֲ�������� int ֵ����Χ [0, a_len)
 *   ����������Ϲ淶����ܷ��� -1
 */
int discrete(double a[], int a_len);

/**
 * @brief ����� double �����е�Ԫ�����д��� \n
 *
 * @param a: double[], ��Ҫ�������е����飨ԭ�ظı����飩
 * @param a_len, int, ���鳤��
 */
void shuffle(double a[], int a_len);
