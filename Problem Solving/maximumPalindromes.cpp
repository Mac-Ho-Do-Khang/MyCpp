// https://www.hackerrank.com/challenges/maximum-palindromes/problem?isFullScreen=true
#include "stdc++.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
    ====================== = GENERAL PROBLEM ====================== =
    Given a substring 'abcccbbccbc', we can find the number of longest palindromes from it by :
    - Computing the frequencies : [a:1  b:5  c:6]
    - We aim for longest palindrome, thus any character appearing odd number of times can be used 
    to put into the middle -> center candidates : [a, b]
    - On each half of the palindrome there would be [a:1/2  b:5/2  c:6/2] -> [a:0  b:2  c:3]
    - Total combination of the half palindrome is (0 + 2 + 3)!/ (0!2!3!) = 10 
    => There are 10 palindromes with the same longest length

    --------------- Sub Problem 1: Finding frequencies ---------------
    Given a string 'abcbac' and index base 1, we compute :
                     a  b  c  d  ...  z
    - charFreq[0] = [0, 0, 0, 0, ..., 0]  // Empty prefix
    - charFreq[1] = [1, 0, 0, 0, ..., 0]  // 'a'
    - charFreq[2] = [1, 1, 0, 0, ..., 0]  // 'ab'
    - charFreq[3] = [1, 1, 1, 0, ..., 0]  // 'abc'
    - charFreq[4] = [1, 2, 1, 0, ..., 0]  // 'abcb'
    - charFreq[5] = [2, 2, 1, 0, ..., 0]  // 'abcba'
    - charFreq[6] = [2, 2, 2, 0, ..., 0]  // 'abcbac'
    For a given substring from position (left,right):
    - freq = charFreq[right] - charFreq[left - 1]
    - 'cba' (left = 3, right = 5) : freq = charFreq[5] - charFreq[2] = [1, 1, 1, 0, ..., 0]
    - This lets us compute character counts for any substring in O(26).Without it, counting character frequencies 
    for every substring would take O(right - left + 1), which is slower for very long substrings.

    --------------- Sub Problem 2 : Finding combinations ---------------
    -Factorials are used in computing combinations C(n, k)
    ​ - The modular inverse of x under modulo m is x ^ -1 such that x.x ^ -1 ≡ 1 (mod m)
    For m = 1e9 + 7 (which is prime), the modular inverse is computed using Fermat's Little Theorem:
                                            x^-1 ≡ x^(m−2) (mod m)
    - Use modular exponentiation for efficient computation.
    - Precompute factorial modulo m : fact[i] ≡ i!(mod m)
    - Precompute modular inverses of factorials : invFact[i] ≡ fact[i]^-1 (mod m) = fact[i]^(m - 2) (mod m)
    - Compute C(n, k) = fact[n] * invFact[n] * invFact[n - k](mod m)
    - Precomputing takes O(Nlogm)
    - Each C(n, k) query is O(1)
*/

const int MOD  = 1'000'000'007;
const int MAXN = 100'001;

vector<int> factorial(MAXN), invFactorial(MAXN);
vector<vector<int>> charFreq;

// Function to calculate modular exponentiation
int modPow(int base, int exp, int mod) 
{
    int result = 1;
    while (exp > 0) 
    {
        if (exp % 2 == 1) result = (1LL * result * base) % mod;
        base = (1LL * base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to precompute factorials and modular inverses
void precomputeFactorials() 
{
    factorial[0] = 1;
    for (int i = 1; i < MAXN; i++) 
        factorial[i] = (1LL * factorial[i - 1] * i) % MOD;
    
    invFactorial[MAXN - 1] = modPow(factorial[MAXN - 1], MOD - 2, MOD);
    for (int i = MAXN - 2; i >= 0; i--) 
        invFactorial[i] = (1LL * invFactorial[i + 1] * (i + 1)) % MOD;
    
}

// Function to compute nCr modulo MOD
int nCr(int n, int r) 
{
    if (r > n || n < 0 || r < 0) return 0;
    return (1LL * factorial[n] * invFactorial[r] % MOD * invFactorial[n - r] % MOD) % MOD;
}

/*
 * Complete the 'initialize' function below.
 *
 * The function accepts STRING s as parameter.
 */
void initialize(string s) // This function is called once before all queries.
{
    int n = s.size();
    charFreq.assign(n + 1, vector<int>(26, 0));

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < 26; j++) charFreq[i + 1][j] = charFreq[i][j];
        charFreq[i + 1][s[i] - 'a']++;
    }

    precomputeFactorials();
}

/*
 * Complete the 'answerQuery' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER l
 *  2. INTEGER r
 */
int answerQuery(int l, int r) // Return the answer for this query modulo 1'000'000'007.
{
    vector<int> freq(26);
    for (int i = 0; i < 26; i++) 
        freq[i] = charFreq[r][i] - charFreq[l - 1][i];

    int oddCount = 0, halfPerms = 0;
    int halfSum = 0;

    for (int f : freq) 
    {
        if (f % 2 == 1) oddCount++;
        halfSum += f / 2;
    }

    halfPerms = factorial[halfSum];
    for (int f : freq) 
        if (f / 2 > 0) 
            halfPerms = (1LL * halfPerms * invFactorial[f / 2]) % MOD;

    return (1LL * halfPerms * max(1, oddCount)) % MOD;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    initialize(s);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int l = stoi(first_multiple_input[0]);

        int r = stoi(first_multiple_input[1]);

        int result = answerQuery(l, r);

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
