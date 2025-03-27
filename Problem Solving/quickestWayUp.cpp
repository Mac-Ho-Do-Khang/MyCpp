// https://www.hackerrank.com/challenges/the-quickest-way-up/problem
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'quickestWayUp' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY ladders
 *  2. 2D_INTEGER_ARRAY snakes
 */

/*
* Given the ladders 12->98 32->62, 42->68
*           snakes  95->13, 97->25, 93->37
* Our initial board would be [0, 1, 2, 3, ..., 101]
* After apply snakes and ladders [0, 1, 2, 3, 11, 98, 13, ..., 31, 62, 33, ..., 91, 92, 37, 94, 13, 95, 96, 25, 98, 99, 100, 101]
* Intial queue: [(1, 0)]  
* After 1st dice roll: [(2, 1), (3, 1), (4, 1), (5, 1), (6, 1), (7, 1)]
* 2nd dice roll start with (2, 1), after which we have: [(3, 1), (4, 1), (5, 1), (6, 1), (7, 1), (8, 2), (9, 2), (10, 2), (11, 2), (98, 2), (13, 2)]
* Go until we reach 100
*/

int quickestWayUp(vector<vector<int>> ladders, vector<vector<int>> snakes) 
{
    vector<int> board(101);  // board[0] is dummy to align with base-1 input
    for (int i = 1; i <= 100; i++) board[i] = i;  

    for (auto& ladder : ladders) board[ladder[0]] = ladder[1];  
    for (auto& snake : snakes) board[snake[0]] = snake[1];  

    vector<bool> visited(101, false);  
    queue<pair<int, int>> q;  // (current position, moves taken)
    q.push({ 1, 0 });  
    visited[1] = true;

    while (!q.empty()) {
        auto [pos, moves] = q.front();
        q.pop();

        if (pos == 100) return moves; 

        for (int dice = 1; dice <= 6; dice++) 
        {
            int next_pos = pos + dice;
            if (next_pos <= 100) next_pos = board[next_pos];  
            if (!visited[next_pos]) 
            {
                visited[next_pos] = true;
                q.push({ next_pos, moves + 1 });
            }
        }
    }
    return -1;  // If we never reach 100
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        vector<vector<int>> ladders(n);

        for (int i = 0; i < n; i++) {
            ladders[i].resize(2);

            string ladders_row_temp_temp;
            getline(cin, ladders_row_temp_temp);

            vector<string> ladders_row_temp = split(rtrim(ladders_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int ladders_row_item = stoi(ladders_row_temp[j]);

                ladders[i][j] = ladders_row_item;
            }
        }

        string m_temp;
        getline(cin, m_temp);

        int m = stoi(ltrim(rtrim(m_temp)));

        vector<vector<int>> snakes(m);

        for (int i = 0; i < m; i++) {
            snakes[i].resize(2);

            string snakes_row_temp_temp;
            getline(cin, snakes_row_temp_temp);

            vector<string> snakes_row_temp = split(rtrim(snakes_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int snakes_row_item = stoi(snakes_row_temp[j]);

                snakes[i][j] = snakes_row_item;
            }
        }

        int result = quickestWayUp(ladders, snakes);

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
