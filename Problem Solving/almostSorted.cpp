// https://www.hackerrank.com/challenges/almost-sorted/problem

#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'almostSorted' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void almostSorted(vector<int>& a) 
{
    int n = a.size();
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());

    // Find mismatched indices
    vector<int> mismatch;
    for (int i = 0; i < n; i++) 
        if (a[i] != sorted_a[i]) 
            mismatch.push_back(i);

    // 0 mismatch -> Already sorted
    if (mismatch.empty()) 
    {
        cout << "yes" << endl;
        return;
    }

    // 2 mismatched indices -> Swap
    if (mismatch.size() == 2) 
    {
        cout << "yes\nswap " << mismatch[0] + 1 << " " << mismatch[1] + 1;
        return;
    }

    // > 2 mismatched indices, check if reversing works
    int left = mismatch.front();
    int right = mismatch.back();
    reverse(a.begin() + left, a.begin() + right + 1);
    if (a == sorted_a) cout << "yes\nreverse " << left + 1 << " " << right + 1 << endl;
    else               cout << "no" << endl;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

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
