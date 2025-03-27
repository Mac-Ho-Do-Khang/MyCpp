// https://www.hackerrank.com/challenges/making-candies/problem
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'minimumPasses' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER m
 *  2. LONG_INTEGER w
 *  3. LONG_INTEGER p
 *  4. LONG_INTEGER n
 */

// The trickiness lies in making sure the value not to overflow LLONG_MAX
// Via this problem I realize that in HackerRank, LONG_MAX == LLONG_MAX
long minimumPasses(long m, long w, long p, long n) 
{
    long passes{}, candy{}, step{}, run{ LLONG_MAX };

    while (candy < n) {
        step = (m > LLONG_MAX / w) ? 0 : (p - candy) / (m * w); // (m > LLONG_MAX/w) means (m*w > LLONG_MAX) -> overflow

        if (step <= 0) 
        {
            long mw = candy / p;

            if (m >= w + mw)      w += mw;
            else if (w >= m + mw) m += mw;
            else 
            {
                long total = m + w + mw;
                m = total / 2;
                w = total - m;
            }

            candy %= p; // After buying as much as possible, we are left with candy%p candies
            step = 1;
        }

        passes += step;

        if (step * m > LLONG_MAX / w) // (step * m > LLONG_MAX / w) means(step * m * w > LLONG_MAX) ->overflow
            candy = LLONG_MAX;
        else 
        {
            candy += step * m * w;
            run = min(run, long(passes + ceil((n - candy) / (m * w * 1.0))));
        }
    }

    return min(passes, run);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    long m = stol(first_multiple_input[0]);

    long w = stol(first_multiple_input[1]);

    long p = stol(first_multiple_input[2]);

    long n = stol(first_multiple_input[3]);

    long result = minimumPasses(m, w, p, n);

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
