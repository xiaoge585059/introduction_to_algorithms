
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief 重置随机种子 \n
 */
void set_random_seed() {
	srand((int)time(0));
}

/**
 * @brief 随机返回 [0, 1) 之间的 double 值 \n
 *
 * @return: double, [0, 1) 之间的随机浮点数
 */
double random() {
	return rand() / (double)(RAND_MAX + 1);
}

/**
 * @brief 随机返回 [a, b) 之间的一个 double 值 \n
 *
 * @param a: double, 返回的随机数的下界（包含）
 * @param b: double, 返回的随机数的上界（不包含）
 * @return: double, [a, b) 之间的随机浮点数
 */
double uniform(double a, double b) {
	return a + random() * (b - a);
}

/**
 * @brief 随机返回 [0, N) 之间的一个 int 值 \n
 *
 * @param N: int, 返回的随机数的上届（不包含）
 * @return: int, [0, N) 之间的随机整数
 */
int uniform(int N) {
	return (int)(random() * N);
}

/* @brief 随机返回 [lo, hi) 之间的一个 int 值 \n
 *
 * @param lo: int, 返回的随机数的下界（包含）
 * @param hi: int, 返回的随机数的上界（不包含）
 * @return: int, [a, b) 之间的随机整数
 */
int uniform(int lo, int hi) {
	return lo + uniform(hi - lo);
}

/**
 * @brief 根据离散概率返回 int 值 \n
 * 出现 i 的概率为 a[i]
 *
 * @param a: int[], i 的概率分布，a[] 中各元素之和必须等于 1
 * @param a_len: int, 数组 a 的长度
 * @return: int, 根据 i 的概率分布返回随机 int 值，范围 [0, a_len)
 *   传入参数不合规范则可能返回 -1
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
 * @brief 随机将 double 数组中的元素排列打乱 \n
 *
 * @param a: double[], 需要打乱排列的数组（原地改变数组）
 * @param a_len, int, 数组长度
 */
void shuffle(double a[], int a_len) {
	for (int i = 0; i < a_len; ++i) {
		// 将 a[i] 和 a[i..a_len-1] 中任意一个元素交换
		int r = i + uniform(a_len - i);
		double temp = a[i];
		a[i] = a[r];
		a[r] = temp;
	}
}
