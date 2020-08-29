
#include <iostream>
using namespace std;

typedef struct ListNode {
	int key = 0;
	ListNode* previous = nullptr;
	ListNode* next = nullptr;

	ListNode(int key) {
		this->key = key;
	}

	~ListNode() {
		delete previous, next;
	}
};

class List {
private:
	ListNode* head = nullptr;

public:
	List() {
		head = nullptr;
	}

	~List() {
		ListNode* next_to_delete = head;
	}
};


/* ≤‚ ‘ */
//*
int main() {
	

	return 0;
}
//*/
