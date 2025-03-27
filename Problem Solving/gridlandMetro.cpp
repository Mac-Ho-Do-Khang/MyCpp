// https://www.hackerrank.com/challenges/gridland-metro/copy-from/417824905

// Both methods only reach 6/33 testcase correct. Once it comes to test case with huge input, both mess up
// Solutions from 'Discussion' only reach the same result

#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'gridlandMetro' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. INTEGER k
 *  4. 2D_INTEGER_ARRAY track
 */

/*
* This first method simply create a 1D array that maps 1-to-1 to each cell on the grid
* Traverse each track and mark its corresponding emptiness
* Note that each row may appear more than once with overlapping track
* If the given grid is too large, allocating the 1D vector as well as traversing the original grid is impossible
*/
int gridlandMetro1(int n, int m, int k, vector<vector<int>> track) 
{
    vector<bool> empty(n * m, true);
    for (auto i : track)
        for (int j{ i[1] - 1 }; j <= i[2] - 1; ++j)
            empty[(i[0] - 1) * n + j] = false;
    int result = 0;
    for_each(empty.begin(), empty.end(), [&result](bool i) {if (i) ++result; });
    return result;
}

/*
* This second method only goes through 'track', collecting information about each track and calculate the result
* Example: Row 19 appears 4 times with track 7->10, 1->5, 9->12, 2->4
* rows[19] = {{7,10}, {1,5}, {9,12}, {2,4}} --sort--> {{1,5}, {2,4}, {7,10}, {11,12}}
* start=1, end=5, occupied=0
* As 2<=5+1, we can merge {1,5}, {2,4} into {1,5}: start=1, end=max(4,5)=5
* ocuppied+=5-1+1=5, start++=6
* As 11<=10+1, we can merge {7,10}, {11,12} into {7,12}: start=7, end=max(10,12)=12
* ocuppied+=12-7+1=11
* Places to place lamports = total cells - occupied
*/
int gridlandMetro2(int n, int m, int k, vector<vector<int>> track) 
{
    unordered_map<int, vector<pair<int, int>>> rows;
    int occupied{};
    for (auto t : track) rows[t[0]].push_back({ t[1],t[2] });
    for (auto i : rows)
    {
        sort(i.second.begin(), i.second.end());
        int start = i.second[0].first, end = i.second[0].second;
        for (int j{ 1 }; j < i.second.size(); ++j)
        {
            if (i.second[j].first <= end + 1) end = i.second[j].second; // Merging segments
            else
            {
                occupied += end - start + 1; 
                start = i.second[j].first; // Moving to new segments
                end = i.second[j].second;
            };
        }
        occupied += end - start + 1; // This is for the last segments
    }
    long long total = (long long)n * m;
    return total - occupied;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int k = stoi(first_multiple_input[2]);

    vector<vector<int>> track(k);

    for (int i = 0; i < k; i++) {
        track[i].resize(3);

        string track_row_temp_temp;
        getline(cin, track_row_temp_temp);

        vector<string> track_row_temp = split(rtrim(track_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int track_row_item = stoi(track_row_temp[j]);

            track[i][j] = track_row_item;
        }
    }

    int result = gridlandMetro(n, m, k, track);

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
