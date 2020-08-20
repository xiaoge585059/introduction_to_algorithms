
#include <iostream>
#include "tools.h"
using namespace std;

/**
 * 计数排序，非原地排序（返回一个排好序的新数组）
 *   排序数组 a，a 中的元素的最大值小于等于 upper_limit，且 a 中元素非负
 */
int* counting_sort(int a[], int a_len, int upper_limit) {
	int* b = new int[a_len] { 0 };
	int c_len = upper_limit + 1;
	int* c = new int[c_len] { 0 };  // c 中元素的索引对应 a 中元素的值
	for (int i = 0; i < a_len; ++i) {
		c[a[i]] += 1;  // c 中元素的值对应相应 a 中相同元素的个数
	}

	for (int i = 1; i < c_len; ++i) {
		c[i] = c[i] + c[i - 1];  // 累加 c[i]，此时 c[i] 的值为数组 a 中小于等于 i 值的元素的总数
	}

	for (int i = a_len - 1; i >= 0; --i) {  // 从后向前遍历，为了稳定排序（相同值的前后次序不变）
		b[c[a[i]] - 1] = a[i];
		c[a[i]] -= 1;  // 可能有相同值，减一以使得相同值找到正确位置(前一个位置)
	}

	delete[] c;
	return b;
}

/* 测试 counting_sort 函数 */
void test_counting_sort() {
	int a[8] = { 2, 5, 3, 0, 2, 3, 0, 3 };
	int upper_limit = 5;
	print_array(a, 8);
	int* b = counting_sort(a, 8, upper_limit);
	print_array(b, 8);

	delete[] b;
}

/**
 * 通过计数排序对数组中元素的相应数位进行排序
 * digit_position 表示当前对第几位进行排序
 */
void radix_sort_by_counting_sort(int a[], int a_len, int digit_position) {
	int* b = new int[a_len] { 0 };
	int c[10] = { 0 };  // 每一位有 10 种取值: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

	int offset = 1;
	for (int i = 1; i < digit_position; ++i) {
		offset *= 10;
	}

	for (int i = 0; i < a_len; ++i) {
		c[(a[i] / offset) % 10] += 1;
	}

	for (int i = 1; i < 10; ++i) {
		c[i] += c[i - 1];
	}

	for (int i = a_len - 1; i >= 0; --i) {
		int ai_pos = (a[i] / offset) % 10;
		b[c[ai_pos] - 1] = a[i];
		c[ai_pos] -= 1;
	}

	for (int i = 0; i < a_len; ++i) {
		a[i] = b[i];
	}

	delete[] b;
}

/**
 * 基数排序
 * 建立在稳定的排序算法之上，依次从最低位开始对每一位进行排序
 * 这个函数处理的数组里所有元素必须位数相等
 * 基数排序也可用于字符串排序
 */
void radix_sort(int a[], int a_len, int digit_num) {
	for (int i = 1; i <= digit_num; ++i) {
		radix_sort_by_counting_sort(a, a_len, i);
	}
}

/* 测试 radix_sort 函数 */
void test_radix_sort() {
	int a[8] = { 329, 457, 657, 839, 436, 720, 355, 233 };
	print_array(a, 8);
	radix_sort(a, 8, 3);
	print_array(a, 8);
}

// ------------------- 桶排序 -------------------

/* 链表节点 */
struct Node {
	double data = 0;
	Node* next = nullptr;

	Node(double data = 0, Node* next = nullptr) {
		this->data = data;
		this->next = next;
	}
};

/* 链表简单实现（有序） */
class SortedList {
private:
	Node* head = nullptr;
	int length = 0;

public:
	/* 有序将 node 插入链表 */
	void insert(Node* node) {
		// head 为空指针则直接将 node 作为 head
		if (this->head == nullptr) {
			this->head = node;
			this->length += 1;
			return;
		}

		if (node->data <= this->head->data) {
			node->next = this->head;
			this->head = node;
			return;
		}

		Node* current = this->head->next;
		Node* previous = this->head;
		while (current != nullptr) {
			if (node->data <= current->data) {
				node->next = current;
				previous->next = node;
				return;
			}
			previous = current;
			current = current->next;
		}

		// 最终 current == nullptr，即 prevous->next == nullptr，node 插入链表最后
		previous->next = node;
	}

	/* 链表是否为空 */
	bool is_empty() {
		return head == nullptr;
	}

	/**
	 * 提取链表第一个元素
	 * 返回第一个元素并从链表中删除
	 * 链表可能为空，使用之前需要判别链表是否为空
	 */
	double extract_head() {
		double result = this->head->data;
		Node* old_head = this->head;
		this->head = this->head->next;
		delete old_head;  // 清理已提取的旧的 head 节点
		return result;
	}

	/* 打印链表 */
	void print() {
		Node* current = this->head;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
};

/* 测试链表 */
void test_list() {
	int a[10] = { 3, 2, 4, 7, 1, 9, 6, 5, 0, 8 };
	SortedList* list = new SortedList();
	for (int i = 0; i < 10; ++i) {
		Node* node = new Node(a[i]);
		list->insert(node);
	}

	list->print();

	cout << list->extract_head() << endl;
	cout << list->extract_head() << endl;

	list->print();
}

/**
 * 桶排序（这里以链表作为桶）
 * 排序的元素都为 [0, 1) 区间内的浮点数
 */
void bucket_sort(double a[], int a_len) {
	SortedList* buckets = new SortedList[a_len];
	for (int i = 0; i < a_len; ++i) {
		buckets[i] = SortedList();  // 存到 SortedList 中的数会自动排序
	}

	// 十个桶存放数字的区间: [0, 0.1), [0.1, 0.2), [0.2, 0.3), ... 以此类推到 [0.9, 1)
	for (int i = 0; i < a_len; ++i) {
		buckets[(int)(a_len * a[i])].insert(new Node(a[i]));
	}

	// 将各个桶中的数有序合并到 a 中
	int count = 0;
	for (int i = 0; i < a_len; ++i) {
		while (!buckets[i].is_empty()) {
			a[count++] = buckets[i].extract_head();
		}
	}
}

/* 测试 bucket_sort 函数 */
void test_bucket_sort() {
	double a[10] = { 0.79, 0.13, 0.16, 0.64, 0.39, 0.20, 0.89, 0.53, 0.71, 0.42 };
	print_array(a, 10);
	bucket_sort(a, 10);
	print_array(a, 10);
}


/* 测试 */
/*
int main() {
	// test_counting_sort();
	// test_radix_sort();
	// test_list();
	test_bucket_sort();

	return 0;
}
//*/
