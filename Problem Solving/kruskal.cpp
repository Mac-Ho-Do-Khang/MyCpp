// https://www.hackerrank.com/challenges/kruskalmstrsub/problem
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

 /*
  * For the weighted graph, <name>:
  *
  * 1. The number of nodes is <name>_nodes.
  * 2. The number of edges is <name>_edges.
  * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
  *
  */

struct DSU 
{
    vector<int> parent, rank;

    DSU(int n) 
    {
        // n nodes are expected to be from 1 -> n, thus 0 is dummy
        parent.resize(n + 1);
        rank.resize(n + 1, 0); // The rank is the height of the tree rooted from one node. Initially, every node is a root itself, thus rank = 0
        for (int i = 0; i <= n; ++i) parent[i] = i; // Initially, every node is parent of itself
    }

    int find(int x) 
    {
        if (parent[x] != x)
            /* Path compression / Flatten the tree
             * By calling recursively, any transitive parent-ship will be resolved
             * e.g: 1 is parent of 3, 3 is parent of 5, 5 is parent of 8
             * parent: [ 0 1 2 1 4 3 6 7 5 ] -> [ 0 1 2 1 4 1 6 7 1 ]
             * If we convert to tree:
             *  1
             *   \
             *    3             1
             *     \     ->   / | \   -> thus called flatten the tree
             *      5        3  5  8
             *       \
             *        8
             */
            parent[x] = find(parent[x]); 
        return parent[x];
    }

    bool unite(int x, int y) 
    {
        int rootX = find(x), rootY = find(y); // not only we trace the roots, we also flatten the trees with these calls
        if (rootX == rootY) return false;

        /* If one tree is higher than the other (higher rank), make the lower tree rooted from the root of the higher one
        * The ranks are unchanged.
        *  1    -> rank 3                                   1   -> still rank 3
        *   \                                              / \
        *    3                    2  -> rank 2     =>     2   3  
        *     \                  /                       /     \
        *      5                4                       4       5  
        *       \              /                       /         \
        *        8            6                       6           8
        */
        if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        // Only when 2 trees are of the same height then one's rank needs increasing if the other becomes the subtree of it
        else 
        {
            parent[rootY] = rootX; // or parent[rootX] = rootY, doesn't matter
            rank[rootX]++;
        }
        return true;
    }
};

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) 
{
    vector<vector<int>> edges;
    int number_of_edges = g_from.size();

    for (int i = 0; i < number_of_edges; ++i) 
        edges.push_back({ g_weight[i], g_from[i], g_to[i] });

    sort(edges.begin(), edges.end()); // sort by the weights

    DSU dsu(g_nodes);
    int result = 0, edges_used = 0;

    for (auto& edge : edges) 
    {
        int weight = edge[0], u = edge[1], v = edge[2];

        if (dsu.unite(u, v)) 
            {
            result += weight;
            edges_used++;
            if (edges_used == g_nodes - 1) break;
        }
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    // Write your code here.
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
