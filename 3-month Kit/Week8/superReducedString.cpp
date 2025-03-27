// https://www.hackerrank.com/challenges/three-month-preparation-kit-reduced-string/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-eight
#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'superReducedString' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string superReducedString(string s)
{
    for (string::const_iterator i{adjacent_find(s.cbegin(), s.cend())}; i != s.cend(); i = adjacent_find(s.cbegin(), s.cend()))
        s.erase(i, i + 2);

    return s == "" ? "Empty String" : s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = superReducedString(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
