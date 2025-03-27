// https://www.hackerrank.com/challenges/three-month-preparation-kit-sansa-and-xor/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-five
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'sansaXor' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

// int sansaXor(vector<int> arr) -> TLE due to O(n^3)
// {
//     size_t n{arr.size()};
//     vector<int> xors;
//     for (int i{}; i < n; ++i)
//     {
//         for (int j{i}; j < n; ++j)
//         {
//             int temp{arr[i]};
//             for (int k = i + 1; k <= j; ++k)
//             {
//                 temp ^= arr[k];
//             }
//             xors.push_back(temp);
//         }
//     }
//     int result{xors[0]};
//     for (int i{1}; i < xors.size(); ++i)
//         result ^= xors[i];
//     return result;
// }
/*
Given array `arr` of n elements. Consider element arr[i]:
- The number of ways to start a subarray at or before index i is i + 1 (since it can start at index 0, 1, 2, ..., i).
- The number of ways to end a subarray at or after index i is n - i (since it can end at index i, i+1, i+2, ..., n-1).
-> There are (i+1)(n-i) subarrays containing arr[i]. In other words, arr[i] appears (i+1)(n-i) time
If arr[i] appears an even number of times, it cancels out (since x ⊕ x = 0).
If n is even, (i+1)(n-i) is even for i=0->n-1, every single element always cancels itself out => result=0
If n is odd, (i+1)(n-i) is odd only when i is even, we only consider i=0,2,4,...,n-1
*/
int sansaXor(vector<int> arr)
{
    int result{};
    size_t n{arr.size()};

    if (n % 2 == 0)
        return 0;

    for (size_t i = 0; i < n; i += 2)
        result ^= arr[i];

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++)
        {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        int result = sansaXor(arr);

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
