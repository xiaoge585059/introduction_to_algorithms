
#include <iostream>
#include "tools.h"
using namespace std;

/* ջ */
class Stack {
private:
	/* ջ�� */
	int top = -1;
	/* �洢ջ��Ԫ�ص����� */
	int* stack = nullptr;

public:
	Stack(int size) {
		this->top = -1;
		this->stack = new int[size] { 0 };
	}

	~Stack() {
		delete[] this->stack;
	}

	/* �ж�ջ�Ƿ�Ϊ�� */
	bool is_empty() {
		return this->top == -1;
	}

	/* ��Ԫ��ѹ��ջ�� */
	void push(int x) {
		this->top += 1;
		this->stack[this->top] = x;
	}

	/* ��ջ��Ԫ�ص��� */
	int pop() {
		if (this->is_empty()) {
			cout << "error: underflow" << endl;  // �쳣��underflow
			return INT_MIN;
		}

		this->top -= 1;
		return this->stack[this->top + 1];
	}

	/* ��ӡջ��Ԫ�� */
	void print() {
		cout << "stack: ";
		for (int i = 0; i <= this->top; ++i) {
			cout << this->stack[i] << " ";
		}
		cout << endl;
	}
};

/* ���� Stack */
void test_Stack() {
	Stack s(10);
	s.push(15);
	s.push(6);
	s.push(2);
	s.push(9);
	s.print();
	s.push(17);
	s.push(3);
	s.print();
	int top = s.pop();
	cout << "pop: " << top << endl;
	s.print();
}


/* ���� */
class Queue {
private:
	/* ����Ԫ������ */
	int head = 0;
	/* ��βԪ�غ�һ������ */
	int tail = 0;
	/* ��Ŷ���Ԫ�ص����� */
	int* queue = nullptr;
	/* �������� */
	int size;

public:
	Queue(int size) {
		this->head = 0;
		this->tail = 0;
		this->size = size;
		this->queue = new int[size] { 0 };
	}

	~Queue() {
		delete[] this->queue;
	}

	/* �����Ƿ�Ϊ�� */
	bool is_empty() {
		return this->head == this->tail;
	}

	/* �����Ƿ����� */
	bool is_full() {
		return (this->head == this->tail + 1) || (this->head == 0 && this->tail == this->size - 1);
	}

	/* Ԫ����ӣ������β */
	void enqueue(int x) {
		if (this->is_full()) {
			cout << "error: overflow" << endl;  // �쳣��overflow
			return;
		}

		this->queue[this->tail] = x;
		if (this->tail == this->size - 1) {
			this->tail = 0;
		} else {
			this->tail += 1;
		}
	}

	/* ����Ԫ�س��� */
	int dequeue() {
		if (this->is_empty()) {
			cout << "error: underflow" << endl;  // �쳣��underflow
			return INT_MIN;
		}

		int x = this->queue[this->head];
		if (this->head == this->size - 1) {
			this->head = 0;
		} else {
			this->head += 1;
		}

		return x;
	}

	/* ��ӡ������Ԫ�� */
	void print() {
		int elements_count = 0;
		if (this->head <= this->tail) {
			elements_count = this->tail - this->head;
		} else {
			elements_count = this->tail + this->size - this->head;
		}
		
		cout << "queue: ";
		int current_index = this->head;
		for (int i = 0; i < elements_count; ++i) {
			cout << this->queue[current_index++] << " ";
			if (current_index == this->size) {
				current_index = 0;
			}
		}
		cout << endl;
	}
};

/* ���� Queue */
void test_Queue() {
	Queue q(12);
	for (int i = 0; i < 6; ++i) {
		q.enqueue(0);
		q.dequeue();
	}

	q.enqueue(15);
	q.enqueue(6);
	q.enqueue(9);
	q.enqueue(8);
	q.enqueue(4);
	q.print();
	q.enqueue(17);
	q.enqueue(3);
	q.enqueue(5);
	q.print();
	int front = q.dequeue();
	cout << "front: " << front << endl;
	q.print();
}


/* ���� */
/*
int main() {
	// test_Stack();
	test_Queue();

	return 0;
}
//*/
