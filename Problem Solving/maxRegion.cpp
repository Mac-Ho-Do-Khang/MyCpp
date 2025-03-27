// https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'maxRegion' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY grid as parameter.
 */

int maxRegion(vector<vector<int>> grid)
{
    size_t row{grid.size()}, col{grid[0].size()};
    int max_area{};
    vector<pair<int, int>> visited;

    auto is_valid = [row, col](pair<int, int> pos) -> bool
    {
        return pos.first >= 0 && pos.second >= 0 && pos.first < row && pos.second < col;
    };
    vector<pair<int, int>> directions{{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    for (int i{}; i < row; ++i)
        for (int j{}; j < col; ++j)
        {
            if (grid[i][j] == 1)
            {
                int area{1};
                stack<pair<int, int>> s;
                s.push({i, j});
                visited.push_back({i, j});
                while (!s.empty())
                {
                    pair<int, int> current = s.top();
                    s.pop();
                    for (auto d : directions)
                    {
                        pair<int, int> next{current.first + d.first, current.second + d.second};
                        if (is_valid(next) && find(visited.begin(), visited.end(), next) == visited.end() && grid[current.first + d.first][current.second + d.second] == 1)
                        {
                            visited.push_back(next);
                            s.push(next);
                            area++;
                        }
                    }
                }
                if (area > max_area)
                    max_area = area;
            }
        }

    return max_area;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    vector<vector<int>> grid(n);

    for (int i = 0; i < n; i++)
    {
        grid[i].resize(m);

        string grid_row_temp_temp;
        getline(cin, grid_row_temp_temp);

        vector<string> grid_row_temp = split(rtrim(grid_row_temp_temp));

        for (int j = 0; j < m; j++)
        {
            int grid_row_item = stoi(grid_row_temp[j]);

            grid[i][j] = grid_row_item;
        }
    }

    int res = maxRegion(grid);

    fout << res << "\n";

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
