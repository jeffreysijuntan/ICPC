#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

void knapsack(int n, double C, int W[], int V[]) {
    int c = (int) floor(C);
    int m[n+1][c+1];
    for (int j = 0; j <= c; j++) {
        m[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= c; j++) {
            if (W[i] > j) {
                m[i][j] = m[i-1][j];
            } else {
                m[i][j] = std::max(m[i-1][j], m[i-1][j-W[i]] + V[i]);
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= c; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    int count = 0;
    int res = m[n][c];
    int w = c;

    vector<int> indices;

    for (int i = n; i > 0 && res > 0; --i) {
        if (res == m[i-1][w])
            continue;
        else {
            count++;
            indices.push_back(i-1);
            res -= V[i];
            w -= W[i];
        }
    }

    printf("%d \n", count);
    for (int i = 0; i < indices.size(); i++) {
        printf("%d ", indices[i]);
    }
    cout << endl;
}

int main() {
    double C;
    int n;
    while (scanf("%lf %d", &C, &n) != EOF) {
        int V[n+1], W[n+1];
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &V[i], &W[i]);
        }
        knapsack(n, C, W, V);
    }
    return 0;
}
