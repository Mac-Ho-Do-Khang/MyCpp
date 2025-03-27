// https://www.hackerrank.com/challenges/organizing-containers-of-balls/problem
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'organizingContainers' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts 2D_INTEGER_ARRAY container as parameter.
 */

string organizingContainers(vector<vector<int>>& container) {

   /* 
   The balls in the containers are not moved around, but just swapped.
   => the number of balls in each container will always remain the same.
   Each container must only have balls with the same number
   => the numbers of balls of each type must match the number of balls in containers.
   (e.g. if there are 3 containers containing 3, 6, 9 balls, then there must be 3 balls of one type, 6 balls of another type and 9 balls of the other type.)
   When working out the numbers of balls in each container and the numbers of balls of each type,
   these two numbers must match to be "Possible".
   */

    int n = container.size();
    vector<long long> capacity_sum(n, 0), type_sum(n, 0);

    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
        {
            capacity_sum[i] += container[i][j];
            type_sum[j] += container[i][j];
        }

    sort(capacity_sum.begin(), capacity_sum.end());
    sort(type_sum.begin(), type_sum.end());

    return (capacity_sum == type_sum) ? "Possible" : "Impossible";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        vector<vector<int>> container(n);

        for (int i = 0; i < n; i++) {
            container[i].resize(n);

            string container_row_temp_temp;
            getline(cin, container_row_temp_temp);

            vector<string> container_row_temp = split(rtrim(container_row_temp_temp));

            for (int j = 0; j < n; j++) {
                int container_row_item = stoi(container_row_temp[j]);

                container[i][j] = container_row_item;
            }
        }

        string result = organizingContainers(container);

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
