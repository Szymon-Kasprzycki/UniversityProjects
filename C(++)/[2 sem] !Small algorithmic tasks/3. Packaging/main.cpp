#include <iostream>

using namespace std;

const int MAX_ITERATIONS = 500;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// REFERENCE https://en.wikipedia.org/wiki/Knapsack_problem
int knapsack(int n, int m, int p[], const int w[]) {
    if (n == 0 || m == 0) return 0;

    int **dp = new int*[n + 1];
    
    for (int i = 0; i <= n; i++) {
        dp[i] = new int[m + 1];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (w[i - 1] <= j) {
                dp[i][j] = maxVal(dp[i - 1][j], p[i - 1] + dp[i - 1][j - w[i - 1]]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    int result = dp[n][m];
    for (int i = 0; i <= n; i++) {
        delete[] dp[i];
    }
    delete[] dp;
    return result;
}

int main() {
    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        // read number of items
        int n;
        cin >> n;

        // read payments of each item
        int *payments = new int[n];
        for (int i = 0; i < n; i++) cin >> payments[i];

        // read weights of each item
        int *weights = new int[n];
        for (int i = 0; i < n; i++) cin >> weights[i];

        // read maximum weight
        int maxWeight;
        cin >> maxWeight;

        // call knapsack function
        int result = knapsack(n, maxWeight, payments, weights);
        cout << result << endl;

        delete[] payments;
        delete[] weights;
    }


    return 0;
}