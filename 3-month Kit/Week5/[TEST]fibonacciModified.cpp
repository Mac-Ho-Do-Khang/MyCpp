//  https://www.hackerrank.com/challenges/fibonacci-modified/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'fibonacciModified' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER t1
 *  2. INTEGER t2
 *  3. INTEGER n
 */

/*
 * Only passes 7/10 testcases. The other 3 are TLE. Even with move assignment still results in TLE.
 * C++ has disadvantage in handling large numbers.
 * There seems to be no viable solution in C++, as the discussion section reveals none of them as well.
 */

class BigInt
{
    vector<int> digits; // digits[0] is LSB

public:
    BigInt(int num)
    {
        if (num == 0)
            digits.push_back(0); // `digits` cannot be empty
        while (num > 0)
        {
            digits.push_back(num % 10);
            num /= 10;
        }
    }

    BigInt operator+(const BigInt &other) const
    {
        BigInt result(0);
        int n = max(digits.size(), other.digits.size());
        result.digits.resize(n + 1, 0);

        int carry{};
        for (size_t i{}; i < n; ++i)
        {
            int sum{carry};
            if (i < digits.size())
                sum += digits[i];
            if (i < other.digits.size())
                sum += other.digits[i];
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }
        result.digits[n] = carry;

        // Remove leading zeros
        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();

        return result;
    }

    BigInt operator*(const BigInt &other) const
    {
        BigInt result(0);
        result.digits.resize(digits.size() + other.digits.size(), 0);

        for (size_t i = 0; i < digits.size(); ++i)
            for (size_t j = 0; j < other.digits.size(); ++j)
            {
                result.digits[i + j] += digits[i] * other.digits[j];
                result.digits[i + j + 1] += result.digits[i + j] / 10; // Carry
                result.digits[i + j] %= 10;
            }

        // Remove leading zeros
        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();

        return result;
    }

    friend ostream &operator<<(ostream &os, const BigInt &num)
    {
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it)
            os << *it;

        return os;
    }
};

BigInt fibonacciModified(int t1, int t2, int n)
{
    BigInt a{t1}, b{t2}, result{0};
    for (int i{}; i < n - 2; ++i)
    {
        result = a + b * b;
        a = b;
        b = result;
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int t1 = stoi(first_multiple_input[0]);

    int t2 = stoi(first_multiple_input[1]);

    int n = stoi(first_multiple_input[2]);

    BigInt result = fibonacciModified(t1, t2, n);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
