// https://www.hackerrank.com/challenges/sherlock-and-pairs/problem?isFullScreen=true
// Only 3/17 test cases passed, even with consulting from Discussion section
// The problem seems to lie in data type `int`
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

long long solve(vector<int> a)  // int -> long long
{
    vector<int> frequency(*max_element(a.begin(), a.end()) + 1, 0);
    for (int i : a) frequency[i]++;
    long long result{};         // int -> long long
    for (int i : frequency)
        result += i * (i - 1) * 1ll; // C(2,n) = n(n-1)/2 -> P(2,n) = n(n-1)
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string a_count_temp;
        getline(cin, a_count_temp);

        int a_count = stoi(ltrim(rtrim(a_count_temp)));

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split(rtrim(a_temp_temp));

        vector<int> a(a_count);

        for (int i = 0; i < a_count; i++) {
            int a_item = stoi(a_temp[i]);

            a[i] = a_item;
        }

        long long result = solve(a);    // int -> long long

        fout << result << "\n";
    }

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

vector<string> split(const string& str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
