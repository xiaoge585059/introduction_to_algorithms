
#include <iostream>
#include "tools.h"
using namespace std;

/* 朴素的矩阵相乘算法 */
int** square_matrix_multiply(int** a, int** b, int n) {
	int** c = new int*[n];
	for (int i = 0; i < n; ++i) {  // 初始化 c 矩阵
		c[i] = new int[n] { 0 };
	}
	int c_ij = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			c_ij = 0;
			for (int k = 0; k < n; ++k) {
				c_ij += a[i][k] * b[k][j];
			}
			c[i][j] = c_ij;
		}
	}

	return c;
}

/* 测试 square_matrix_multiply 函数 */
void test_square_matrix_multiply() {
	int _a[2][2] = { {1, 3}, {7, 5} };
	int* a[2];
	a[0] = _a[0];
	a[1] = _a[1];
	int _b[2][2] = { {6, 8}, {4, 2} };
	int* b[2];
	b[0] = _b[0];
	b[1] = _b[1];
	int** c = square_matrix_multiply(a, b, 2);
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
}

/* 矩阵相加（指定矩阵的一部分） */
int** matrix_add(int** a, int a_i, int a_j, int** b, int b_i, int b_j, int n) {
	int** c = new int* [n];
	for (int i = 0; i < n; ++i) {
		c[i] = new int[n] { 0 };
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			c[i][j] = a[a_i + i][a_j + j] + b[b_i + i][b_j + j];
		}
	}

	return c;
}

/* 矩阵相减（指定矩阵的一部分） */
int** matrix_minus(int** a, int a_i, int a_j, int** b, int b_i, int b_j, int n) {
	int** c = new int* [n];
	for (int i = 0; i < n; ++i) {
		c[i] = new int[n] { 0 };
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			c[i][j] = a[a_i + i][a_j + j] - b[b_i + i][b_j + j];
		}
	}

	return c;
}

/* 测试 matrix_add 和 matrix_minus 函数 */
void test_matrix_add() {
	int _a[2][2] = { {1, 3}, {7, 5} };
	int* a[2];
	a[0] = _a[0];
	a[1] = _a[1];
	int _b[2][2] = { {6, 8}, {4, 2} };
	int* b[2];
	b[0] = _b[0];
	b[1] = _b[1];
	int** c = matrix_add(a, 0, 0, b, 0, 0, 2);
	// int** c = matrix_minus(a, 0, 0, b, 0, 0, 2);

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
}

/**
 * 矩阵相乘的分治递归算法（Strassen 算法）
 *   进行 7 次递归矩阵乘法，比朴素递归算法的 8 次递归矩阵乘法少 1 次
 *   朴素递归算法的 8 次递归矩阵乘法:
 *     C11 = A11 * B11 + A12 * B21
 *     C12 = A11 * B12 + A12 * B22
 *     C21 = A21 * B11 + A22 * B21
 *     C22 = A21 * B12 + A22 * B22
 *
 * n 必须为 2 的整数次方
 */
int** strassen_square_matrix_multiply_recursive(int** a, int a_i, int a_j, int** b, int b_i, int b_j, int n) {
	int** c = new int* [n];
	for (int i = 0; i < n; ++i) {  // 初始化矩阵 c
		c[i] = new int[n] { 0 };
	}

	if (n == 1) {
		c[0][0] = a[a_i][a_j] * b[b_i][b_j];
		return c;
	} else {
		int half_n = n / 2;
		int a11_i = a_i, a11_j = a_j;
		int a12_i = a_i, a12_j = a_j + half_n;
		int a21_i = a_i + half_n, a21_j = a_j;
		int a22_i = a_i + half_n, a22_j = a_j + half_n;
		int b11_i = b_i, b11_j = b_j;
		int b12_i = b_i, b12_j = b_j + half_n;
		int b21_i = b_i + half_n, b21_j = b_j;
		int b22_i = b_i + half_n, b22_j = b_j + half_n;

		int** s1 = matrix_minus(b, b12_i, b12_j, b, b22_i, b22_j, half_n);
		int** s2 = matrix_add(a, a11_i, a11_j, a, a12_i, a12_j, half_n);
		int** s3 = matrix_add(a, a21_i, a21_j, a, a22_i, a22_j, half_n);
		int** s4 = matrix_minus(b, b21_i, b21_j, b, b11_i, b11_j, half_n);
		int** s5 = matrix_add(a, a11_i, a11_j, a, a22_i, a22_j, half_n);
		int** s6 = matrix_add(b, b11_i, b11_j, b, b22_i, b22_j, half_n);
		int** s7 = matrix_minus(a, a12_i, a12_j, a, a22_i, a22_j, half_n);
		int** s8 = matrix_add(b, b21_i, b21_j, b, b22_i, b22_j, half_n);
		int** s9 = matrix_minus(a, a11_i, a11_j, a, a21_i, a21_j, half_n);
		int** s10 = matrix_add(b, b11_i, b11_j, b, b12_i, b12_j, half_n);

		int** p1 = strassen_square_matrix_multiply_recursive(a, a11_i, a11_j, s1, 0, 0, half_n);
		int** p2 = strassen_square_matrix_multiply_recursive(s2, 0, 0, b, b22_i, b22_j, half_n);
		int** p3 = strassen_square_matrix_multiply_recursive(s3, 0, 0, b, b11_i, b11_j, half_n);
		int** p4 = strassen_square_matrix_multiply_recursive(a, a22_i, a22_j, s4, 0, 0, half_n);
		int** p5 = strassen_square_matrix_multiply_recursive(s5, 0, 0, s6, 0, 0, half_n);
		int** p6 = strassen_square_matrix_multiply_recursive(s7, 0, 0, s8, 0, 0, half_n);
		int** p7 = strassen_square_matrix_multiply_recursive(s9, 0, 0, s10, 0, 0, half_n);

		int** c11 = matrix_add(matrix_minus(matrix_add(p5, 0, 0, p4, 0, 0, half_n), 0, 0, p2, 0, 0, half_n), 0, 0, p6, 0, 0, half_n);
		int** c12 = matrix_add(p1, 0, 0, p2, 0, 0, half_n);
		int** c21 = matrix_add(p3, 0, 0, p4, 0, 0, half_n);
		int** c22 = matrix_minus(matrix_minus(matrix_add(p5, 0, 0, p1, 0, 0, half_n), 0, 0, p3, 0, 0, half_n), 0, 0, p7, 0, 0, half_n);

		// 将 c11, c12, c21, c22 组合为 c
		for (int i = 0; i < half_n; ++i) {
			for (int j = 0; j < half_n; ++j) {
				c[i][j] = c11[i][j];
				c[i][j + half_n] = c12[i][j];
				c[i + half_n][j] = c21[i][j];
				c[i + half_n][j + half_n] = c22[i][j];
			}
		}

		for (int i = 0; i < half_n; ++i) {
			delete[] s1[i], s2[i], s3[i], s4[i], s5[i], s6[i], s7[i], s8[i], s9[i], s10[i],
				p1[i], p2[i], p3[i], p4[i], p5[i], p6[i], p7[i], c11[i], c12[i], c21[i], c22[i];
		}
		delete[] s1, s2, s3, s4, s5, s6, s7, s8, s9, s10,
			p1, p2, p3, p4, p5, p6, p7, c11, c12, c21, c22;

		return c;
	}
}

/* 测试 strassen_square_matrix_multiply_recursive 函数 */
void test_strassen_square_matrix_multiply_recursive() {
	int _a[2][2] = { {1, 3}, {7, 5} };
	int* a[2];
	a[0] = _a[0];
	a[1] = _a[1];
	int _b[2][2] = { {6, 8}, {4, 2} };
	int* b[2];
	b[0] = _b[0];
	b[1] = _b[1];
	int** c = strassen_square_matrix_multiply_recursive(a, 0, 0, b, 0, 0, 2);

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
}


/* 测试 */
//*
int main() {
	// test_square_matrix_multiply();
	// test_matrix_add();
	test_strassen_square_matrix_multiply_recursive();

	return 0;
}
//*/