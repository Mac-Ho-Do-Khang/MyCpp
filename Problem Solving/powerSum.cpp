// https://www.hackerrank.com/challenges/the-power-sum/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'powerSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER X
 *  2. INTEGER N
 */

int countWays(int X, int N, int num) 
{
    int power = pow(num, N);
    if (power > X) return 0;       // If num^N > X, stop recursion
    if (power == X) return 1;      // We've found a valid way

    // Try two possibilities:
    return countWays(X - power, N, num + 1) // Include num^N and continue searching with next number
        +  countWays(X, N, num + 1);        // Skip num^N and continue searching with next number
}

int powerSum(int X, int N) 
{
    return countWays(X, N, 1);
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string X_temp;
    getline(cin, X_temp);

    int X = stoi(ltrim(rtrim(X_temp)));

    string N_temp;
    getline(cin, N_temp);

    int N = stoi(ltrim(rtrim(N_temp)));

    int result = powerSum(X, N);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
