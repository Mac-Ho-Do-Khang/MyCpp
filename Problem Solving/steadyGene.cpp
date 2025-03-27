// https://www.hackerrank.com/challenges/bear-and-steady-gene/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(string gene)
{
    int n = gene.size();
    int quarter = n / 4;

    unordered_map<char, int> total_frequency = { {'A', 0}, {'T', 0}, {'G', 0}, {'C', 0} };
    for (char c : gene) total_frequency[c]++;

    unordered_map<char, int> excess_frequency;
    for (auto& i : total_frequency)
        excess_frequency[i.first] = i.second - quarter; // negative means lacking of the character
    
    if (excess_frequency['A'] == 0 && excess_frequency['T'] == 0
     && excess_frequency['G'] == 0 && excess_frequency['C'] == 0)
        return 0;

    // Sliding window to find the smallest substring to replace
    int left = 0, result = n;
    unordered_map<char, int> window_frequency = { {'A', 0}, {'T', 0}, {'G', 0}, {'C', 0} };
    for (int right = 0; right < n; ++right) 
    {
        window_frequency[gene[right]]++;
        while (window_frequency['A'] >= excess_frequency['A']
            && window_frequency['T'] >= excess_frequency['T']
            && window_frequency['G'] >= excess_frequency['G']
            && window_frequency['C'] >= excess_frequency['C'])
        {
            result = min(result, right - left + 1);
            window_frequency[gene[left]]--;
            left++;
        }
    }

    return result;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string gene;
    getline(cin, gene);

    int result = steadyGene(gene);

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
