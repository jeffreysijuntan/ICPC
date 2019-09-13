#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, B;
    scanf("%d", &H);

    int sumH = 0;
    int arrH[H];
    for (int i = 0; i < H; i++) {
        scanf("%d", &arrH[i]);
        sumH += arrH[i];
    }

    scanf("%d", &B);
    int sumB = 0;
    int arrB[B];
    for (int i = 0; i < B; i++) {
        scanf("%d", &arrB[i]);
        sumB += arrB[i];
    }

    int sum = std::min(sumB, sumH);
    int dpH[H+1][sum+1];
    int dpB[B+1][sum+1];


    for (int i = 0; i <= H; i++) {
        for (int j = 0; j <= sum; j++) {
            if (j == 0)
                dpH[i][j] = 0;
            else
                dpH[i][j] = -1;
        }
    }

    for (int i = 0; i <= B; i++) {
        for (int j = 0; j <= sum; j++) {
            if (j == 0)
                dpB[i][j] = 0;
            else
                dpB[i][j] = -1;
        }
    }


    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < arrH[i-1]) {
                dpH[i][j] = dpH[i-1][j];
            } else {
                if (dpH[i-1][j] == -1 && dpH[i-1][j-arrH[i-1]] == -1)
                    dpH[i][j] = -1;
                else if (dpH[i-1][j] == -1)
                    dpH[i][j] = dpH[i-1][j-arrH[i-1]] + 1;
                else if (dpH[i-1][j-arrH[i-1]] == -1)
                    dpH[i][j] = dpH[i-1][j];
                else
                    dpH[i][j] = std::min(dpH[i-1][j], dpH[i-1][j-arrH[i-1]]+1);
            }
        }
    }

    for (int i = 1; i <= B; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < arrB[i-1]) {
                dpB[i][j] = dpB[i-1][j];
            } else {
                if (dpB[i-1][j] == -1 && dpB[i-1][j-arrB[i-1]] == -1)
                    dpB[i][j] = -1;
                else if (dpB[i-1][j] == -1)
                    dpB[i][j] = dpB[i-1][j-arrB[i-1]] + 1;
                else if (dpB[i-1][j-arrB[i-1]] == -1)
                    dpB[i][j] = dpB[i-1][j];
                else
                    dpB[i][j] = std::min(dpB[i-1][j], dpB[i-1][j-arrB[i-1]]+1);
            }
        }
    }

    /*
    for (int i = 0; i <= H; i++) {
        for (int j = 0; j <= sum; j++) {
            cout << dpH[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i <= B; i++) {
        for (int j = 0; j <= sum; j++) {
            cout << dpB[i][j] << " ";
        }
        cout << endl;
    }      
    */

    int res = INT_MAX;
    for (int i = 1; i <= sum; i++) {
        if (dpH[H][i] != -1 && dpB[B][i] != -1) {
            res = std::min(dpH[H][i]+dpB[B][i], res);
        }
    }

    if (res == INT_MAX)
        printf("%s", "impossible");
    else
        printf("%d", res);
    
    return 0;
}