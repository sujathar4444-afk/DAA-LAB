#include <iostream>
#include <vector>
using namespace std;

int knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<int> dp(W + 1, 0);

    // Loop through all items
    for (int i = 0; i < n; i++) {
        // Traverse weights backwards
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }

    return dp[W];
}

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> wt(n), val(n);

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
    }

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    int result = knapsack(W, wt, val, n);
    cout << "Maximum value = " << result << endl;

    return 0;
}
