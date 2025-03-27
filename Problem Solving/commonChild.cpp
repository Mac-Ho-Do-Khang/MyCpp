// https://www.hackerrank.com/challenges/common-child/problem
#include "stdc++.h"
using namespace std;

/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */

int commonChild(string s1, string s2) {
    size_t n = s1.length();
    size_t m = s1.length();
    vector<vector<int>> result(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s1[i - 1] == s2[j - 1]) result[i][j] = result[i - 1][j - 1] + 1;
            else                        result[i][j] = max(result[i][j - 1], result[i - 1][j]);

    /*
    The loops go from 1 because the first row(dp[0][j]) and the first column(dp[i][0]) are initialized to 0. These represent the cases where either string is empty:
    - dp[0][j] : Longest common subsequence when the first string is empty and the second string has j characters.
    - dp[i][0] : Longest common subsequence when the second string is empty and the first string has i characters.

         "" N  O  H  A  R  A  A
    ""   0  0  0  0  0  0  0  0
    S    0  0  0  0  0  0  0  0
    H    0  0  0  1  1  1  1  1
    I    0  0  0  1  1  1  1  1
    N    0  1  1  1  1  1  1  1
    C    0  1  1  1  1  1  1  1
    H    0  1  1  2  2  2  2  2
    A    0  1  1  2  3  3  3  3
    N    0  1  1  2  3  3  3  3

    */

    return result[n][m];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

    return 0;
}
