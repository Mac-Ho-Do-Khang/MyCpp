// https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'hackerlandRadioTransmitters' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY x
 *  2. INTEGER k
 */

/*
    - Given the input [7 2 4 6 5 9 12 11] and k=2
    - Mark the locations: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 (base-0 index)
                          F T F T T T T F T F T  T  T  T  
                          Include k extra dummy locations at the end (T values) to handle edge cases for houses near the boundaries.
    - Start at the first location. Skip all empty locations (F).
    - For each house (T), try to place a transmitter at the furthest location within the range k.
    - If no valid position is found within the range, backtrack to the current location and place the transmitter there.
    - After placing a transmitter, skip ahead to the next uncovered house beyond the range.
    ---------------------- Example walk through ----------------------
    - At 0: F -> skip
    - At 1: T, reach 1+k=3 which is T -> place a radar at 3 will cover up to 1+k+k=5
    - At 5+1=6: T, reach 6+2=8: T -> place a radar at 3 will cover up to 10
    - At 10+1=11: T, reach 11+2=13: T (this is originally out of bounds but we create as dummies) -> place a radar at 13 (actually this is placed at either the house 11 or 12) will cover the rest
    => 3 radars total
*/

int hackerlandRadioTransmitters(vector<int> x, int k) 
{
    int n = (*max_element(x.begin(), x.end()));
    vector<bool> locations(n + k, false);
    for (int i : x) locations[i - 1] = true;
    for (int i{}; i < k; ++i) locations[n + i] = true;
    int result{};
    for (int i{}; i < n;)
    {
        if (!locations[i]) ++i;
        else
            for (int j{ k }; j >= 0; --j)
            {
                if (j == 0) { result++; i++; }
                if (locations[i + j])
                {
                    result++;
                    i += j + k + 1;
                    break;
                }
                
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

    int k = stoi(first_multiple_input[1]);

    string x_temp_temp;
    getline(cin, x_temp_temp);

    vector<string> x_temp = split(rtrim(x_temp_temp));

    vector<int> x(n);

    for (int i = 0; i < n; i++) {
        int x_item = stoi(x_temp[i]);

        x[i] = x_item;
    }

    int result = hackerlandRadioTransmitters(x, k);

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
