// https://www.hackerrank.com/challenges/big-sorting/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'bigSorting' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY unsorted as parameter.
 */

// vector<string> bigSorting(vector<string> unsorted) // This is a more elegant way
// {
//     // If a string is sorter, it should always be smaller (as numbers are)
//     sort(unsorted.begin(), unsorted.end(), [](const string &a, const string &b)
//          { return a.size() == b.size() ? a < b : a.size() < b.size(); });
//     return unsorted;
// }

// This is a more verbose way, but via this I learnt more about strick weak ordering (SWO)
vector<string> bigSorting(vector<string> unsorted)
{
    sort(unsorted.begin(), unsorted.end(), [](const string &a, const string &b)
         {
        if(a.size()!=b.size()) return a.size()<b.size();
        else
        {
            size_t n{a.size()};
            for(int i{};i<n;++i)
                if(a[i]!=b[i]) return a[i]<b[i];
                
            return false; // true will result in segmentation fault
            // For any two equal elements a and b, comp(a, b) must return false, and comp(b, a) also false
            // If a == b return true here, when sort use comp(a, b) gets true, later on comp(b, a) also true, 
            // it gets confused and doesn't know which one should be first
        } });
    return unsorted;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> unsorted(n);

    for (int i = 0; i < n; i++)
    {
        string unsorted_item;
        getline(cin, unsorted_item);

        unsorted[i] = unsorted_item;
    }

    vector<string> result = bigSorting(unsorted);

    for (size_t i = 0; i < result.size(); i++)
    {
        fout << result[i];

        if (i != result.size() - 1)
        {
            fout << "\n";
        }
    }

    fout << "\n";

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
