// https://www.hackerrank.com/challenges/primsmstsub/problem
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'prims' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER start
 */

int prims(int n, vector<vector<int>> edges, int start) 
{
    vector<vector<pair<int, int>>> graph(n + 1);
    for (auto& edge : edges) 
    {
        int u = edge[0], v = edge[1], w = edge[2];
        graph[u].push_back({ v, w }); // (node, weight)
        graph[v].push_back({ u, w }); // (node, weight)
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Max heap

    vector<bool> visited(n + 1, false);
    visited[start] = true;

    for (auto& edge : graph[start]) 
        pq.push({ edge.second, edge.first });

    int result{};

    while (!pq.empty()) 
    {
        pair<int, int> p = pq.top();
        pq.pop();
        int u = p.second;
        int weight = p.first;

        /*
        * In BFS, we only add a new node once and mark it visited right away, so we don't do anything here
        * In Prim, an unvisited node can be added multiple times corresponding to multiple edges, and after we pick the lightest
        * edge, we mark the node visited here
        */
        if (visited[u]) continue;
        visited[u] = true;

        result += weight;

        for (auto& edge : graph[u]) 
            if (!visited[edge.first])
            {
                pq.push({ edge.second, edge.first });
                /*
                * BFS works with unweighted graph, whereas Prim/Kruskal works with weighted one
                * Multiple edges can lead to a same node
                * In BFS, once we reach a node from any node, we'll mark it visited right away right here
                * But in Prim, we need to consider every edges pointing towards one node, as we want the minimum weighted one, 
                so reaching a node from only one node is not enough, thus we won't mark that node as visited here
                */
            }
                
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

    vector<vector<int>> edges(m);

    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    string start_temp;
    getline(cin, start_temp);

    int start = stoi(ltrim(rtrim(start_temp)));

    int result = prims(n, edges, start);

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
