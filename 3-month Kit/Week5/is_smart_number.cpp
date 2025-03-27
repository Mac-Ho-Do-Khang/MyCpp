// https://www.hackerrank.com/challenges/three-month-preparation-kit-smart-number/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-five
// C++14 and 20 have nothing to debug, thus use C++11
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*
A smart number has an odd number of factors. Given a number `n` and its sqrt `m`, we always have that
the number of factors from [1->m] == [m->n]
                m                                               n
    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16
    |   |       |               |                               |
    |   '-----------------------'                               |
    '-----------------------------------------------------------'
The number of factors is odd only when that number has an integer sqrt
*/
bool is_smart_number(int num)
{
    int val = (int)sqrt(num);
    if ((double)num / val == val) // (num/val==1) -> ((double)num / val == val)
        return true;
    return false;
}

int main()
{

    int test_cases;
    cin >> test_cases;
    int num;
    for (int i = 0; i < test_cases; i++)
    {
        cin >> num;
        bool ans = is_smart_number(num);
        if (ans)
        {
            cout << "YES" << endl;
        }
        else
            cout << "NO" << endl;
    }
    return 0;
}
