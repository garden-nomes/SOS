/*
 * Problem 3.2
 * Noah Weiner
 *
 * Swap two adjacent elements by adjusting only the links (and not the data) using
 *  a. singly linked lists
 *  b. doubly linked lists
 *
 *  Output:
 *
 *  Singly linked list: 0 1 2 3 4 5 6 7 8 9 
 *  Swapping element 5...
 *  Singly linked list: 0 1 2 3 4 6 5 7 8 9 
 *
 *  Doubly linked list: 0 1 2 3 4 5 6 7 8 9 
 *  Swapping element 5...
 *  Singly doubly list: 0 1 2 3 4 6 5 7 8 9 
 */

#include <iostream>
using namespace std;

/*
 * a. singly linked list
 */

struct Node_S {
	Node_S* next;
	int value;

	Node_S(int val) : value(val), next(NULL) { }
};

void push(Node_S* node, int val) {
	while (node->next)
		node = node->next;

	Node_S* next = new Node_S(val);
	node->next = next;
}

void print(const Node_S* node, ostream& out = cout) {
	while (node != NULL) {
		out << node->value << " ";
		node = node->next;
	}
}

void deleteList(Node_S* node) {
	if (node->next) deleteList(node->next);
	delete node;
}

int swap(Node_S* a, int index) {
	Node_S* prev = NULL;
	for (int i = 0; i < index; i++) {
		if (!a->next) return -1;	// no adjacent node to swap
		prev = a;
		a = a->next;
	}

	Node_S* b = a->next;
	if (prev) prev->next = b;
	a->next = b->next;
	b->next = a;
}

/*
 * b. doubly linked list
 */

struct Node_D {
	Node_D* next;
	Node_D* prev;
	int value;

	Node_D(int val, Node_D* p = NULL) : value(val), next(NULL), prev(p) { }
};

void push(Node_D* node, int val) {
	while (node->next)
		node = node->next;

	Node_D* next = new Node_D(val, node);
	node->next = next;
}

void print(const Node_D* node, ostream& out = cout) {
	while (node != NULL) {
		out << node->value << " ";
		node = node->next;
	}
}

void deleteList(Node_D* node) {
	if (node->next) deleteList(node->next);
	delete node;
}

int swap(Node_D* a, int index) {
	for (int i = 0; i < index; i++) {
		if (!a->next) return -1;	// no adjacent node to swap
		a = a->next;
	}

	// commence swappage
	Node_D* b = a->next;
	a->prev->next = b;
	b->next->prev = a;
	a->next = b->next;
	b->prev = a->prev;
	a->prev = b;
	b->next = a;
}

/*
 * Test functionality
 */

int main(int argc, char* argv[]) {
	// create test lists
	Node_S* ns = new Node_S(0);
	Node_D* nd = new Node_D(0);
	for (int i = 1; i < 10; i++) {
		push(ns, i);
		push(nd, i);
	}

	// test singly linked list
	cout << "Singly linked list: ";
	print(ns);
	cout << endl << "Swapping element 5..." << endl;
	swap(ns, 5);
	cout << "Singly linked list: ";
	print(ns);

	// test doubly linked list
	cout << endl << endl << "Doubly linked list: ";
	print(nd);
	cout << endl << "Swapping element 5..." << endl;
	swap(nd, 5);
	cout << "Singly doubly list: ";
	print(nd);
	cout << endl;

	// clean up
	deleteList(ns);
	deleteList(nd);

	return 0;
}
