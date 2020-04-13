#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cmath>

using namespace std;

void badSort(int[], int, int, float);

int main() {        
	int MAX = 10000;
	int A[MAX];
	int sizes[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

	int size= sizeof(sizes) / sizeof(sizes[0]);

	cout << "Alpha = 2/3" << endl;

	for (int i = 0; i < size; i++) {
		cout << sizes[i] << "\t\t";
		for (int j = 0; j < sizes[i]; j++) {
			A[j] = (rand() % 10000);
		}   

		// check running time
		auto start = chrono::system_clock::now();
		badSort(A, 0, sizes[i] - 1, (float)(2.0 / 3));
		auto end = chrono::system_clock::now();
		auto execTime =  std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		cout << execTime.count() << endl;
	}

	cout << "Alpha = 3/4" << endl;
	for (int i = 0; i < size; i++) {
		cout << sizes[i] << "\t\t";
		for (int j = 0; j < sizes[i]; j++) {
			A[j] = (rand() % 10000);
		}   

		// check running time
		auto start = chrono::system_clock::now();
		badSort(A, 0, sizes[i] - 1, (float)(3.0 / 4));
		auto end = chrono::system_clock::now();
		auto execTime =  std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		cout << execTime.count() << endl;
	}
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
