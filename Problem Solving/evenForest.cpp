// https://www.hackerrank.com/challenges/even-tree/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

// Set these as global variables to be able to be used by `dfs`
vector<vector<int>> adjacency_list;
vector<vector<int>> branch_structures;
vector<int> subtree_sizes;

/*
* There's alwayes n node from 1 -> n, which is converted into 0 -> n-1 and passed into `dfs`
* If original node 7 have three branches with 1,3,4 children within these branches respectively, branch_structures[2] = {1,3,4}
* We traverse each node of `branch_structures`, whose branches are then traversed
* If a branch has even number of children, we can always cut that edge, making a new subtree and the parent one with both even nodes
*/

int dfs(int node, int parent)
{
    subtree_sizes[node] = 1;
    vector<int> branch_sizes;
    for (int neighbor : adjacency_list[node])
    {
        if (neighbor == parent) continue;
        int child_size = dfs(neighbor, node);
        branch_sizes.push_back(child_size);
        subtree_sizes[node] += child_size;
    }
    branch_structures[node] = branch_sizes;
    return subtree_sizes[node];
}

int evenForest(int t_nodes, int t_edges, vector<int> t_from, vector<int> t_to)
{
    adjacency_list.resize(t_nodes);
    branch_structures.resize(t_nodes);
    subtree_sizes.resize(t_nodes);
    for (int i{}; i < t_edges; ++i)
    {
        int u = t_from[i] - 1, v = t_to[i] - 1; // Convert to 0-base
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    dfs(0, -1); // Root is now 0 instead of 1

    int result{};
    for (auto i : branch_structures)
        for (int j : i) if (j % 2 == 0) result++; // Branch with even children => cut this edge
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_nodes_edges_temp;
    getline(cin, t_nodes_edges_temp);

    vector<string> t_nodes_edges = split(rtrim(t_nodes_edges_temp));

    int t_nodes = stoi(t_nodes_edges[0]);
    int t_edges = stoi(t_nodes_edges[1]);

    vector<int> t_from(t_edges);
    vector<int> t_to(t_edges);

    for (int i = 0; i < t_edges; i++) {
        string t_from_to_temp;
        getline(cin, t_from_to_temp);

        vector<string> t_from_to = split(rtrim(t_from_to_temp));

        int t_from_temp = stoi(t_from_to[0]);
        int t_to_temp = stoi(t_from_to[1]);

        t_from[i] = t_from_temp;
        t_to[i] = t_to_temp;
    }

    int res = evenForest(t_nodes, t_edges, t_from, t_to);

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
