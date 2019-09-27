/*
1. Read rows and columns (cols) as integer arguments from the command line.
2. Create an unsigned char matrix M of size [rows x cols] (if your language of choice doesn't support the unsigned char type, upgrade the type to the shortest integer type supported by that language).
3. Fill M with randomly selected non-negative integers.
4. Apply the filter K=[-1, 0, 1] along the rows axis, then the cols axis (i.e. convolve the matrix M with K along the vertical & horizontal axis respectively).
5. Store the vertical convolution result computed above in a new matrix Dy and the horizontal convolution result in Dx. You must explicitly compute and store the Dy & Dx matrices.
6. Print the total time taken by the machine in computing Dx and Dy matrices.
7. Compute the min and max values for both Dx & Dy matrices individually (and in separate functions from the above computation of Dx and Dy). Print the computed min & max values.
*/

/*
Assumptions:
1. User first specify how matrix size with integer m, n in the first line
2. Assume m >= 3 && n >= 3
3. Assume no padding is used, thus dx and dy will have dimension (m-2)*n and m*(n-2)
4. Value is set to 0 if overflow happens;
*/

#include <iostream>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <chrono>       /* time */
#include <vector>

using namespace std;

#define MAX 255

using Matrix = vector<vector<unsigned char> >;

int K[3] = {-1, 0, 1};


Matrix convolve(Matrix &M) {
	int m = M.size();
	int n = M[0].size();
	// Initalize output
	vector<vector<unsigned char> > out(m);
	for (int i = 0; i < m; ++i)
		out[i].resize(n-2, 0);

	for (int i = 0; i < m; ++i) {
		for (int j = 1; j < n-1; ++j) {
			//out[i][j-1] = M[i][j-1] * K[0] + M[i][j] * K[1] + M[i][j+1] * K[2]; 
			//for this specific kernel, this is essential the same as:
			out[i][j-1] = M[i][j+1] >= M[i][j-1] ? M[i][j+1] - M[i][j-1] : 0; // if underflow, set value to 0
		}
	}
	return out;
}

void printMatrix(Matrix& M) {
	for (int i = 0; i < M.size(); ++i) {
		for (int j = 0; j < M[i].size(); ++j) {
			cout << (int) M[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix transpose(Matrix& M) {
	int r = M[0].size();
	int c = M.size();

	Matrix N;
	N.resize(r);
	for (int i = 0; i < r; ++i)
		N[i].resize(c);

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			N[i][j] = M[j][i];
		}
	}

	return N;
}

unsigned char maxM(Matrix &M) {
	unsigned char res = 0;
	for (int i = 0; i < M.size(); ++i) {
		res = std::max(res, *std::max_element(M[i].begin(), M[i].end()));
	}
	return res;
}

unsigned char minM(Matrix &M) {
	unsigned char res = MAX;
	for (int i = 0; i < M.size(); ++i) {
		res = std::min(res, *std::min_element(M[i].begin(), M[i].end()));
	}
	return res;
}

int main() {
	int m, n;
	cin >> m >> n;
	Matrix M;
	M.resize(m);
	for (int i = 0; i < m; ++i)
		M[i].resize(n);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			M[i][j] = rand() % (MAX-1) + 1;
		}
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	
	auto dy = convolve(M);
	auto N = transpose(M);
	auto dx = convolve(N);
	dx = transpose(dx);

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

	cout << "Elapsed Time: " << duration << endl;

	cout << "dx max: " << (int) maxM(dx) << endl;
	cout << "dx min: " << (int) minM(dx) << endl;
	cout << "dy max: " << (int) maxM(dy) << endl;
	cout << "dy min: " << (int) minM(dy) << endl;
	
	/*
	printMatrix(M);
	cout << endl; 
	printMatrix(dx);
	cout << endl;
	printMatrix(dy);
	*/
	
}