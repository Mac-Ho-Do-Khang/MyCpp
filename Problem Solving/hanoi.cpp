// https://www.hackerrank.com/challenges/gena/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'hanoi' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY posts as parameter.
 */

/*
    If n = 3 and disks are at rods [2, 1, 3], we encode it as:
    state = (2 - 1) × 4^2 + (1 - 1) × 4^1 + (3 - 1) × 4^0
          = 1 × 16 + 0 × 4 + 2 = 18
*/
int encode(const vector<int>& positions) 
{
    int hash = 0;
    for (int i = 0; i < positions.size(); i++) 
        hash = hash * 4 + (positions[i] - 1);
    return hash;
}

vector<int> decode(int hash, int n) 
{
    vector<int> positions(n);
    for (int i = n - 1; i >= 0; i--) 
    {
        positions[i] = (hash % 4) + 1;
        hash /= 4;
    }
    return positions;
}
 // Use BFS to explore the minimum number of moves required to reach the target state from the initial configuration.
int hanoi(const vector<int>& posts) {
    int n = posts.size();
    int target = encode(vector<int>(n, 1)); // Target: All disks on rod 1

    queue<int> q;
    unordered_map<int, int> visited; // {state_hash, moves}

    int start = encode(posts);
    q.push(start);
    visited[start] = 0;

    while (!q.empty()) 
    {
        int current_hash = q.front();
        q.pop();
        int moves = visited[current_hash];

        if (current_hash == target) return moves;

        vector<int> positions = decode(current_hash, n);

        // Generate valid moves
        for (int from = 1; from <= 4; ++from) 
        {
            int top_disk = -1;
            for (int i = 0; i < n; ++i) 
                if (positions[i] == from) // Find the smallest disk
                {
                    top_disk = i;
                    break;
                }
            if (top_disk == -1) continue; // No disk on this rod

            for (int to = 1; to <= 4; ++to) 
            {
                if (from == to) continue;

                bool can_move = true;
                for (int i = 0; i < top_disk; ++i) 
                    if (positions[i] == to) // We cannot move if there is a smaller disk on `to` rod.
                    {
                        can_move = false;
                        break;
                    }

                if (!can_move) continue;

                // Move disk
                vector<int> new_positions = positions;
                new_positions[top_disk] = to;
                int new_hash = encode(new_positions);

                if (!visited.count(new_hash)) 
                {
                    visited[new_hash] = moves + 1;
                    q.push(new_hash);
                }
            }
        }
    }
    return -1; // Should never reach here
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string loc_temp_temp;
    getline(cin, loc_temp_temp);

    vector<string> loc_temp = split(rtrim(loc_temp_temp));

    vector<int> loc(n);

    for (int i = 0; i < n; i++) {
        int loc_item = stoi(loc_temp[i]);

        loc[i] = loc_item;
    }

    int res = hanoi(loc);

    fout << res << "\n";

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
