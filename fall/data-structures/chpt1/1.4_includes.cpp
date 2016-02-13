#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string process_file(string fname);
string parse_line(string line);

int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "usage: " << argv[0] << " <filename>" << endl;
		return 0;
	}

	cout << process_file(argv[1]);

	return 0;
}

string process_file(string fname) {
	ifstream infile;
	string ret = "";

	infile.open(fname.c_str());
	if (infile.is_open()) {
		string line;
		while (getline(infile, line)) {
			ret += parse_line(line);
		}
	} else {
		return "/* INLCUDE ERROR: Could not find " + fname + " */\n";
	}

	return ret;
}


string parse_line(string line) {
	string buf = "";
	string fname = "";

	for (int i = 0; i < line.length(); i++) {
		char& c = line[i];
		if (buf == "#include <" || buf == "#include \"") {
			if (c == '>' || c == '\"') {
				return process_file(fname);
			} else {
				fname += c;
			}
		} else {
			buf += c;
		}
	}

	return line + "\n";
}
