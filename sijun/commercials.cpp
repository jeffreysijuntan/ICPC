#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
    int N, P;
    scanf("%d %d", &N, &P);

    int p[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
    }

    int dp[N];
    dp[0] = p[0] - P;
    for (int i = 1; i < N; i++) {
        dp[i] = std::max(dp[i-1]+p[i]-P, p[i]-P);
    }

    cout << std::max(0, *std::max_element(dp, dp+N));
}