// https://www.hackerrank.com/challenges/knightl-on-chessboard/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'knightlOnAChessboard' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts INTEGER n as parameter.
 */

// unordered_map requires its type to be both hashable and comparable. pair<int,int> does have operator==, but not hashable
struct pair_hash 
{
    size_t operator()(const pair<int, int>& p) const 
    {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

vector<vector<int>> knightlOnAChessboard(int n) 
{
    vector<vector<int>> results(n - 1, vector<int>(n - 1, -1));

    for (int i = 1; i < n; i++) 
        for (int j = 1; j < n; j++) 
        {
            queue<pair<int, int>> q; // For BFS
            // Normal BFS only need each node to be marked as visited or not, but we also want the number of move from (0,0)
            // to each node, thus using map to store this information
            unordered_map<pair<int, int>, int, pair_hash> count; 

            vector<pair<int, int>> directions = 
            {
                {-i, -j}, {-i, j}, {i, -j}, {i, j},
                {-j, -i}, {-j, i}, {j, -i}, {j, i}
            }; // both {-i, -j} and {-j, -i} are not neglegible, as shown by Knight(1,2) on the problem page

            count[{0, 0}] = 0;
            q.push({ 0, 0 });

            bool found = false;
            while (!q.empty()) 
            {
                auto current = q.front();
                q.pop();

                for (auto direction : directions) 
                {
                    pair<int, int> next = { current.first + direction.first, current.second + direction.second };

                    if (next.first < 0 || next.second < 0 || next.first >= n || next.second >= n) continue;
                    if (count.find(next) != count.end()) continue; // node visited

                    count[next] = count[current] + 1;
                    if (next == make_pair(n - 1, n - 1)) // if reaching the destination
                    {
                        results[i - 1][j - 1] = count[next];
                        found = true;
                        break;
                    }
                    q.push(next);
                }
                if (found) break;
            }
        }

    return results;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> result = knightlOnAChessboard(n);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }

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
