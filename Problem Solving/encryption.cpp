// https://www.hackerrank.com/challenges/encryption/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

/*
 * Complete the 'encryption' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string encryption(string s) {
    int col = ceil(sqrt(s.length()));
    string result;
    for (int i = 0; i < col; ++i)
    {
        for (string::iterator it = s.begin() + i; it < s.end(); it += col)
            result += *it;
        result += ' ';
    }
    result.pop_back();
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = encryption(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
