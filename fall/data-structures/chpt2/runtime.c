/* Test the runtime of several algorithms for data structures hw 2.7 */

#include <stdio.h>
#include <time.h>
#include <math.h>

void func1(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum++;
}

void func2(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			sum++;
}

void func3(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n * n; j++)
			sum++;
}

void func4(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			sum++;
}

void func5(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i * i; j++)
			for (int k = 0; k < j; k++)
				sum++;
}

void func6(int n) {
	int sum = 0;
	for (int i = 1; i < n; i++)
		for (int j = 1; j < i * i; j++)
			if (j % i == 0)
				for (int k = 0; k < j; k++)
					sum++;
}

int main(int argc, char** argv) {
	clock_t begin, end;
	double runtimes[4][6];

	for (int i = 0; i < 4; i++) {
		int n = pow(4, i + 1);
		printf("For N = %d:\n", n);

		printf("Evaluating algorithm 1...\n");
		begin = clock();
		func1(n);
		end = clock();
		runtimes[i][0] = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("Evaluating algorithm 2...\n");
		begin = clock();
		func2(n);
		end = clock();
		runtimes[i][1] = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("Evaluating algorithm 3...\n");
		begin = clock();
		func3(n);
		end = clock();
		runtimes[i][2] = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("Evaluating algorithm 4...\n");
		begin = clock();
		func4(n);
		end = clock();
		runtimes[i][3] = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("Evaluating algorithm 5...\n");
		begin = clock();
		func5(n);
		end = clock();
		runtimes[i][4] = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("Evaluating algorithm 6...\n\n");
		begin = clock();
		func6(n);
		end = clock();
		runtimes[i][5] = (double)(end - begin) / CLOCKS_PER_SEC;
	}

	printf("N\t\t| 1\t\t| 2\t\t| 3\t\t| 4\t\t| 5\t\t| 6\t\t\n");
	for (int i = 0; i < 4; i++) {
		printf("%d\t\t| %f\t| %f\t| %f\t| %f\t| %f\t| %f\t\n",
				(int)pow(4, i + 1), runtimes[i][0], runtimes[i][1], runtimes[i][2],
				runtimes[i][3], runtimes[i][4], runtimes[i][5]);
	}

	return 0;
}
