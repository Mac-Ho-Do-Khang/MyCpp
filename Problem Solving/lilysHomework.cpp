// https://www.hackerrank.com/challenges/lilys-homework/problem

#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'lilysHomework' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int lilysHomework(vector<int> arr) 
{
    /*
    The goal is to make arr sorted in either order, whichever requires less swaps is chosen
    To calculate number of swaps to make an array sorted in a particular order, we follow cycle decomposition method
    Given the array 1,3,5,7,2,4,6,8
    First, mark each element with its own index: (1, 0) (3, 1) (5, 2) (7, 3) (2, 4) (4, 5) (6, 6) (8, 7)
    Then, we sort based on the values:           (1, 0) (2, 4) (3, 1) (4, 5) (5, 2) (6, 6) (7, 3) (8, 7)
    Create another array to mark each visit:    [   F      F      F      F      F      F      F      F  ]
    For each cycle, visit the first unvisited element, then jumps to the element with the index of the current one;
        continue until we reach the 1st element again => one cycle. 
    For each cycle, we increase number of swaps = its size - 1. This is because in order to make n elements go to
        their correct positions, we need n - 1 swaps
    Do until all elements are visited
            Cycle 1: (1, 0) -> (1, 0)  size = 1 => 0 swap
            Cycle 2: (2, 4) -> (5, 2) -> (3, 1) -> (2, 4)   size = 3 => 2 swaps
            Cycle 3: (4, 5) -> (6, 6) -> (7, 3) -> (4, 5)   size = 3 => 2 swaps
            Cycle 4: (8, 7) -> (8, 7)  size = 1 => 0 swap
        Therefore, in order to ascendingly sort 1,3,5,7,2,4,6,8 we need 4 swaps
    */

    // Calculating swaps to reach ascending sorted
    vector<pair<pair<int, int>, bool>> asc_arr;
    int asc_swaps = 0;
    for (int i = 0; i < arr.size(); ++i)
        asc_arr.push_back({ {arr[i],i},false });
    sort(asc_arr.begin(), asc_arr.end());
    for (auto i : asc_arr)
    {
        if (i.second) continue;
        int index = i.first.second;
        int size = 0;
        while (asc_arr[index].second == false)
        {
            size++;
            asc_arr[index].second = true;
            index = asc_arr[index].first.second;
        }
        asc_swaps += size - 1;
    }
    // Calculating swaps to reach descending sorted
    vector<pair<pair<int, int>, bool>> dsc_arr;
    int dsc_swaps = 0;
    for (int i = 0; i < arr.size(); ++i)
        dsc_arr.push_back({ {arr[i],i},false });
    sort(dsc_arr.begin(), dsc_arr.end(), [](pair<pair<int, int>, bool> a, pair<pair<int, int>, bool> b) 
        {return a.first.first > b.first.first; });
    for (auto i : dsc_arr)
    {
        if (i.second) continue;
        int index = i.first.second;
        int size = 0;
        while (dsc_arr[index].second == false)
        {
            size++;
            dsc_arr[index].second = true;
            index = dsc_arr[index].first.second;
        }
        dsc_swaps += size - 1;
    }
    return (asc_swaps > dsc_swaps) ? dsc_swaps : asc_swaps;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

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

    int result = lilysHomework(arr);

    fout << result << "\n";

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
