// https://www.hackerrank.com/challenges/anagram/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'anagram' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

/*
        abcdzyxc
                        a   b   c   d   ...     x   y   z
first_half_frequency    1   1   1   1           0   0   0
second_half_frequency   0   0   1   0           1   1   1
difference              1-> 2-> 2-> 3->         4-> 5-> 6
1 letter changed reduce difference by 2, thus 3 letters need changing here.
*/

int anagram(string s)
{
    size_t n{s.size()};
    if (n % 2 == 1)
        return -1;
    vector<int> first_half_frequency(26), second_half_frequency(26);
    for (int i{}; i < n / 2; ++i)
        if (i < n / 2)
            first_half_frequency[s[i] - 'a']++;
    for (int i = n / 2; i < n; ++i)
        second_half_frequency[s[i] - 'a']++;
    int difference{};
    for (int i{}; i < 26; ++i)
        difference += abs(first_half_frequency[i] - second_half_frequency[i]);

    return difference / 2;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string s;
        getline(cin, s);

        int result = anagram(s);

        fout << result << "\n";
    }

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
