// https://www.hackerrank.com/challenges/three-month-preparation-kit-new-year-chaos/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-seven
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumBribes' function below.
 *
 * The function accepts INTEGER_ARRAY q as parameter.
 */

/*
    1 2 3 4 5 6 7 8
    1 2 5 3 4 6 7 8 -> 5 bribes 3 and 4
    1 2 5 3 7 4 6 8 -> 7 bribes 4 and 6
    1 2 5 3 7 8 4 6 -> 8 bribes 4 and 6
    ...
* Observe that no matter what happens after 5 bribes and passes 3 and 4, 5 will always stand before 3 and 4, and only 3 and 4
are elements behind 5 that are smaller than 5.
* Thus, starting from the end of the queue, the number of elements that are smaller than one specific element reveals us the
number of bribes that element has made.
 */

void minimumBribes(vector<int> q)
{
    int bribes{};
    set<int> s;
    for (auto i = q.rbegin(); i != q.rend(); ++i)
    {
        s.insert(*i);
        int idx{};
        for (auto j = s.begin(); j != s.end() && *j != *i; ++j, ++idx)
            ;
        if (idx == 0) // only element in set -> no bribes
            ;
        else if (idx == 1) // 1 element before the element -> 1 bribe
            bribes += 1;
        else if (idx == 2) // 2 elements before the element -> 2 bribes
            bribes += 2;
        else // 3 or more elements before the element -> too chaotic
        {
            cout << "Too chaotic" << endl;
            return;
        }
    }
    cout << bribes << endl;
}

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split(rtrim(q_temp_temp));

        vector<int> q(n);

        for (int i = 0; i < n; i++)
        {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
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

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
