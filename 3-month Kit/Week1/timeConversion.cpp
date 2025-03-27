// https://www.hackerrank.com/challenges/three-month-preparation-kit-time-conversion/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-one
#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */
stringstream &operator>>(stringstream &i, int &n)
{
    char c{};
    while (!isdigit(i.peek()) && !i.eof())
        i.get(c);
    (istream &)i >> n;
    return i;
}

string timeConversion(string s)
{
    int hour{}, minute{}, second{};
    stringstream ss{s};
    ss >> hour >> minute >> second;
    string time{s.substr(s.size() - 2)};
    if (time == "PM")
        hour += 12;
    if (hour == 12 || hour == 24)
        hour -= 12;
    stringstream o{};
    o << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << ":" << setw(2) << second; // 07:08:30 instead of 7:8:20
    return o.str();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
