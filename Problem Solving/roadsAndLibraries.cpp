// https://www.hackerrank.com/challenges/torque-and-development/problem
#include "stdc++.h"
using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) 
{
    if (c_road >= c_lib) return n * (long)c_lib; // n * c_lib * 1l is incorrect as it's evaluated as (n * c_lib) * 1l
    for_each(cities.begin(), cities.end(), [](vector<int>& city) {city[0]--, city[1]--; }); // Convert cities to base-0 index
    vector<vector<int>> adj(n);
    for (auto& city : cities)
    {
        // int u = city[0] - 1, v = city[1] - 1; // Can also convert to 0-base here instead of above
        int u = city[0], v = city[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int group_number{};
    // City `n` will be the (n-1)th element of `visited`, which holds its group number
    vector<int> visited(n, -1);
    queue<int> q;
    for (int i{}; i < n; ++i)
    {
        if (visited[i] != -1) continue;
        q.push(i);
        visited[i] = group_number;
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            for (int neighbor : adj[current])
            {
                if (visited[neighbor] == -1)
                {
                    q.push(neighbor);
                    visited[neighbor] = group_number;
                }
            }
        }
        group_number++;
    }

    // Calculate size of each group using frequency count
    vector<int> sizes(group_number, 0);
    for (int i : visited) sizes[i]++;

    long result{};
    for (int i{}; i < sizes.size(); ++i)
    {
        // Each group: 1 library + (size-1)*roads
        result += c_lib + (sizes[i] - 1) * (long)c_road; // shouldn't use c_lib + (sizes[i] - 1) * c_road * 1l for the same reason
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(cin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

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
