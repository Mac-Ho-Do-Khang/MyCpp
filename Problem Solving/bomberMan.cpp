#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 */

vector<string> bomberMan(int n, vector<string> grid)
{
    if (n == 1) return grid;

    int rows = grid.size();
    int cols = grid[0].size();

    vector<string> full_bomb(rows, string(cols, 'O'));
    if (n % 2 == 0) return full_bomb; // If n is even, the grid is full of bombs

    auto explode = [&](const vector<string>& g) 
    {
        vector<string> result = full_bomb;
        for (int i = 0; i < rows; ++i) 
            for (int j = 0; j < cols; ++j) 
                if (g[i][j] == 'O') 
                {
                    result[i][j] = '.';
                    if (i > 0)        result[i - 1][j] = '.';
                    if (i < rows - 1) result[i + 1][j] = '.';
                    if (j > 0)        result[i][j - 1] = '.';
                    if (j < cols - 1) result[i][j + 1] = '.';
                }
        return result;
    };

    // After the first full bomb cycle, the grid cycles every 4 seconds
    vector<string> grid_after_1st_explode = explode(grid);
    vector<string> grid_after_2nd_explode = explode(grid_after_1st_explode);

    if ((n - 3) % 4 == 0) return grid_after_1st_explode;
    else                  return grid_after_2nd_explode;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int r = stoi(first_multiple_input[0]);

    int c = stoi(first_multiple_input[1]);

    int n = stoi(first_multiple_input[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
