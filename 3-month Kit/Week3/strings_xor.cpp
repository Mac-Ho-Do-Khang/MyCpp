// https://www.hackerrank.com/challenges/three-month-preparation-kit-strings-xor/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-three
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// The discussion section reveals that the problem always return 'Incorrect' using c++
string strings_xor(string s, string t)
{

    string res = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == t[i]) // `=` -> `==`
            res += '0';   // `=` -> `+=`
        else
            res += '1'; // `=` -> `+=`
    }

    return res;
}

int main()
{
    string s, t;
    cin >> s >> t;
    cout << strings_xor(s, t) << endl;
    return 0;
}
