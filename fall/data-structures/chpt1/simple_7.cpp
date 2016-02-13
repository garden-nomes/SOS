#include <iostream>
using namespace std;

template <typename T>
class MemoryCell {
	public:
		explicit MemoryCell(const T& initialValue = T())
			: storedValue(initialValue) {}
		const T& read() const
			{ return storedValue; }
		void write(const T& x)
			{ storedValue = x; }

		// operators
		
		bool operator<(const MemoryCell<T>& rhs) const
			{ return storedValue < rhs.storedValue; }
		bool operator<=(const MemoryCell<T>& rhs) const
			{ return storedValue <= rhs.storedValue; }
		bool operator==(const MemoryCell<T>& rhs) const
			{ return storedValue == rhs.storedValue; }
		bool operator!=(const MemoryCell<T>& rhs) const
			{ return storedValue != rhs.storedValue; }
		friend ostream& operator<<(ostream& os, const MemoryCell<T>& memoryCell)
			{ return os << memoryCell.storedValue; }
		ostream& print(ostream& os)
			{ return os << storedValue; }

	private:
		T storedValue;
};

void printExpr(string s, bool expr) {
	cout << s << ": " << (expr ? "true" : "false") << endl;
}

int main(int argc, char* argv[]) {
	MemoryCell<int> a(6);
	MemoryCell<int> b(7);
	MemoryCell<string> c("c");

	cout << "a: " << a << ", b: " << b << endl << endl;
	printExpr("a < b", a < b);
	printExpr("a <= b", a <= b);
	printExpr("a == b", a == b);
	printExpr("a != b", a != b);

	cout << "c: " << c << endl;

	return 0;
}
