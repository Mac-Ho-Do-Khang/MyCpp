// https://www.hackerrank.com/challenges/journey-to-the-moon/problem
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */

/*
* The discussed solution is to use DFS, as follow:
* The first step is to determine the number of countries represente. This can be done using a depth first search. 
* Everyone from a country is part of the same connected component.
* But I approach totally differently
*/

long journeyToMoon(int n, vector<vector<int>> astronaut) // int -> long
{
    unordered_map<int, int> groups, sizes;
    // groups' element: <astronaut's id, group number>
    // sizes' element: <group number, number of members>
    for (int i{}, m{}; i < astronaut.size(); ++i)
    {
        if (groups.find(astronaut[i][0]) != groups.end()
            && groups.find(astronaut[i][1]) == groups.end()) // If a new second astronaut pairs with a known one who comes first
        {
            groups[astronaut[i][1]] = groups[astronaut[i][0]];
            sizes[groups[astronaut[i][0]]]++;
        }
        else if (groups.find(astronaut[i][1]) != groups.end()
            && groups.find(astronaut[i][0]) == groups.end()) // If a new first astronaut pairs with a known one who comes second
        {
            groups[astronaut[i][0]] = groups[astronaut[i][1]];
            sizes[groups[astronaut[i][1]]]++;
        }
        else if (groups.find(astronaut[i][1]) != groups.end()
            && groups.find(astronaut[i][0]) != groups.end()  // If both astronauts are already known and belongs to 2 different groups
            && groups.find(astronaut[i][0]) != groups.find(astronaut[i][1])) 
        {
            int change_to_group = groups[astronaut[i][1]];
            int deleted_group = groups[astronaut[i][0]];
            int increased_size = sizes[groups[astronaut[i][0]]];
            for (auto& [id, group_no] : groups)       // Move all astronauts from the 1st group to the 2nd one
            {
                if (group_no == deleted_group)
                    group_no = change_to_group;
            }
            sizes.erase(deleted_group);               // Remove the size of the 1st group
            sizes[change_to_group] += increased_size; // Update the size of the 2nd group
        }
        else // Both astronauts are new (belong to no group)
        {
            groups[astronaut[i][0]] = m;
            groups[astronaut[i][1]] = m;
            sizes[m] = 2;
            m++;
        }
    }

    /*
    * There are in total n astronauts, belonging to k different groups, each with size >= 1
    * There are C(n,2) = n(n-1)/2 ways to pick a pair of astronauts, including those of a same group
    * Within each group i, there are C(n_i,2) = n_i(n_i-1)/2 ways to pick a pair of astronauts
    * So to pick a pair of different groups, there are C(n-2) - C(n_i-2) ways, where i = 0,1,...,k
    */
    int within{};
    for (auto& [group_number, size] : sizes)
        within += size * (size - 1) / 2;

    return n * (n - 1l) / 2 - within; // int -> long
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int p = stoi(first_multiple_input[1]);

    vector<vector<int>> astronaut(p);

    for (int i = 0; i < p; i++) {
        astronaut[i].resize(2);

        string astronaut_row_temp_temp;
        getline(cin, astronaut_row_temp_temp);

        vector<string> astronaut_row_temp = split(rtrim(astronaut_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int astronaut_row_item = stoi(astronaut_row_temp[j]);

            astronaut[i][j] = astronaut_row_item;
        }
    }

    long result = journeyToMoon(n, astronaut); // int -> long

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
