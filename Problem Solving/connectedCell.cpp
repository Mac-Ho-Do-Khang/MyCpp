// https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'connectedCell' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

int connectedCell(vector<vector<int>> matrix) 
{
    int row = matrix.size(), col = matrix[0].size();
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    int result{};
    vector<pair<int, int>> directions{ {-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1} };
    for (int i{}; i < row; i++)
    {
        for (int j{}; j < col; j++)
        {
            if (visited[i][j] || matrix[i][j] == 0) continue;
            queue<pair<int, int>> q;    // vanilla BFS
            visited[i][j] = true;
            q.push({ i,j });
            int area{ 1 };              // already has the 1st cell
            while (!q.empty()) {
                pair<int, int> current = q.front();
                q.pop();

                for (auto direction : directions)
                {
                    if (current.first + direction.first >= 0
                        && current.first + direction.first < row
                        && current.second + direction.second >= 0
                        && current.second + direction.second < col)
                        if (!visited[current.first + direction.first][current.second + direction.second]
                            && matrix[current.first + direction.first][current.second + direction.second] == 1)
                        {
                            visited[current.first + direction.first][current.second + direction.second] = true;
                            area++;
                            q.push({ current.first + direction.first,current.second + direction.second });
                        }
                }
            }
            if (area > result) result = area;
        }
    }
    return result;
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

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < m; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = connectedCell(matrix);

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
