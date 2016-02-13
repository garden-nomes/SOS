/* Problem 5.17
 * Noah Weiner
 *
 * An (old-style) BASIC program consists of a series of statements numbered in ascending
 * order. Control is passed by use of a goto or gosub and a statement number. Write a
 * program that reads in a legal BASIC program and renumbers the statements so that the
 * first starts at number F and each statement has a number D higher than the previous
 * statement. You may assume an upper limit of N statements, but the statement numbers
 * in the input might be as large as a 32-bit integer. Your program must run in linear
 * time.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
using namespace std;

int main(int argc, char** argv) {
	// read in arguments

	ifstream infile;
	int f, d;

	if (argc != 4) {
		cout << "usage: " << argv[0] << " <infile> <F> <D>" << endl;
		return 1;
	}

	infile.open(argv[1]);
	if (!infile.is_open()) {
		cout << "Sorry, couldn't open " << argv[1] << " for reading." << endl;
		return 1;
	}

	f = atoi(argv[2]);
	d = atoi(argv[3]);

	// process file

	map<unsigned long, string> statements;
	unsigned long key;
	string statement;
	string line;
	size_t sz;

	while (getline(infile, line)) {
		if (!line.empty()) {
			key = stoul(line, &sz);
			statement = line.substr(sz);
			statements[key] = statement;
		}
	}

	// output new statement numbers 

	for (auto itr : statements) {
		cout << f << itr.second << endl;
		f += d;
	}

	// finish up

	infile.close();
	return 0;
}