#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

const int maxN = 100000;
const double eps = 1e-4;

typedef long double ld;

const unordered_map<int, string> p_table = {
	{439, "A"},
	{440, "A"},
	{466, "Bb"},
	{493, "B"},
	{494, "B"},
	{523, "C"},
	{554, "Db"},
	{587, "D"},
	{622, "Eb"},
	{659, "E"},
	{698, "F"},
	{739, "Gb"},
	{740, "Gb"},
	{783, "G"},
	{784, "G"},
	{830, "Ab"},
};

const unordered_set<string> Gma({"G", "A", "B", "C", "D", "E", "Gb"});
const unordered_set<string> Cma({"C", "D", "E", "F", "G", "A", "B"});
const unordered_set<string> Ema({"Eb", "F", "G", "Ab", "Bb", "C", "D"});
const unordered_set<string> Fmi({"Gb", "Ab", "A", "B", "Db", "D", "E"});
const unordered_set<string> Gmi({"G", "A", "Bb", "C", "D", "Eb", "F"});

// normalize frequency to the range [440, 880]
ld norm(ld freq) {
	if (freq < 27.5)
		freq *= 32;
	else if (freq >= 27.5 && freq < 55)
		freq *= 16;
	else if (freq >= 55 && freq < 110)
		freq *= 8;
	else if (freq >= 110 && freq < 220)
		freq *= 4;
	else if (freq >= 220 && freq < 440)
		freq *= 2;
	else if (freq >= 880 && freq < 1760)
		freq /= 2;
	else if (freq >= 1760 && freq < 3520)
		freq /= 4;
	else if (freq > 3520)
		freq /= 8;
	return freq;
}

// Match frequency to the given pitch
string match(ld freq) {
	int f = (int) norm(freq+eps);
	return p_table.at(f);
}

bool isSubset(unordered_set<string> s1, unordered_set<string> s2) {
	for (auto & e : s1) {
		if (!s2.count(e))
			return false;
	} 
	return true;
}

string getKey(unordered_set<string>& pitches) {
	string key = "";
	int cnt = 0;
	if (pitches.size() > 7)
		return "";
	if (isSubset(pitches, Gma)) {
		cnt++;
		key = "G major";
	}
	if (isSubset(pitches, Cma)) {
		cnt++;
		key = "C major";
	}
	if (isSubset(pitches, Ema)) {
		cnt++;
		key = "Eb major";
	}
	if (isSubset(pitches, Fmi)) {
		cnt++;
		key = "F# minor";
	}
	if (isSubset(pitches, Gmi)) {
		cnt++;
		key = "G minor";
	}
	if (cnt > 1) return "";
	return key;
}

int main() {
	int n;
	cin >> n;
	
	vector<string> song(n, "");
	unordered_set<string> pitches;
	ld freq;
	for (int i = 0; i < n; ++i) {
		cin >> freq;
		string p = match(freq+eps);
		pitches.insert(p);
		song[i] = p;		
	}
	
	string k = getKey(pitches);
	if (k == "")
		cout << "cannot determine key";
	else {
		cout << k << endl;
		for (auto & p : song) {
			if (k == "G major" && p == "Gb") {
				cout << "F#" << endl;
			}
			else if (k == "F# minor") {
				if (p == "Gb") cout << "F#" << endl;
				else if (p == "Ab") cout << "G#" << endl;
				else if (p == "Db") cout << "C#" << endl;
				else cout << p << endl;
			}
			else
				cout << p << endl;
		}
	}	
}
