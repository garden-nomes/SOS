/*
 * Problem 3.5
 * Noah Weiner
 *
 * Given two sorted lists, L 1 and L 2 , write a procedure to 
 * compute L 1 ∪ L 2 using only the basic list operations.
 *
 * Output:
 *
 * a: [0, 3, 6, 9, 12, 15, 18, 21, 24, 27]
 * b: [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28]
 * concat(a, b): [0, 2, 3, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 26, 27, 28]
 */

#include <iostream>
#include <list>
#include <cstring>
using namespace std;

/*
 * Concatenate two sorted lists into a third sorted list.
 */
template<typename Object>
list<Object> concat(const list<Object>& a, const list<Object>& b) {
	auto itr_a = a.begin();
	auto itr_b = b.begin();
	list<Object> ret;

	while (itr_a != a.end() or itr_b != b.end()) {
		if (*itr_a == *itr_b) {
			ret.push_back(*itr_a);
			++itr_a;
			++itr_b;
		} else if (*itr_a > *itr_b)
			ret.push_back(*itr_b++);
		else
			ret.push_back(*itr_a++);
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
	for (int i = 0; i < 30; i++) {
		if (i % 3 == 0) a.push_back(i);
		if (i % 2 == 0) b.push_back(i);
	}

	printList("a", a);
	printList("b", b);
	printList("concat(a, b)", concat(a, b));

	return 0;
}
