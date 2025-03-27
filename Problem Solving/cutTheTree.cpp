// https://www.hackerrank.com/challenges/cut-the-tree/problem?isFullScreen=true
#include "stdc++.h"
using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

// Use DFS with recursion

int total;
vector<int> sub_total;
vector<vector<int>> adjency;

void dfs(int node, int parent, const vector<int>& data) 
{
    sub_total[node] = data[node];
    for (int neighbor : adjency[node])
        if (neighbor != parent) 
        {
            dfs(neighbor, node, data);
            sub_total[node] += sub_total[neighbor];
        }
}

int cutTheTree(vector<int> data, vector<vector<int>> edges) 
{
    int n = data.size();
    adjency.assign(n, vector<int>());
    sub_total.assign(n, 0);

    // Build adjacency list (zero-based index)
    for (const auto& edge : edges) 
    {
        int u = edge[0] - 1, v = edge[1] - 1;  // Convert to zero-based
        adjency[u].push_back(v);
        adjency[v].push_back(u);
    }

    total = accumulate(data.begin(), data.end(), 0);

    // Compute subtree sums
    dfs(0, -1, data);

    // Find the minimum difference when cutting an edge
    int result = INT_MAX;
    for (int i = 1; i < n; ++i) // Root node is not considered for cut
    { 
        int sum1 = sub_total[i];
        int sum2 = total - sum1;
        result = min(result, abs(sum1 - sum2));
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string data_temp_temp;
    getline(cin, data_temp_temp);

    vector<string> data_temp = split(rtrim(data_temp_temp));

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        int data_item = stoi(data_temp[i]);

        data[i] = data_item;
    }

    vector<vector<int>> edges(n - 1);

    for (int i = 0; i < n - 1; i++) {
        edges[i].resize(2);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    int result = cutTheTree(data, edges);

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
