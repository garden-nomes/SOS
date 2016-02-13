/*
 * Problem 3.6a
 * Noah Weiner
 *
 * Write a program to solve the Josephus problem for general values of M and N.
 * Try to make your program as efficient as possible. Make sure you dispose of cells.
 *
 * b) O(m*n)
 * c) O(n), the speed would be drastically increased as the program needs to delete
 *    n elements.
 */

#include <iostream>
using namespace std;

/*
 * Linked list implementation
 */

struct player {
	player* next;
	unsigned int id;
	player(unsigned int i, player* n = NULL) : id(i), next(n) {}
};

int hot_potato_list(unsigned int m, unsigned int n) {
	// create list
	player* first = new player(1);
	player* p = first;
	if (n > 0) {
		for (unsigned int i = 2; i <= n; i++) {
			p->next = new player(i);
			p = p->next;
		}
	}
	p->next = first;

	// elimination
	player* o = p;	// chase pointer
	p = first;

	// run until there is only one node left
	while (p->next != p) {
		// advance m places
		for (int i = 0; i < m; i++) {
			o = p;
			p = p->next;
		}

		// eliminate node
		o->next = p->next;
		delete p;
		p = o->next;
	}

	int id = p->id;
	delete p;
	return id;
}

void print_test(unsigned int m, unsigned int n) {
	cout << "hot_potato_list(" << m << ", " << n << "): ";
	cout << hot_potato_list(m, n) << endl;
	cout << "hot_potato_recursive(" << m << ", " << n << "): ";
	cout << hot_potato_recursive(m, n) << endl;
}	

int main(int argc, char* argv[]) {
	print_test(0, 5);
	print_test(1, 5);
	print_test(0, 10);
	print_test(1, 10);
	print_test(3, 10000);

	return 0;
}
