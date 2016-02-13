/*
 * Problem 3.22
 * Noah Weiner
 *
 * Write a program to evaluate a postfix expression.
 *
 * AND
 *
 * Problem 3.23
 *
 * a. Write a program to convert an infix expression that includes
 *    (, ), +, -, *, and / to postfix.
 * b. Add the exponentiation operator to your repertoire.
 * c. Write a program to convert a postfix expression to infix.
 */

#include <iostream>
#include <cstdlib>
#include <stack>
#include <cstring>
#include <cmath>
using namespace std;

/*
 * Utility functions
 *
 */

/*
 * Takes an array of strings, outputs them in format <title>: [s1] [s2] ... [sN]
 */
void print_strings(char** s, int length, string title = "") {
	if (title != "") cout << title << ": ";
	if (length > 0) {
		cout << s[0];
		for (int i = 1; i < length; i++)
			cout << ' ' << s[i];
	}
	cout << endl;
}

/*
 * Pops an element off a stack and returns the value that was popped.
 */
template <typename Object>
Object pop(stack<Object>& s) {
	Object o = s.top();
	s.pop();
	return o;
}

void print_stack(stack<char*> s, string title = "") {
	if (title != "") cout << title << ": ";
	if (!s.empty())
		cout << pop(s);
	while (!s.empty())
		cout << " " << pop(s);
	cout << endl;
}

/*
 * Postix evaluation
 *
 * Given expresions expr as an array of strings, and the length of the
 * expression, returns the integer value the expression evaluates to.
 */
int evaluate_postfix(char** expr, int length) {
	stack<int> s;
	for (int i = 0; i < length; i++) {
		// test for integer
		char* p;
		int x = strtol(expr[i], &p, 10);
		if (*p == 0) s.push(x);

		// else apply operator
		else {
			switch (*expr[i]) {
				case '+':
					s.push(pop(s) + pop(s));
					break;
				case '-':
					s.push(pop(s) - pop(s));
					break;
				case '/':
					s.push(pop(s) / pop(s));
					break;
				case '*':
					s.push(pop(s) * pop(s));
					break;
				case '^':
					s.push(pow(pop(s), pop(s)));
				default:
					cout << "Invalid input: " << expr[i] << endl;
					break;
			}
		}
	}

	if (s.top())
		return s.top();
	else {
		cout << "Invalid expression." << endl;
		return 0;
	}
}

/*
 * A sort of functional data structure for operator precedence.
 */
int operator_precedence(char op) {
	switch (op) {
		case '+':
			return 2;
		case '-':
			return 2;
		case '*':
			return 1;
		case '/':
			return 1;
		case '^':
			return 0;
		case '(':
			return 3;
		case ')':
			return 3;
		default:
			return -1;
	}
}

string infix_to_postfix(string expr) {
	stack<char> operators;
	string postfix;
	string num_buffer;

	for (auto c = expr.begin(); c != expr.end(); ++c) {

		// check for operator
		if (operator_precedence(*c) >= 0) {
			// write number buffer
			if (!num_buffer.empty()) {
				if (!postfix.empty()) postfix += " ";
				postfix += num_buffer;
				num_buffer.clear();
			}

			// handle operator
			if (*c == ')') {	// special case ')'
				while (operators.top() != '(') {
					if (!postfix.empty()) postfix += " ";
					postfix += pop(operators);
					if (operators.empty()) {
						cout << "Error: unmatched ')' in expression." << endl;
						return postfix;
					}
				}

				operators.pop();	// remove '('
			} else if (*c == '(') {	// special case '('
				operators.push(*c);
			} else {
				// pop operators until we reach one of higher precedence
				// or the end of the stack
				while (!operators.empty()
						&& operator_precedence(*c) >= operator_precedence(operators.top())) {
					if (!postfix.empty()) postfix += " ";
					postfix += pop(operators);
				}
			
				operators.push(*c);	// add operator to the stack
			}
		}
		
		// check for digit
		else if ('0' <= *c && *c <= '9')
			num_buffer += *c;	// keep a buffer for multi-digit integers

		// check for delimeter
		else {
			// write number buffer
			if (!num_buffer.empty()) {
				if (!postfix.empty()) postfix += " ";
				postfix += num_buffer;
				num_buffer.clear();
			}
		}

	}

	// write last number
	if (!num_buffer.empty()) {
		if (!postfix.empty()) postfix += " ";
		postfix += num_buffer;
	}
	
	// pop all remaining operators
	while (!operators.empty()) {
		if (!postfix.empty()) postfix += " ";
		postfix += pop(operators);
	}
	
	return postfix;
}

int main(int argc, char** argv) {
	if (argc < 2 || (strcmp(argv[1], "--infix") == 0 && argc < 3)) {
		cout << "Usage: " << argv[0] << " [--infix] <integer expression>" << endl;
		return 0;
	}

	if (strcmp(argv[1], "--infix") == 0) {
		string postfix;
		cout << (postfix = infix_to_postfix(argv[2]))
			 << " = " << evaluate_postfix(postfix) << endl;
	} else
		cout << "Evaluation: " << evaluate_postfix(++argv, argc - 1) << endl;

	return 0;
}
