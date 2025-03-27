// https://www.hackerrank.com/challenges/three-month-preparation-kit-pylons/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-seven
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'pylons' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY arr
 */

int pylons(int k, vector<int> arr)
{
    int result{};
    for (int n{}; n < arr.size();)
    {
        vector<int> places;                    // Store all locations of `1` within each k range
        for (int i{n - k + 1}; i < n + k; ++i) // Here not only do we need to check forward, but backward as well
                                               /*
                                                   ... 1 0 0 1 0 0 0 0 (end)  k=5
                                                       ^     ^   ^ ^ ^
                                                       a     d   b c e
                                                   After we place a pylon at a (which covers up to b), we jump to the farthest next location, which is c
                                                   If we only check from c and beyond, we return -1 because c and e cannot be covered. But we miss d, which can cover those 2.
                                                   The reason is that d is within the range of pylon a, but skipped as we only check from the maximum range of pylon a and beyond.
                                                   Therefore, from the furthest range of the most recent pylon, we need to check both forward and backward.
                                               */
            if (arr[i] == 1)                   // Somehow HackerRank doesn't error `vector subscript out of range` when i < 0, but VS does???
                places.push_back(i);
        if (!places.empty()) // There is at least one `1` within the range
        {
            result++;                                           // Place the pylon
            n = *max_element(places.begin(), places.end()) + k; // Jump to the farthest next location
        }
        else
            return -1;
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = pylons(k, arr);

    fout << result << "\n";

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
