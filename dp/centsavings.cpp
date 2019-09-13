#include <iostream>
using namespace std;

int round(int n) { 
    // Smaller multiple 
    int a = (n / 10) * 10; 
    // Larger multiple 
    int b = a + 10; 
    // Return of closest of two 
    return (n - a >= b - n)? b : a; 
} 

int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    
    int p[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int dp[n][d+2];

    int cumsum[n];
    cumsum[0] = p[0];
    dp[0][1] = round(p[0]);
    
    for (int i = 1; i < n; i++) {
        cumsum[i] = cumsum[i-1] + p[i];
        dp[i][1] = round(cumsum[i]);
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j][1] << " ";
        }
        cout << endl;
    }*/

    for (int k = 2; k <= std::min(d+1, n); k++) {
        for (int i = 0; i < n; i++) {
            int min = 2147483647;
            for (int l = k-2; l < i; l++) {
                min = std::min(dp[l][k-1] + round(cumsum[i]-cumsum[l]), min);
            }
            dp[i][k] = min;
        }
    }

    /*
    cout << endl;
    for (int k = 1; k <= d+1; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << dp[i][j][k] << " ";
            }
            cout << endl;
        } 
        cout << endl;
    }
    */
    int min = 2147483647;
    for (int i = 1; i <= std::min(d+1, n); i++) {
        min = std::min(min, dp[n-1][i]);
    }
    printf("%d", min);

}