/* Noah Weiner
 * Data Structures Lab 6
 *
 * Specifiation:
 * Design a data structure that supports push, pop, top, isEmpty (ie the typical Stack interface). In
 * addition, you should also support getMin, which returns, but does not delete the minimum value. All your
 * methods must be O(1).
 *   - Give a detailed design
 *   - Prove all methods are O(1) and prove they are all correct. In particular, prove that getMin will
 *     always return the minimum.
 *   - Implement (you will be using already implemented data structures for this)
 *   - Test
 *
 * Note: I changed some of the naming conventions; isEmpty() is now empty() and getMin() is just min().
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename Comparable>
class Stack {
private:
	struct Node {
		Node* n_next;
		Node* n_next_largest;
		Comparable n_value;
		Node(Comparable& value, Node* next) : n_value(value), n_next(next) { }

	};

public:
	/*------------------------
	 * Constructors/Destructor
	 *-----------------------*/

	// constructor
	Stack() : head(NULL), min_node(NULL) { }

	// destructor
	~Stack() {
		Node* tmp;
		while (head != NULL)
			pop();
	}

	// copy constructor
	Stack(const Stack& rhs) {
		Node* tmp = rhs.head;
		while (tmp != NULL) {
			push(tmp->n_value);
			tmp = tmp->next;
		}
	}

	// move constructor
	Stack(Stack&& rhs) : head(rhs.head), min_node(rhs.min_node) {
		rhs.head = NULL;
		rhs.min_node = NULL;
	}

	// copy assignment
	Stack& operator=(const Stack& rhs) {
		if (this != &rhs) {
			~Stack();
			Node* tmp;
			for (tmp = rhs.head; tmp != NULL; tmp = tmp->next)
				push(tmp->n_value);
		}
		return *this;
	}

	// move assignment
	Stack& operator=(Stack&& rhs) {
		if (this != &rhs) {
			~Stack();
			std::swap(head, rhs.head);
			std::swap(min_node, rhs.min_node);
		}
		return *this;
	}

	/*------------------------
	 * Operations
	 *-----------------------*/

	// insert new node at head
	// O(1), performs 3 operations max regardless of list size. Ensures min will always point to the smallest
	// value by checking if the new value is smaller than the current min. If min_node->value is the current
	// smallest value, and the new value is smaller than that, then min_node->n_next_largest will always point
	// to the next largest value.
	void push(Comparable& value) {
		head = new Node(value, head);
		// track smallest value
		if (min_node == nullptr)
			min_node = head;
		else if (value < min_node->n_value) {
			head->n_next_largest = min_node;
			min_node = head;
		}
	}

	// delete head
	// O(1), only works on head. Ensures min will always point to smallest value, as push() ensures that
	// min_node->n_next_largest will be the new smallest value.
	//
	// You might think that this would run into trouble since it's possible for a node to have a nullptr
	// n_next_largest, but it only accesses n_next_largest with head == min_node and n_next_largest is set
	// at the same time min_node is set in push().
	void pop() {
		if (head != NULL) {
			Node* tmp = head->n_next;
			// update min element if nessecary
			if (head == min_node)
				min_node = min_node->n_next_largest;
			delete head;
			head = tmp;
		}
	}

	// return head's value
	// Definitely O(1)
	Comparable& top() const {
		return head->n_value;
	}

	// return smallest element
	// Also definitely O(1). See push() and pop() to see how min_node works.
	Comparable& min() const {
		return min_node->n_value;
	}

	// return whether stack is empty
	// Most definitely O(1)
	bool empty() const {
		return head == NULL;
	}

private:
	Node* head;
	Node* min_node;
};

/*------------------
 * Test code
 *------------------*/

int main(int argc, char* argv[]) {
	Stack<int> stack;

	std::srand(std::time(NULL));

	// push a bunch of random numbers
	std::cout << "Pushing:" << std::endl;
	int x;
	for (int i = 0; i < 10; ++i) {
		x = std::rand() % 100;
		std::cout << x;
		stack.push(x);
		std::cout << "\t(min " << stack.min() << ")" << std::endl;
	}

	// pop them all off
	std::cout << std::endl << "Popping:" << std::endl;
	while (!stack.empty()) {
		std::cout << stack.top() << "\t(min " << stack.min() << ")" << std::endl;
		stack.pop();
	}

	return 0;
}

/*-----------------------------
 * Sample output:
 * Pushing:
 * 87	(min 87)
 * 56	(min 56)
 * 51	(min 51)
 * 70	(min 51)
 * 33	(min 33)
 * 81	(min 33)
 * 55	(min 33)
 * 99	(min 33)
 * 83	(min 33)
 * 44	(min 33)
 * 
 * Popping:
 * 44	(min 33)
 * 83	(min 33)
 * 99	(min 33)
 * 55	(min 33)
 * 81	(min 33)
 * 33	(min 33)
 * 70	(min 51)
 * 51	(min 51)
 * 56	(min 56)
 * 87	(min 87)
 *----------------------------*/