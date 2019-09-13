#include <iostream>
#include <unordered_set>
#include <algorithm>
using namespace std;

void build_table(int (&arr)[6][6][13], int limit) {
    int a, b;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 13; k++) {
                if (k == 0) {
                    arr[i][j][k] = 0;
                }
                arr[i][j][k] = -1;
            }
        }
    }
    for (int i = 0; i < limit; i++) {
        scanf("%d %d", &a, &b);
        for (int j = 1; j < 13; ++j) {
            scanf("%d", &arr[a][b][j]);
        }
    }
}

void testBuildTable(int (&arr)[6][6][12]) {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            for (int k = 0; k < 13; k++) {
                cout << arr[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void testItvs(int *itvs, int size) {
    for (int i = 0; i < size; i++) {
        cout << itvs[i] << " ";
    } 
    cout << endl;
}

int main() {
    int ww; int wb; int bw; int bb; int L;
    scanf("%d %d %d %d %d", &ww, &wb, &bw, &bb, &L);

    int WW[6][6][13];
    int WB[6][6][13];
    int BW[6][6][13];
    int BB[6][6][13];

    build_table(WW, ww);
    build_table(WB, wb);
    build_table(BW, bw);
    build_table(BB, bb);

    //testBuildTable(WW);
    //testBuildTable(WB);
    //testBuildTable(BW);
    //testBuildTable(BB);

    int p[L];
    int itvs[L-1];
    for (int i = 0; i < L; i++) {
        scanf("%d", &p[i]);
        if (i >= 1) {
            itvs[i-1] = (p[i] - p[i-1]);
        }
    }

    for (int i = 0; i < L; i++) {
        p[i] = p[i] % 12;
    }

    //testItvs(itvs, L-1);

    unordered_set<int> blacks({0,2,5,7,10});
    
    int dp[L][6];

    for (int i = 0; i < 6; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i < L; i++) {
        int itv = itvs[i-1];
        if (blacks.find(p[i-1]) != blacks.end()) {
            if (blacks.find(p[i]) != blacks.end()) {
                // black -> black
                //propagate(dp, BB, itv, i);
                for (int k = 1; k <= 5; k++) {
                    int min = 0x00ffffff;
                    if (itv == 0) {
                        dp[i][k] = dp[i-1][k];
                        continue;
                    }
                    for (int j = 1; j <= 5; j++) {
                        if (j == k) continue;
                        int next;
                        if (itv < 0) {
                            next = BB[k][j][-itv];
                        } else if (itv > 0)
                            next = BB[j][k][itv];
                        
                        if (next == -1)
                            continue;
                        min = std::min(dp[i-1][j]+next, min);
                    }
                    dp[i][k] = min;
                }
                //cout << "BB" << endl;
            } else {
                // black -> white
                for (int k = 1; k <= 5; k++) {
                    int min = 0x00ffffff;
                    if (itv == 0) {
                        dp[i][k] = dp[i-1][k];
                        continue;
                    }
                    for (int j = 1; j <= 5; j++) {
                        if (j == k) continue;
                        int next;
                        if (itv < 0) {
                            next = WB[k][j][-itv];
                        } else if (itv > 0)
                            next = BW[j][k][itv];

                        if (next == -1)
                            continue;
                        min = std::min(dp[i-1][j]+next, min);
                    }
                    dp[i][k] = min;
                }
                //cout << "BW" << endl;
            } 
        } else {
            if (blacks.find(p[i]) != blacks.end()) {
                // white -> black
                //propagate(dp, WB, itv, i);
                for (int k = 1; k <= 5; k++) {
                    int min = 0x00ffffff;
                    if (itv == 0) {
                        dp[i][k] = dp[i-1][k];
                        continue;
                    }
                    for (int j = 1; j <= 5; j++) {
                        if (j == k) continue;
                        int next;
                        if (itv < 0) {
                            next = BW[k][j][-itv];
                        } else if (itv > 0)
                            next = WB[j][k][itv];

                        if (next == -1)
                            continue;
                        min = std::min(dp[i-1][j]+next, min);
                    }
                    dp[i][k] = min;
                }
                //cout << "WB" << endl;
            } else {
                // white -> white
                //propagate(dp, WW, itv, i);
                for (int k = 1; k <= 5; k++) {
                    int min = 0x00ffffff;
                    if (itv == 0) {
                        dp[i][k] = dp[i-1][k];
                        continue;
                    }
                    for (int j = 1; j <= 5; j++) {
                        if (j == k) continue;
                        int next;
                        if (itv < 0) {
                            next = WW[k][j][-itv];
                        } else if (itv > 0)
                            next = WW[j][k][itv];
                        
                        if (next == -1)
                            continue;
                        min = std::min(dp[i-1][j]+next, min);
                    }
                    dp[i][k] = min;
                }
                //cout << "WW" << endl;
            }
        }
    }

    /*    
    for (int i = 0; i < L; i++) {
        for (int j = 1; j <= 5; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
    

    printf("%d", *std::min_element(dp[L-1]+1, dp[L-1]+6));

}