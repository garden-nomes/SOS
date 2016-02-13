#include <cstdio>
#include <iostream>
#include "intCell.h"
using namespace std;

int main(int argc, char** argv) {
    IntCell arr[3];

	// read three numbers
    int input;
	for (int i = 0; i < 3; i++) {
		cin >> input;
		arr[i] = IntCell(input);
	}

	// print the numbers forwards and backwards
    cout << arr[0].read() << " " << arr[1].read() << " " << arr[2].read() << endl;
    cout << arr[2].read() << " " << arr[1].read() << " " << arr[0].read() << endl;

    // find min, max and total
    IntCell total = IntCell(0);
    IntCell min = arr[0], max = arr[0];
    for (int i = 0; i < 3; i++) {
        if (arr[i].read() > max.read()) max = arr[i];
        if (arr[i].read() < min.read()) min = arr[i];
        total = total.add(arr[i]);
    }
    
    cout << "max: " << max.read() << endl;
    cout << "min: " << min.read() << endl;
    cout << "avg: " << (float)total.read() / 3.0 << endl;

    return 0;
}
