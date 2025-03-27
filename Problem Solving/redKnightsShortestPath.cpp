// https://www.hackerrank.com/challenges/red-knights-shortest-path/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'printShortestPath' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER i_start
 *  3. INTEGER j_start
 *  4. INTEGER i_end
 *  5. INTEGER j_end
 */

 /*
 * Apply BFS but each node not only marked visited or not but also attached with the previous node that comes right before it
 * This additional information is used to back track the route to the start position once reaching the end position without using recursion
 */
void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end) 
{
    map<pair<int, int>, pair<int, int>> visited; // <current,previous>
    vector<pair<int, int>> directions
    {
        {-2,-1}, // UL
        {-2,1},  // UR
        {0,2},   // R
        {2,1},   // LR
        {2,-1},  // LL
        {0,-2}   // L
    };
    queue<pair<int, int>> q;
    q.push({ i_start,j_start });
    visited[{i_start, j_start}] = { -1,-1 }; // mark the previous position of the 1st one as {-1,-1}
    while (!q.empty())
    {
        auto current = q.front();
        q.pop();
        if (current == pair<int, int>{i_end, j_end})
        {
            vector<string> paths;
            int counts{};
            for (auto previous = visited[current]; previous != pair<int, int>{-1, -1}; previous = visited[current])
            {
                counts++;
                if (current.first - previous.first == -2 && current.second - previous.second == -1) paths.push_back("UL");
                else if (current.first - previous.first == -2 && current.second - previous.second == 1) paths.push_back("UR");
                else if (current.first - previous.first == 0 && current.second - previous.second == 2) paths.push_back("R");
                else if (current.first - previous.first == 2 && current.second - previous.second == 1) paths.push_back("LR");
                else if (current.first - previous.first == 2 && current.second - previous.second == -1) paths.push_back("LL");
                else if (current.first - previous.first == 0 && current.second - previous.second == -2) paths.push_back("L");
                current = previous;
            }
            cout << counts << endl;
            for (auto i = paths.rbegin(); i != paths.rend(); ++i) cout << *i << " ";
            return;
        }
        for (auto direction : directions)
        {
            if (current.first + direction.first >= 0
                && current.first + direction.first < n
                && current.second + direction.second >= 0
                && current.second + direction.second < n
                && visited.find({ current.first + direction.first,current.second + direction.second }) == visited.end())
            {
                q.push({ current.first + direction.first,current.second + direction.second });
                visited[{current.first + direction.first, current.second + direction.second}] = current;
            }
        }
    }
    cout << "Impossible";
    return;
}


int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int i_start = stoi(first_multiple_input[0]);

    int j_start = stoi(first_multiple_input[1]);

    int i_end = stoi(first_multiple_input[2]);

    int j_end = stoi(first_multiple_input[3]);

    printShortestPath(n, i_start, j_start, i_end, j_end);

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
