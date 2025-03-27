// https://www.hackerrank.com/challenges/three-month-preparation-kit-sherlock-and-valid-string/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-seven
#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

// Another method in `Problem Solving` folder

string isValid(string s)
{
    vector<int> frequency(26);
    for (char c : s)
        frequency[c - 'a']++;

    unordered_map<int, int> frequency_count; // count the frequency of each frequency (excluding 0 frequency)
    for (int i : frequency)
        if (i != 0)
            frequency_count[i]++;

    if (frequency_count.size() <= 1) // if all characters have the same frequency
        return "YES";
    else if (frequency_count.size() == 2) // if there are only two different frequencies
    {
        vector<pair<int, int>> frequency_and_count; // size of 2
        for (auto f : frequency_count)
            frequency_and_count.push_back(f);
        sort(frequency_and_count.begin(), frequency_and_count.end()); // the smaller frequency comes first

        // a:1  c:3  d:3  e:3  f:0 ... z:0 -> (freq=1:1) (freq=3:3) -> remove one `a` makes all freq=3 -> valid string
        if (frequency_and_count[0].first == 1 && frequency_and_count[0].second == 1)
            return "YES";
        // a:4  c:3  d:3  e:3  f:0 ... z:0 -> (freq=3:3) (freq=4:1) -> remove one `a` makes all freq=3 -> valid string
        // a:4  c:4  d:3  e:3  f:0 ... z:0 -> (freq=3:2) (freq=4:2) -> need to remove at least 2 chars to make all freq=3
        // thus, the higher frequency must be only 1 more than the other, and it must also appear only once
        else if (frequency_and_count[1].first - frequency_and_count[0].first == 1)
            if (frequency_and_count[1].second == 1)
                return "YES";

        return "NO";
    }
    else // 3 or more different frequencies
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
