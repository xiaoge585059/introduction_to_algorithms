
#include <iostream>
#include "tools.h"
using namespace std;

/* 获取堆中某个节点 i 的父节点（假定 i 不为根节点，即 i > 0） */
inline int parent(int i) {
	return ((i + 1) >> 1) - 1;  // 右移操作相当于除以 2，但效率比除法高
}

/* 获取堆中某个节点 i 的左子节点（假定 i 的左移一位操作不会溢出） */
inline int left(int i) {
	return (i << 1) + 1;  // 左移操作相当于乘以 2，但效率比乘法高
}

/* 获取堆中某个节点 i 的右子节点（假定 i 的左移一位操作不会溢出） */
inline int right(int i) {
	return (i << 1) + 2;
}

/* 测试内联函数 parent, left, right */
void test_parent_child() {
	for (int i = 0; i < 5; ++i) {
		cout << "left child of " << i << ": " << left(i) << endl;
		cout << "parent of " << left(i) << ": " << parent(left(i)) << endl;
		cout << "right child of " << i << ": " << right(i) << endl;
		cout << "parent of " << right(i) << ": " << parent(right(i)) << endl;
		cout << endl;
	}
}

/**
 * 维护最大堆的性质，即某个节点的值大于等于其左右子节点
 * 如果某个节点与子节点有交换，依次维护相应子节点的最大堆性质
 */
void max_heapify(int a[], int heap_size, int node_i) {
	int i = -1;
	int l = 0, r = 0;
	int largest = node_i;
	int temp = 0;
	while (i != largest) {
		i = largest;  // 第一次循环的时候 i 取值为 node_i
		l = left(i);
		r = right(i);
		if (l < heap_size && a[l] > a[i]) {
			largest = l;
		}
		if (r < heap_size && a[r] > a[largest]) {
			largest = r;
		}

		// 确保父节点大于左右子节点
		if (i != largest) {
			temp = a[i];
			a[i] = a[largest];
			a[largest] = temp;
		}
	}
}

/**
 * 在数组上建立最大堆
 * 叶子节点是只有一个节点的数，自然是最大堆
 * 从叶子节点开始向根节点一层层建立最大堆
 */
void build_max_heap(int a[], int a_len) {
	int heap_size = a_len;  // 堆的大小不一定是数组长度
	for (int i = heap_size / 2 - 1; i >= 0; --i) {
		max_heapify(a, heap_size, i);
	}
}

/**
 * 堆排序算法（升序）
 *   1.建立最大堆（最大堆的根元素为堆中最大的元素）
 *   2.将最大堆的根节点与最后一个节点交换，将堆拥有的节点数减一，重新建立最大堆
 *   3.重复第 2 步，直到堆只有一个节点，算法运行完毕
 */
void heap_sort(int a[], int a_len) {
	build_max_heap(a, a_len);

	int heap_size = a_len;
	int temp = 0;
	for (int i = a_len - 1; i >= 1; --i) {
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		heap_size -= 1;
		max_heapify(a, heap_size, 0);  // 恢复最大堆性质
	}
}

/* 测试 heap_sort 函数 */
void test_heap_sort() {
	int a[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	print_array(a, 10);
	heap_sort(a, 10);
	print_array(a, 10);
}

/* 获取最大堆中的最大值，即最大堆第一个元素 */
int heap_maximum(int a[], int heap_size) {
	return a[0];
}

/* 获取最大堆中的最大值，并将其从最大堆中取出, heap_size 减一 */
int heap_extract_max(int a[], int heap_size) {
	if (heap_size < 1) {
		return INT_MIN;  // 此处应该报错："heap underflow"
	}

	int max = a[0];
	a[0] = a[heap_size - 1];
	max_heapify(a, heap_size - 1, 0);

	return max;
}

/* 将堆中 i 节点的值增加为 key(key 必须大于等于 i 节点原先的值，并维持最大堆的性质) */
void heap_increase_key(int a[], int i, int key) {
	if (key < a[i]) {
		return;  // 此处应报错："new key is smaller than current key"
	}

	a[i] = key;
	int temp = 0;
	/*
	while (i > 0 && a[parent(i)] < a[i]) {
		temp = a[i];
		a[i] = a[parent(i)];
		a[parent(i)] = temp;

		i = parent(i);
	} */

	// 更高效地完成元素交换操作
	while (i > 0 && a[parent(i)] < key) {
		a[i] = a[parent(i)];
		i = parent(i);
	}
	a[i] = key;
}

/* 将 key 值插入最大堆，堆的元素数加一，并维持最大堆性质 */
void max_heap_insert(int a[], int heap_size, int key) {
	heap_size += 1;
	a[heap_size - 1] = INT_MIN;
	heap_increase_key(a, heap_size - 1, key);
}

/* 从最大堆中删除 i 节点，并维护最大堆性质，将 heap_size 减一 */
void heap_delete(int a[], int heap_size, int i) {
	if (a[i] > a[heap_size - 1]) {
		a[i] = a[heap_size - 1];
		max_heapify(a, heap_size, i);
	} else {
		heap_increase_key(a, i, a[heap_size - 1]);
	}

	// heap_size -= 1;
}

/* 测试优先队列的相关函数 */
void test_priority_queue() {
	int a[11] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1, 0 };
	int heap_size = 10;
	print_array(a, heap_size, "原最大堆：");
	heap_increase_key(a, 8, 15);
	print_array(a, heap_size, "将 a[8] 节点增加到 15 后：");
	max_heap_insert(a, 10, 13);
	heap_size += 1;
	print_array(a, heap_size, "将值为 13 的节点插入到最大堆后：");
	int max = heap_extract_max(a, heap_size);
	heap_size -= 1;
	print_array(a, heap_size, "将最大堆中最大值移出后：");
	cout << "最大值为：" << max << endl;

	cout << endl << "delete: " << endl;
	int b[7] = { 15, 7, 9, 1, 2, 3, 8 };
	int heap_size_b = 7;
	print_array(b, heap_size_b, "原最大堆：");
	heap_delete(a, heap_size_b, 4);
	heap_size_b -= 1;
	print_array(b, heap_size_b, "删除第 5 个元素后：");
}


/* 测试 */
/*
int main() {
	// test_parent_child();
	// test_heap_sort();
	test_priority_queue();

	return 0;
}
//*/
