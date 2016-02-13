/*
 * Midterm problem 2
 * Noah Weiner
 *
 * Implement a simple stack (ie just push, pop, top, isEmpty). You may use either a vector or a list.
 * Assume there is no max size. Do not implement an iterator. Your stack should be templated and should
 * implement the big-3 or big-5. Use your stack to write a simple paren-matching program. Give the big-O
 * of your methods.
 *
 * All member functions are constant time except for The copy constructor and destructor, which are O(n).
 */

#include <iostream>
#include <string>
using namespace std;

template<typename Object>
class Stack {
	private:
	
	struct Node {
		Object data;
		Node* next;
		Node(const Object& d = Object(), Node* n = NULL)
			: data(d), next(n) { }
	};

	public:	

	Stack() { head = NULL; }
	~Stack() { while (!isEmpty()) pop(); }
	Stack(const Stack& rhs) {
		Node* n = rhs.head;
		while (n != NULL) {
			push(n->data);
			n = n->next;
		}
	}

	bool isEmpty() { return head == NULL; }

	Stack& pop() {
		Node* n = head;
		head = head->next;
		delete n;
	}

	Object& top() {
		return head->data;
	}

	void push(const Object& d) {
		Node* n = new Node(d, head);
		head = n;
	}

	private:
	Node* head;

};

/*
 * Parem-matching program
 */
bool parems_matched(string s) {
	Stack<char> lparems;
	for (auto c = s.begin(); c != s.end(); c++) {
		if (*c == '(') lparems.push(*c);
		else if (*c == ')') {
			if (lparems.isEmpty()) return false;
			else lparems.pop();
		}
	}

	return lparems.isEmpty() ? true : false;
}

/*
 * Test code
 */
int main(int arc, char** argv) {
	string valid = "(4+5) * ((9+12)*2)";
	string invalid = "(4+5) * ((9+12)*2";
	cout << valid << ": " << parems_matched(valid) << endl;
	cout << invalid << ": " << parems_matched(invalid) << endl;

	return 0;
}
