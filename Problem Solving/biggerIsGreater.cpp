// https://www.hackerrank.com/challenges/bigger-is-greater/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'biggerIsGreater' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING w as parameter.
 */

string biggerIsGreater(string w) {
    if (next_permutation(w.begin(), w.end())) return w;
    else                                      return "no answer";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string T_temp;
    getline(cin, T_temp);

    int T = stoi(ltrim(rtrim(T_temp)));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

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
