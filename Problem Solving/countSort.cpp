// https://www.hackerrank.com/challenges/countingsort4/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countSort' function below.
 *
 * The function accepts 2D_STRING_ARRAY arr as parameter.
 */

void countSort(vector<vector<string>> arr)
{
    // Precompute the integer values of arr[i][0] to save time, then cache these integers into a new array
    // Thus, instead of calling stoi() repeatedly during stable_sort, only call it once for each element here
    vector<pair<int, string>> int_arr(arr.size());
    for (size_t i = 0; i < arr.size(); ++i)
        int_arr[i] = {stoi(arr[i][0]), i < arr.size() / 2 ? "-" : arr[i][1]};

    // Use comparator here, otherwise it sorts based on pair.first and within a same pair.first sorts based on pair.second => not stable
    stable_sort(int_arr.begin(), int_arr.end(), [](pair<int, string> a, pair<int, string> b)
                { return a.first < b.first; });

    // Outputting each element individually with cout is relatively slow. Thus, construct a single string and output it once
    string result;
    for (const pair<int, string> &i : int_arr)
        result += i.second + " ";
    cout << result;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<string>> arr(n);

    for (int i = 0; i < n; i++)
    {
        arr[i].resize(2);

        string arr_row_temp_temp;
        getline(cin, arr_row_temp_temp);

        vector<string> arr_row_temp = split(rtrim(arr_row_temp_temp));

        for (int j = 0; j < 2; j++)
        {
            string arr_row_item = arr_row_temp[j];

            arr[i][j] = arr_row_item;
        }
    }

    countSort(arr);

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
