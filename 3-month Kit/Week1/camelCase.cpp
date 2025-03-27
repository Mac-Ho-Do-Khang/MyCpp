// https://www.hackerrank.com/challenges/three-month-preparation-kit-camel-case/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-one
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    string query{};
    while (getline(cin, query))
    {
        string result{};
        string::iterator it = remove(query.begin(), query.end(), '\r'); // HackerRank input ends with `\r\n` for newline
        if (it != query.end())
            query.erase(it);
        string s{query.substr(4)};
        if (query[0] == 'S')
        {
            for (char c : s)
                if (c >= 'A' && c <= 'Z')
                {
                    result += ' ';
                    result += c + 32;
                }
                else if (c >= 'a' && c <= 'z')
                    result += c;
            if (result[0] == ' ')
                result = result.substr(1);
        }
        else // query[0]=='C'
        {
            bool capitalize{false};
            for (char c : s)
            {
                if (c == ' ')
                    capitalize = true;
                else if (capitalize)
                {
                    result += c - 32;
                    capitalize = false;
                }
                else
                    result += c;
            }
            if (query[2] == 'M') // methods have `()` at the end
                result.append("()");
            else if (query[2] == 'C') // classes have capital name
                result[0] -= 32;
        }
        cout << result << endl;
    }
    return 0;
}
