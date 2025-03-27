// https://www.hackerrank.com/challenges/count-luck/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'countLuck' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING_ARRAY matrix
 *  2. INTEGER k
 */

/*
* Apply BFS but each node not only marked visited or not but also attached with the previous node that comes right before it
* This additional information is used to back track the route to the start position once reaching the end position without using recursion
* Only use wand when in an intersection, meaning the current node:
* - Has 3 or more neighbors if not the start node (the up front and behind neighbors are inevitable as we proceed to reach this node)
* - Has 2 or more neighbors if start node (start node only need one neighbor from which we can travel out)
* Use (!= 'X') instead of (== '.') as (== '.') cannot cover the case of '*'
*/
string countLuck(vector<string> matrix, int k) {
    size_t row{ matrix.size() };
    size_t col{ matrix[0].size() };
    pair<int, int> start_position, end_position;
    bool found_start = false, found_end = false;
    for (int i{}, j{}; i < row; ++i)
    {
        if (!found_start)
        {
            j = matrix[i].find('M');
            if (j != string::npos)
            {
                start_position = { i,j };
                found_start = true;
            }
        }
        if (!found_end)
        {
            j = matrix[i].find('*');
            if (j != string::npos)
            {
                end_position = { i,j };
                found_end = true;
            }
        }
        if (found_start && found_end) break;
    }
    map<pair<int, int>, pair<int, int>> visited; // <current,previous>
    vector<pair<int, int>> directions{ {-1,0},{0,1},{1,0},{0,-1} };
    queue<pair<int, int>> q;
    q.push(start_position);
    visited[start_position] = { -1,-1 }; // The previous node of the 1st one is marked as {-1,-1}
    bool reach_destination = false;
    while (!q.empty())
    {
        auto [current_x, current_y] = q.front();
        q.pop();
        for (auto [dir_x, dir_y] : directions)
        {
            if (current_x + dir_x >= 0
                && current_x + dir_x < row
                && current_y + dir_y >= 0
                && current_y + dir_y < col
                && visited.find({ current_x + dir_x,current_y + dir_y }) == visited.end()
                && matrix[current_x + dir_x][current_y + dir_y] != 'X')
            {
                q.push({ current_x + dir_x,current_y + dir_y });
                visited[{current_x + dir_x, current_y + dir_y}] = { current_x,current_y };
                if (current_x + dir_x == end_position.first
                    && current_y + dir_y == end_position.second)
                {
                    reach_destination = true;
                    break;
                }
            }
        }
        if (reach_destination) break;
    }
    int wands{};
    vector<string> copy(matrix);
    for (auto trace = visited[{end_position.first, end_position.second}]; trace != pair<int, int>{-1, -1}; trace = visited[{trace.first, trace.second}])
    {
        int neighbors{};
        for (auto [dir_x, dir_y] : directions)
        {
            if (trace.first + dir_x >= 0
                && trace.first + dir_x < row
                && trace.second + dir_y >= 0
                && trace.second + dir_y < col
                && matrix[trace.first + dir_x][trace.second + dir_y] != 'X')
                neighbors++;
        }
        if ((trace != start_position && neighbors >= 3)
            || (trace == start_position && neighbors >= 2))
        {
            wands++;
            //copy[trace.first][trace.second] = '1';
        }
        //else copy[trace.first][trace.second] = '0';
    }
    /*for (string i : copy) cout << i << endl;
    cout << endl;*/
    return (wands == k) ? "Impressed" : "Oops!";
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<string> matrix(n);

        for (int i = 0; i < n; i++) {
            string matrix_item;
            getline(cin, matrix_item);

            matrix[i] = matrix_item;
        }

        string k_temp;
        getline(cin, k_temp);

        int k = stoi(ltrim(rtrim(k_temp)));

        string result = countLuck(matrix, k);

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
