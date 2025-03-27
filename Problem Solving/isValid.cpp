// https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

 // void insert(map<char,int>& mp, set<int>& st, char value)
 // {
 //     if(mp.find(value)!=mp.end()) mp.insert({value,1});
 //     else                         mp[value]++;
 // }

string isValid(string s) 
{
    if (s.length() < 3) return "YES";
    vector<pair<char, int>> frequency;
    for (char c : s)
    {
        auto it = find_if(frequency.begin(), frequency.end(), [c](pair<char, int> p) {return p.first == c; });
        if (it == frequency.end())
            frequency.push_back({ c,1 });
        
        else it->second++;
    }
    sort(frequency.begin(), frequency.end(), [](pair<char, int> a, pair<char, int> b) {return a.second < b.second; });
    
    for (auto i : frequency) cout << i.first << ":" << i.second << "  "; // a:1  b:2  c:2  d:3 ...

    int first_freq = frequency.begin()->second;
    int last_freq = frequency.rbegin()->second;

    if (frequency.size() == 1) // Only one character
        return "YES";
    else if (frequency.size() == 2 && last_freq - first_freq < 2) // a:2  b:2  -OR-  a:4  b:5
        return "YES";
    else if (last_freq == first_freq) // a:2  b:2 ... y:2  z:2
        return "YES";
    else if (
        first_freq == 1 && 
        distance(frequency.begin(),
            find_if(frequency.begin(), frequency.end(), [first_freq](pair<char, int>p) 
                {return p.second != first_freq; })) == 1
            ) // a:1  b:100  c:100  ...  z:100  -OR- a:1  b:100  c:100  ...  z:101
    {
        set<int> count_frequencies;
        for (auto i : frequency) count_frequencies.insert(i.second);
        if (count_frequencies.size() > 2) // [1,100,101] => Remove the 'a' which appears only once cannot make the string valid
            return "NO";
        else                              // [1,100] => Remove the 'a' which appears only once can make the string valid
            return "YES";
    }
    else if (
        distance(find_if(frequency.begin(), frequency.end(), [first_freq](pair<char, int>p) 
        {return p.second != first_freq; }), frequency.end()) == 1 && last_freq - first_freq == 1
            ) // a:5  b:5  c:5  ...  y:5  z:6
        return "YES";
    else 
        return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
