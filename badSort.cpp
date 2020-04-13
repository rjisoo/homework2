#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

void badSort(int[], int, int, float);
int getNumber(std::string);

int main() {
	// open files
	std::ifstream fin;
	fin.open("data.txt");
	std::ofstream fout;
	fout.open("bad.out");

	int MAX = 10000;
	int A[MAX];
	int num, elm, numerator, denominator;
	float alpha = 1.0;

	// get user input for alpha
	while (!(alpha < 1 && alpha > 0)) {
		numerator = getNumber("Numerator");
		denominator = getNumber("Denominator");
		if (denominator == 0) {
			std::cout << "Invalid denominator" << std::endl;
			alpha = 1.0;
		} else {
			alpha = (float)numerator/denominator;
			std::cout << "Alpha: " << numerator << "/" << denominator << std::endl;

			if (alpha >= 1 || alpha <= 0) {
				std::cout << "Please enter the value between 0 < a < 1\n";
			}
		}
	}

	// read numbers until the right of file
	while (!fin.eof()) {
		// first value of the line
		fin >> num;

		// copy integers in to the array
		for (int i = 0; i < num; i++) {
			fin >> A[i];
		}

		badSort(A, 0, num - 1, alpha);

		// export sorted array to bad.out file
		for (int i = 0; i < num; i++) {
			fout << A[i] << " ";
		}
		fout << std::endl;
	}

	fin.close();
	fout.close();

	return 0;
}

void badSort(int A[], int left, int right, float alpha) {
	int n = (right - left + 1);

	// if (n = 2) and (A[0] > A[1])
	// swap A[0] and A[1]
	if (n == 2 && A[left] > A[right]) {
		int temp = A[left];
		A[left] = A[right];
		A[right] = temp;
	}

	// else if (n > 2)
	// m = ⌈𝛼 · 𝑛⌉
	// badSort(A[0 ··· m − 1])
	// badSort(A[n – m ··· n − 1])
	// badSort(A[0 ··· m − 1])
	else if (n > 2) {
		int m = ceil(alpha * n);
		if (m == n) {
			m = m - 1;
		}
		badSort(A, left, left + m - 1, alpha);
		badSort(A, right - m + 1, right, alpha);
		badSort(A, left, left + m - 1, alpha);
	}
}

int getNumber(std::string inputType) {
	// receive cin and error check for invalid inputs
	std::cout << "Enter an int (" << inputType << "): " ;
	int x = 0;
	while(!(std::cin >> x)){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.  Try again: ";
	}
	std::cout << "You enterd: " << x << std::endl;
	return x;
}
