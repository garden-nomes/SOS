/*
 * Problem 3.11
 * Noah Weiner
 *
 * Assume that a singly linked list is implemented with a header node, but no tail
 * node, and that it maintains only a pointer to the header node. Write a class that
 * includes methods to
 * a. return the size of the linked list
 * b. print the linked list
 * c. test if a value x is contained in the linked list
 * d. add a value x if it is not already contained in the linked list
 * e. remove a value x if it is contained in the linked list
 *
 * Output
 *
 * New list
 * []
 * Size: 0
 *
 * Populate list
 * [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
 * Size: 10
 *
 * List contains 5: true
 * List contains 15: false
 *
 * Remote 5
 * [0, 1, 2, 3, 4, 6, 7, 8, 9]
 * Size: 9
 *
 */

#include <iostream>
using namespace std;

template<typename Object>
class List {
	public:
		List() : header(new Node(Object())), listSize(0) { }
		~List() { recursiveDelete(header); }

		int size() const { return listSize; }

		void print(ostream& os = cout) {
			Node* n = header->next;
			if (n) {
				os << "[" << n->value;
				n = n->next;
				while (n != NULL) {
					os << ", " << n->value;
					n = n->next;
				}
				os << "]" << endl;
			} else
				os << "[]" << endl;
		}

		bool contains(Object x) const {
			for (Node* n = header->next; n != NULL; n = n->next)
				if (n->value == x) return true;
			return false;
		}

		void add(Object x) {
			Node* n = header;
			while (n->next != NULL) n = n->next;
			n->next = new Node(x);
			listSize++;
		}	

		void remove(Object x) {
			Node* p = header;
			Node* n = header->next;
			while (n != NULL) {
				if (n->value == x) {
					p->next = n->next;
					delete n;
					listSize--;
				}
				p = n;
				n = n->next;
			}
		}

	private:
		struct Node {
			Node* next;
			Object value;
			Node(Object val, Node* n = NULL) :
				value(val), next(n) { }
		};

		Node* header;
		int listSize;

		void recursiveDelete(Node* n) {
			if (n->next) recursiveDelete(n->next);
			delete n;
		}
};

int main(int argc, char* argv[]) {
	// create list
	List<int> list = List<int>();
	cout << "New list" << endl;
	list.print();
	cout << "Size: " << list.size() << endl << endl;

	// populate list
	for (int i = 0; i < 10; i++) list.add(i);
	cout << "Populate list" << endl;
	list.print();
	cout << "Size: " << list.size() << endl << endl;

	// test contains()
	cout << "List contains 5: " << (list.contains(5) ? "true" : "false") << endl;
	cout << "List contains 15: " << (list.contains(15) ? "true" : "false") << endl << endl;

	// test remove()
	list.remove(5);
	cout << "Remove 5" << endl;
	list.print();
	cout << "Size: " << list.size() << endl;

	return 0;
}
