#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to build bad character table
void badCharHeuristic(string pattern, vector<int> &badChar) {
    int m = pattern.size();

    // Initialize all occurrences as -1
    for (int i = 0; i < 256; i++)
        badChar[i] = -1;

    // Fill the actual value of last occurrence
    for (int i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;
}

// Boyer Moore search function
void boyerMooreSearch(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> badChar(256);
    badCharHeuristic(pattern, badChar);

    int shift = 0; // shift of pattern with respect to text

    while (shift <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j while characters match
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        // If pattern is present
        if (j < 0) {
            cout << "Pattern found at index: " << shift << endl;

            // Shift pattern so next character aligns
            shift += (shift + m < n) ? m - badChar[text[shift + m]] : 1;
        } 
        else {
            // Shift pattern using bad character rule
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }
}

int main() {
    string text = "ABAAABCD";
    string pattern = "ABC";

    boyerMooreSearch(text, pattern);

    return 0;
}