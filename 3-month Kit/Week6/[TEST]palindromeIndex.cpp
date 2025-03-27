// https://www.hackerrank.com/challenges/palindrome-index/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'palindromeIndex' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

bool is_palindrome(string s1)
{
    string s2{s1};
    reverse(s1.begin(), s1.end());
    return s1 == s2;
}

int palindromeIndex(string s)
{
    string::iterator i{s.begin()}, j{s.end() - 1};
    for (; i < j; ++i, --j)
        if (*i != *j)
            break;

    if (i >= j) // `s` is already palindrome
        return -1;

    if (is_palindrome(string{s.begin(), i}.append(string{next(i), s.end()}))) // if removing `i` makes `s` palindrome
        return distance(s.begin(), i);
    if (is_palindrome(string{s.begin(), j}.append(string{next(j), s.end()}))) // if removing `j` makes `s` palindrome
        return distance(s.begin(), j);

    return -1;
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

        int result = palindromeIndex(s);

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
