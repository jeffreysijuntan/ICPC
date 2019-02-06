#include <iostream>
using namespace std;

int parent[200005];
int id[200005];
int num[200005];
long long sum[200005];
int dl;

int find(int x) {
	x = id[x];
	while (parent[x] != x) {
		x = parent[x];
	}
	return x;
}

void numsum(int p) {
	int rootp = find(p);
	printf("%d %lld \n", num[rootp], sum[rootp]);
}

void join(int a, int b) {
	int rootb = find(b);
	int roota = find(a);
	if (roota != rootb) {
		parent[rootb] = roota;
		num[roota] += num[rootb];
		sum[roota] += sum[rootb];
	}
}

void move(int p, int q) {
	int rootp = find(p);
	int rootq = find(q);
	if (rootp != rootq) {
		sum[rootp] -= (long long)p;
		num[rootp] -= 1;
		sum[rootq] += (long long)p;
		num[rootq] += 1;

		id[p] = rootq;

		/*
		id[p] = ++dl;
		sum[id[p]] = (long long) p;
		num[id[p]] = 1;
		parent[id[p]] = id[p];
		join(q, p);
		*/
	}
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i < n+1; i++) {
			id[i] = parent[i] = i;
			sum[i] = (long long) i;
			num[i] = 1; 
		}
		dl = n;

		int cmd, p, q;
		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			switch (cmd) {
				case 1:
					scanf("%d %d", &p, &q);
					join(p, q);
					break;
				case 2:
					scanf("%d %d", &p, &q);
					move(p, q);
					break;
				case 3:
					scanf("%d", &p);
					numsum(p);
					break;
				default:
					break;
			}
		}
	}
	return 0;
}
