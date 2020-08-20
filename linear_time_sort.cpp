
#include <iostream>
#include "tools.h"
using namespace std;

/**
 * �������򣬷�ԭ�����򣨷���һ���ź���������飩
 *   �������� a��a �е�Ԫ�ص����ֵС�ڵ��� upper_limit���� a ��Ԫ�طǸ�
 */
int* counting_sort(int a[], int a_len, int upper_limit) {
	int* b = new int[a_len] { 0 };
	int c_len = upper_limit + 1;
	int* c = new int[c_len] { 0 };  // c ��Ԫ�ص�������Ӧ a ��Ԫ�ص�ֵ
	for (int i = 0; i < a_len; ++i) {
		c[a[i]] += 1;  // c ��Ԫ�ص�ֵ��Ӧ��Ӧ a ����ͬԪ�صĸ���
	}

	for (int i = 1; i < c_len; ++i) {
		c[i] = c[i] + c[i - 1];  // �ۼ� c[i]����ʱ c[i] ��ֵΪ���� a ��С�ڵ��� i ֵ��Ԫ�ص�����
	}

	for (int i = a_len - 1; i >= 0; --i) {  // �Ӻ���ǰ������Ϊ���ȶ�������ֵͬ��ǰ����򲻱䣩
		b[c[a[i]] - 1] = a[i];
		c[a[i]] -= 1;  // ��������ֵͬ����һ��ʹ����ֵͬ�ҵ���ȷλ��(ǰһ��λ��)
	}

	delete[] c;
	return b;
}

/* ���� counting_sort ���� */
void test_counting_sort() {
	int a[8] = { 2, 5, 3, 0, 2, 3, 0, 3 };
	int upper_limit = 5;
	print_array(a, 8);
	int* b = counting_sort(a, 8, upper_limit);
	print_array(b, 8);

	delete[] b;
}

/**
 * ͨ�����������������Ԫ�ص���Ӧ��λ��������
 * digit_position ��ʾ��ǰ�Եڼ�λ��������
 */
void radix_sort_by_counting_sort(int a[], int a_len, int digit_position) {
	int* b = new int[a_len] { 0 };
	int c[10] = { 0 };  // ÿһλ�� 10 ��ȡֵ: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

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
 * ��������
 * �������ȶ��������㷨֮�ϣ����δ����λ��ʼ��ÿһλ��������
 * ����������������������Ԫ�ر���λ�����
 * ��������Ҳ�������ַ�������
 */
void radix_sort(int a[], int a_len, int digit_num) {
	for (int i = 1; i <= digit_num; ++i) {
		radix_sort_by_counting_sort(a, a_len, i);
	}
}

/* ���� radix_sort ���� */
void test_radix_sort() {
	int a[8] = { 329, 457, 657, 839, 436, 720, 355, 233 };
	print_array(a, 8);
	radix_sort(a, 8, 3);
	print_array(a, 8);
}

// ------------------- Ͱ���� -------------------

/* ����ڵ� */
struct Node {
	double data = 0;
	Node* next = nullptr;

	Node(double data = 0, Node* next = nullptr) {
		this->data = data;
		this->next = next;
	}
};

/* �����ʵ�֣����� */
class SortedList {
private:
	Node* head = nullptr;
	int length = 0;

public:
	/* ���� node �������� */
	void insert(Node* node) {
		// head Ϊ��ָ����ֱ�ӽ� node ��Ϊ head
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

		// ���� current == nullptr���� prevous->next == nullptr��node �����������
		previous->next = node;
	}

	/* �����Ƿ�Ϊ�� */
	bool is_empty() {
		return head == nullptr;
	}

	/**
	 * ��ȡ�����һ��Ԫ��
	 * ���ص�һ��Ԫ�ز���������ɾ��
	 * �������Ϊ�գ�ʹ��֮ǰ��Ҫ�б������Ƿ�Ϊ��
	 */
	double extract_head() {
		double result = this->head->data;
		Node* old_head = this->head;
		this->head = this->head->next;
		delete old_head;  // ��������ȡ�ľɵ� head �ڵ�
		return result;
	}

	/* ��ӡ���� */
	void print() {
		Node* current = this->head;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
};

/* �������� */
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
 * Ͱ����������������ΪͰ��
 * �����Ԫ�ض�Ϊ [0, 1) �����ڵĸ�����
 */
void bucket_sort(double a[], int a_len) {
	SortedList* buckets = new SortedList[a_len];
	for (int i = 0; i < a_len; ++i) {
		buckets[i] = SortedList();  // �浽 SortedList �е������Զ�����
	}

	// ʮ��Ͱ������ֵ�����: [0, 0.1), [0.1, 0.2), [0.2, 0.3), ... �Դ����Ƶ� [0.9, 1)
	for (int i = 0; i < a_len; ++i) {
		buckets[(int)(a_len * a[i])].insert(new Node(a[i]));
	}

	// ������Ͱ�е�������ϲ��� a ��
	int count = 0;
	for (int i = 0; i < a_len; ++i) {
		while (!buckets[i].is_empty()) {
			a[count++] = buckets[i].extract_head();
		}
	}
}

/* ���� bucket_sort ���� */
void test_bucket_sort() {
	double a[10] = { 0.79, 0.13, 0.16, 0.64, 0.39, 0.20, 0.89, 0.53, 0.71, 0.42 };
	print_array(a, 10);
	bucket_sort(a, 10);
	print_array(a, 10);
}


/* ���� */
/*
int main() {
	// test_counting_sort();
	// test_radix_sort();
	// test_list();
	test_bucket_sort();

	return 0;
}
//*/
