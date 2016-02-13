/*
 * Problem 3.4
 * Noah Weiner
 *
 * Given two sorted lists, L1 and L2, write a procedure to compute L1 ∩ L2 using
 * only the basic list operations.
 *
 * Output:
 *
 * a: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
 * b: [0, 2, 4, 6, 8, 10, 12, 14, 16, 18]
 * intersection(a, b): [0, 2, 4, 6, 8]
 */

#include <iostream>
#include <cstring>
#include <list>
using namespace std;

/*
 * Returns a list of the common elements of two sorted lists.
 */
template<typename Object>
list<Object> intersection(const list<Object>& a, const list<Object>& b) {
	auto itr_a = a.begin();
	auto itr_b = b.begin();
	list<Object> ret;

	while (itr_a != a.end() && itr_b != b.end()) {
		if (*itr_a == *itr_b) {
			ret.push_back(*itr_a++);
			++itr_b;
		}
		else if (*itr_a < *itr_b)
			++itr_a;
		else
			++itr_b;
	}

	return ret;
}

template<typename Object>
void printList(string s, list<Object> list, ostream& out = cout) {
	auto itr = list.begin();
	cout << s << ": [" << *itr++;
	while (itr != list.end())
		cout << ", " << *itr++;
	cout << "]" << endl;
}

int main(int argc, char* argv[]) {
	list<int> a;
	list<int> b;
	for (int i = 0; i < 20; i++) {
		if (i < 10) a.push_back(i);
		if (i % 2 == 0) b.push_back(i);
	}

	printList("a", a);
	printList("b", b);
	printList("intersection(a, b)", intersection(a, b));

	return 0;
}
