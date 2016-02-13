/*
 * Problem 3.1
 * Noah Weiner
 *
 * You are given a list, L, and another list, P, containing
 * integers sorted in ascending order. The operation printLots(L,P)
 * will print the elements in L that are in positions specified by P.
 * For instance, if P = 1, 3, 4, 6, the elements in positions 1, 3, 4,
 * and 6 in L are printed. Write the procedure printLots(L,P). You may
 * use only the public STL container operations. What is the running
 * time of your procedure?
 *
 * Runtime: 0.25 seconds
 */


#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace std;

#define TEST_SIZE 1000000

template<typename Object>
void printLots(const vector<Object>& L, const vector<int> & P, ostream& out = cout) {
	auto itr = P.begin();
	while (itr != P.end())
		out << L[*itr++] << "\t";
	out << endl;
}

int main(int argc, char* argv[]) {
	// create test arrays
	vector<int> L = vector<int>(TEST_SIZE);
	int i = 0;
	auto itr = L.begin();
	while (itr != L.end())
		*itr++ = i++;

	vector<int> P = vector<int>(TEST_SIZE / 5);
	i = 0;
	itr = P.begin();
	while (itr != P.end()) {
		*itr++ = i;
		i += 5;
	}
		
	// measure runtime
	cout << "Starting test..." << endl;
	clock_t time = clock();
	printLots(L, P);
	time = clock() - time;
	printf("\nRuntime: %8f seconds.\n", (float)time / CLOCKS_PER_SEC);

	return 0;
}
