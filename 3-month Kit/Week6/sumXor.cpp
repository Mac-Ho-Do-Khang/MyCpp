// https://www.hackerrank.com/challenges/three-month-preparation-kit-sum-vs-xor/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-six
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'sumXor' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER n as parameter.
 */

// long sumXor(long n) // O(n) -> TLE
// {
//     if (n == 0)
//         return 1;
//     int result{};
//     for (int i{}; i < n; ++i)
//         if (n + i == (n ^ i))
//             result++;
//     return result;
// }

/*
 * The condition n + i == (n ^ i) holds when there is no carry in the addition of n and i, meaning no overlapping of bit 1s ever.
 * i can only have bit 1s in places where n has bit 0s.
 * n has k bit 0s -> i has 2^k possibilities to place bit 1s.
 */

long sumXor(long n)
{
    if (n == 0)
        return 1; // Special case

    int zeros = 0;
    while (n)
    {
        if ((n & 1) == 0)
            zeros++;
        n >>= 1;
        /* Another way
        if ((n %2) == 0) zeros++;
        n /= 2;
        */
    }
    return pow(2, zeros); // 2^zeroBits
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    long n = stol(ltrim(rtrim(n_temp)));

    long result = sumXor(n);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}
