// https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem?isFullScreen=true

#include "stdc++.h"
using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'activityNotifications' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY expenditure
 *  2. INTEGER d
 */

int activityNotifications(vector<int> expenditure, int d) 
{
    auto it = expenditure.begin() + d;
    auto oldest = expenditure.begin();
    multiset<int> data(expenditure.begin(), it);
    auto med_it = next(data.begin(), (d - 1) / 2);
    int result = 0;

    for (; it != expenditure.end(); ++it, ++oldest) 
    {
        double median;
        if (d % 2 == 0) median = (*med_it + *next(med_it)) / 2.0;
        else            median = *med_it;
        
        if (*it >= 2 * median) result++;

        // Update the multiset
        data.insert(*it);
        if (*it < *med_it) --med_it;      // If the new element < median, move the median backward
        if (*oldest <= *med_it) ++med_it; // If the deleted element <= median, move the median forward
        data.erase(data.find(*oldest));
        // data.erase(*oldest) : This won't work as it may remove more than one elements with the same value
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

    int d = stoi(first_multiple_input[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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
