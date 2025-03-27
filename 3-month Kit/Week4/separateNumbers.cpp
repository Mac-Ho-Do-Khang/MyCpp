// https://www.hackerrank.com/challenges/three-month-preparation-kit-separate-the-numbers/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-four
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'separateNumbers' function below.
 *
 * The function accepts STRING s as parameter.
 */

/*
Given the string s = "123124125"
Consider 1-digit number, start with 1:
- We find "1" in s and "1" != s, increment to 2 and append -> "12"
- We find "12" in s and "12" != s, increment to 3 and append -> "123"
- We find "123" in s and "123" != s, increment to 4 and append -> "1234"
- We cannot find "123" in s -> 1 digit is not possible
Consider 2-digit number, start with 12:
- We find "12" in s and "12" != s, increment to 13 and append -> "1213"
- We cannot find "1213" in s -> 2 digit is not possible
Consider 3-digit number, start with 123:
- We find "123" in s and "123" != s, increment to 124 and append -> "123124"
- We find "123124" in s and "123124" != s, increment to 125 and append -> "123124125"
- We find "123124125" in s and "123124125" == s -> result found
*/

void separateNumbers(string s)
{
    size_t size{s.size()};
    if (size <= 1)
    {
        cout << "NO" << endl;
        return;
    }
    for (int i{1}; i <= size / 2; ++i)
    {
        string start_str(s.begin(), s.begin() + i);
        long long num{stoll(start_str)};
        string current_str{start_str};
        while (s.find(current_str) != string::npos)
        {
            num++;
            current_str.append(to_string(num));
            if (current_str == s)
            {
                cout << "YES " << start_str << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
}

int main()
{
    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string s;
        getline(cin, s);

        separateNumbers(s);
    }

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
