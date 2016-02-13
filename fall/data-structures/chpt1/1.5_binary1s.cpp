#include <iostream>
using namespace std;

int binary_1s(const int num, int ones = 0) {
	ones += num % 2;
	
	if (num < 2) {
		return ones;
	} else {
		return binary_1s(num / 2, ones);
	}
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < 256; i++) {
		cout << i << ": " << binary_1s(i) << "\t";
	}

	cout << endl;

	return 0;
}
