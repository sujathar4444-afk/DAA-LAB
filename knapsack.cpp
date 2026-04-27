#include <iostream>
using namespace std;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int* wt = new int[n];
    int* val = new int[n];

    cout << "Enter weights:\n";
    for(int i = 0; i < n; i++)
        cin >> wt[i];

    cout << "Enter values:\n";
    for(int i = 0; i < n; i++)
        cin >> val[i];

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    // Dynamic 2D array
    int** dp = new int*[n + 1];
    for(int i = 0; i <= n; i++)
        dp[i] = new int[W + 1];

    // Fill DP table
    for(int i = 0; i <= n; i++)
    {
        for(int w = 0; w <= W; w++)
        {
            if(i == 0 || w == 0)
                dp[i][w] = 0;

            else if(wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "Maximum profit: " << dp[n][W] << endl;

    // Free memory
    for(int i = 0; i <= n; i++)
        delete[] dp[i];

    delete[] dp;
    delete[] wt;
    delete[] val;

    return 0;
}