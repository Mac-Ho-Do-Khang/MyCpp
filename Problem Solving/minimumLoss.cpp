// https://www.hackerrank.com/challenges/minimum-loss/problem
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'minimumLoss' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts LONG_INTEGER_ARRAY price as parameter.
 */

// This first version return the correct result but time out due to O(n²)
int minimumLoss1(vector<long> price) 
{
    int n = price.size();
    int result = INT_MAX;
    for (int i{}; i < n - 1; ++i)
        for (int j{ i + 1 }; j < n; ++j)
            if (price[i] > price[j])
                if (price[i] - price[j] < result) result = price[i] - price[j];
    return result;
}

// This version is O[Nlog(N)] due to sort, and only traverse once
int minimumLoss2(vector<long> price) 
{
    int n = price.size();
    vector<pair<long, int>> price_and_time; // <price, day>
    int result = INT_MAX;
    for (int i{ 0 }; i < n; ++i)
        price_and_time.emplace_back(price[i], i);
    sort(price_and_time.begin(), price_and_time.end()); // sort by price
    for (int i{ 1 }; i < n; ++i)
        if (price_and_time[i].second < price_and_time[i - 1].second         // If the higher price comes before the lower (its date is higher than the lower's)
         && price_and_time[i].first - price_and_time[i - 1].first < result) // If the difference is minimal
            result = price_and_time[i].first - price_and_time[i - 1].first;
    
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string price_temp_temp;
    getline(cin, price_temp_temp);

    vector<string> price_temp = split(rtrim(price_temp_temp));

    vector<long> price(n);

    for (int i = 0; i < n; i++) {
        long price_item = stol(price_temp[i]);

        price[i] = price_item;
    }

    int result = minimumLoss(price);

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
