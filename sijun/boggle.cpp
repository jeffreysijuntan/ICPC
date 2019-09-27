#include <iostream>
#include <unordered_set>
using namespace std;

void dfs(char (&grid)[4][4], int x, int y, string curr, unordered_set<string>& prefixSet, unordered_set<string>& wordSet, unordered_set<string>& foundWord, unordered_set<int> visited) {
	curr = curr + grid[x][y];
	visited.insert((x+1)*10 + y+1);
	if (wordSet.count(curr)) {
		foundWord.insert(curr);
	}
	if (!prefixSet.count(curr)) {
		return;		
	}
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			if (dx == 0 && dy == 0) 
				continue;
			if (x+dx < 0 || x+dx >= 4 || y+dy < 0 || y+dy >= 4) {
				continue;
			}
			if (!visited.count((x+dx+1)*10 + (y+dy+1)))
				dfs(grid, x+dx, y+dy, curr, prefixSet, wordSet, foundWord, visited);
		}
	}
}

int maxScore(unordered_set<string>& foundWord) {
	int score = 0;
	for (auto word : foundWord) {
		int l = word.size();
		if (l == 3 || l == 4) {
			score++;
		}
		else if (l >= 5 && l <= 6) {
			score += 2 + l - 5;		
		}
		else if (l == 7) {
			score += 5;
		}
		else if (l == 8) {
			score += 11;
		}
	}
	return score;
}

string maxL(unordered_set<string>& foundWord) {
	int maxL = 0;
	string maxWord = "";
	for (auto word : foundWord) {
		if (word.size() >= maxL) {
			if (word.size() == maxL) {
				maxWord = min(word, maxWord);
			} else {
				maxWord = word;
			}
			maxL = word.size();
		}
	}
	return maxWord;
}

int main() {
	int n;
	cin >> n;
	string words[n];

	unordered_set<string> prefixSet;
	unordered_set<string> wordSet;
	for (int i = 0; i < n; ++i) {
		string word;
		cin >> word;
		wordSet.insert(word);
		for (int j = 0; j < word.size() - 1; ++j) {
			prefixSet.insert(word.substr(0, j+1));
		}
	}

	int m;
	cin >> m;

	for (int i = 0; i < m; ++i) {
		char grid[4][4];
		for (int j = 0; j < 4; ++j) {
			string row;
			cin >> row;
			for (int k = 0; k < 4; ++k)
				grid[j][k] = row[k];
		}

		unordered_set<string> foundWord;
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				unordered_set<int> visited;
				dfs(grid, x, y, "", prefixSet, wordSet, foundWord, visited);
			}
		}

		int maxS = maxScore(foundWord);
		string maxWord = maxL(foundWord);
		cout << maxS << " " << maxWord << " " << foundWord.size() << endl; 
	}
}