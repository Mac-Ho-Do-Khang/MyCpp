// https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'sherlockAndAnagrams' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

/*
    - Extract every substring of the given string
    - Sort all the substrings = > Those anagrams strings will be the same
    - Count the frequency of each sorted substring: n
    - The number of pairs for each substring is C(n, 2) = n(n - 1) / 2
*/

int sherlockAndAnagrams(string s) 
{
    unordered_map<string, int> frequency;
    for (string::iterator i = s.begin(); i != s.end(); ++i)
        for (string::iterator j = i + 1; j != s.end() + 1; ++j)
        {
            string str(i, j);
            sort(str.begin(), str.end());
            if (frequency.find(str) == frequency.end()) frequency[str] = 1;
            else                                        frequency[str]++;
        }

    int result = 0;
    for (auto i : frequency) 
        result += i.second * (i.second - 1) / 2;

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

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
