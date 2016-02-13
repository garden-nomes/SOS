#include <iostream>
using namespace std;


/*
 * minimal list using an array representation
 * fixed size
 * This version expects the head to be at index position 0
 * which then requires a move for each cons and tail. A more efficient
 * version will keep the head at the "right" end. But I wanted everyone
 * to see how straightforward it is to design it at the left end with a copy.
 * 
 * This also does not check for if a cons exceeds capacity: if it does
 * the program will get a segmentation violation, which isn't terrible. In
 * general though you want to program for an exception.
 */

template<class Object>
class List {
public:
	List(int sz=15) {
		elements = new Object[sz];
		theSz = 0;
		capacity = sz;
	}

	~List() {
		delete elements;
	}
	
	bool isEmpty() const {
		return theSz == 0;
	}

	Object head() const {
		if (!isEmpty()) {
			return elements[0];
		}
		return (Object)NULL;	// This is really a temporary patch
				// really head is a partial function
				// and this should throw an exception
	}

	void tail() {
		lcopy();
		theSz--;
	}

	void cons(Object o) {
		// No check for capacity
		rcopy();
		elements[0] = o;
		theSz++;
	}

	void printList() {
		for (int i=0; i<theSz; i++) {
			std::cout << elements[i] << ", ";
		}
		std::cout << std::endl;
	}

	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin() { return elements; }
	iterator end() { return &elements[theSz]; }

private:
	Object * elements;
	int theSz;
	int capacity;

	/*
 	 * lcopy() from 0 to theSz;
	 */
	void lcopy() {
		for (int i = 0; i<theSz-1; i++) {
			elements[i] = elements[i+1];
		}
	}
	
	/*
	 * rcopy() from theSz downto 0
	 */
	void rcopy() {
		for (int i=theSz; i>0; i--) {	
			elements[i] = elements[i-1];
		}
	}
};

int main(int argc, char* argv[]) {
	List<int> list = List<int>(20);
	for (int i = 1; i <= 10; i++)
		list.cons(i);

	for (List<int>::iterator i = list.begin(); i != list.end(); i++)
		cout << *i << " ";
	cout << endl;

	return 0;
}
