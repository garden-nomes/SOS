/*
 * Problem 3.29
 * Noah Weiner
 *
 * Write an algorithm for printing a singly linked list in reverse, using only constant extra space. This instruction
 * implies that you cannot use recursion but you may assume that your algorithm is a list member function. Can such
 * an algorithm be written if the routine is a constant member function?
 *
 * The algorthim can be implemented as a constant member function, since it doesn't actually modify the state of the list.
 */

#include <iostream>
using namespace std;

/*
 * Singly linked list
 */

struct Node {
	Node* next;
	int value;

	Node(int v, Node* n = NULL) :
		value(v), next(n) { }
};

Node* push(Node* n, int value) {
	n->next = new Node(value);
	return n->next;
}

void delete_node(Node* n) {
	if (n->next) delete_node(n->next);
	delete n;
}

void print_forward(Node* head) {
	cout << "[" << head->value;
	head = head->next;
	while (head != NULL) {
		cout << ", " << head->value;
		head = head->next;
	}
	cout << "]" << endl;
}

/*
 * Reverse print algorithm
 *
 * Keep a pointer to the end of the list, and iterate over the list
 * until that pointer is reached, decrementing it every time.
 */

void print_reverse(Node* head) {
	cout << "[";
	Node* end = NULL;

	do {
		if (end != NULL) cout << ", ";

		Node* n = head;
		while (n->next != end) n = n->next;
		cout << n->value;
		end = n;
	} while (end != head);

	cout << "]" << endl;
}

/*
 * Main function
 */

int main(int argc, char* argv[]) {
	Node* head = new Node(1);
	Node* n = head;
	for (int i = 2; i <= 10; i++)
		n = push(n, i);

	print_forward(head);
	print_reverse(head);

	delete_node(head);
	return 0;
}
