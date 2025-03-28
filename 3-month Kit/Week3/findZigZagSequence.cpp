// https://www.hackerrank.com/challenges/three-month-preparation-kit-zig-zag-sequence/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=three-month-preparation-kit&playlist_slugs%5B%5D=three-month-week-three
#include <bits/stdc++.h>
using namespace std;

void findZigZagSequence(vector<int> a, int n)
{
    sort(a.begin(), a.end());
    int mid = (n) / 2; // ((n-1) / 2) -> ((n) / 2)
    swap(a[mid], a[n - 1]);

    int st = mid + 1;
    int ed = n - 2; // (n - 1) -> (n -2)
    while (st <= ed)
    {
        swap(a[st], a[ed]);
        st = st + 1;
        ed = ed - 1; // (ed + 1) -> (ed - 1)
    }
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
            cout << " ";
        cout << a[i];
    }
    cout << endl;
}

int main()
{
    int n, x;
    int test_cases;
    cin >> test_cases;

    for (int cs = 1; cs <= test_cases; cs++)
    {
        cin >> n;
        vector<int> a;
        for (int i = 0; i < n; i++)
        {
            cin >> x;
            a.push_back(x);
        }
        findZigZagSequence(a, n);
    }
}
