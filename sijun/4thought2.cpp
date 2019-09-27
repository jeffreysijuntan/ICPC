#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int cal(int op, int num1, int num2) {
	if (op == 1)
		return num1 + num2;
	if (op == 2)
		return num1 - num2;
	if (op == 3)
		return num1 * num2;
	if (op == 4)
		return num1 / num2;
}

int main() {
	int n;
	cin >> n;
	int input[n];
	for (int i = 0; i < n; i++) {
		cin >> input[i];
	}

	std::unordered_map<int, int> solutions;

	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= 4; ++j) {
			for (int k = 1; k <= 4; ++k) {
				std::vector<int> nums = {4, 4, 4, 4};
				std::vector<int> ops = {i, j, k};

				for (int q = 0; q < ops.size(); ++q) {
					if (ops[q] > 2) {
						nums[q] = cal(ops[q], nums[q], nums[q+1]);
						nums.erase(nums.begin()+q+1);
						ops.erase(ops.begin()+q);
						q--;
					}
				}

				for (int q = 0; q < ops.size(); ++q) {
					nums[q] = cal(ops[q], nums[q], nums[q+1]);
					nums.erase(nums.begin()+q+1);
					ops.erase(ops.begin()+q);
					q--;
				}

				solutions[nums[0]] = i * 100 + j * 10 + k;
			}
		}
	}

	char op2char[5] = {'0', '+', '-', '*', '/'};
	for (int i = 0; i < n; ++i) {
		int key = input[i];
		if (solutions.count(key)) {
			int ops = solutions[key];
			int i = ops / 100;
			int j = (ops % 100) / 10;
			int k =  ops % 100 % 10;
			cout << 4 << " " << op2char[i] << " " << 4 <<  " " << op2char[j] << " " << 4  << " " << op2char[k] << " " << 4 << " = " << key << endl;
		} else {
			cout << "no solution" << endl;
		}
	}
}