// https://www.hackerrank.com/challenges/two-pluses/problem

#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'twoPluses' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY grid as parameter.
 */

 // Function to calculate the maximum size of plus centered at (x, y)
int getPlusSize(const vector<string>& grid, int x, int y) 
{
    int size = 1; // set size = 0 will also work but cost one more while loop
    int rows = grid.size();
    int cols = grid[0].size();

    while (x - size >= 0 && x + size < rows && y - size >= 0 && y + size < cols &&
           grid[x - size][y] == 'G' && grid[x + size][y] == 'G' &&
           grid[x][y - size] == 'G' && grid[x][y + size] == 'G') 
        size++;
    
    return size - 1;
}

// Function to check if two pluses overlap
bool overlap(const vector<pair<int, int>>& plus1, const vector<pair<int, int>>& plus2) 
{
    for (const auto& p1 : plus1) 
        for (const auto& p2 : plus2) 
            if (p1 == p2) return true;

    return false;
}

// Function to get the cells occupied by a plus of size `size` at center (x, y)
vector<pair<int, int>> getPlusCells(int x, int y, int size) 
{
    vector<pair<int, int>> cells;
    cells.emplace_back(x, y);
    for (int i = 1; i <= size; i++) 
    {
        cells.emplace_back(x - i, y); // Up
        cells.emplace_back(x + i, y); // Down
        cells.emplace_back(x, y - i); // Left
        cells.emplace_back(x, y + i); // Right
    }
    return cells;
}

int twoPluses(vector<string> grid) 
{
    int rows = grid.size();
    int cols = grid[0].size();
    vector<pair<int, pair<int, int>>> pluses; // each element is pair<area,plus>

    // Find all possible pluses
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) 
            if (grid[i][j] == 'G') 
            {
                int size = getPlusSize(grid, i, j);
                for (int s = 0; s <= size; s++) 
                    pluses.push_back({ 4 * s + 1, {i, j} });
            }

    // Sort by area in descending order
    sort(pluses.rbegin(), pluses.rend());

    int result = 0;

    // Check all pairs of pluses -> BRUTE FORCE
    for (int i = 0; i < pluses.size(); i++) 
        for (int j = i + 1; j < pluses.size(); j++) 
        {
            int area1 = pluses[i].first;
            int area2 = pluses[j].first;

            int x1 = pluses[i].second.first;  
            int y1 = pluses[i].second.second; 
            int x2 = pluses[j].second.first;  
            int y2 = pluses[j].second.second; 

            int size1 = (area1 - 1) / 4;
            int size2 = (area2 - 1) / 4;

            auto plus1Cells = getPlusCells(x1, y1, size1);
            auto plus2Cells = getPlusCells(x2, y2, size2);

            if (!overlap(plus1Cells, plus2Cells)) 
                result = max(result, area1 * area2);
        }

    return result;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

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
