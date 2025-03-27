#include <iostream>
using namespace std;

void bubble_sort(int *arr, int n, bool (*compare)(int a, int b) = [](int a, int b)
                                  { return a < b; })
{
    for (int i{n - 1}; i > 0; --i)
        for (int j{}; j < i; ++j)
            if (!compare(arr[j], arr[j + 1]))
                swap(arr[j], arr[j + 1]);
}

void selection_sort(int *arr, int n, bool (*compare)(int a, int b) = [](int a, int b)
                                     { return a < b; })
{
    for (int i{}; i < n - 1; ++i)
    {
        int idx{i};
        for (int j{i + 1}; j < n; ++j)
            if (!compare(arr[idx], arr[j]))
                idx = j;
        if (idx != i)
            swap(arr[idx], arr[i]);
    }
}

void insertion_sort(int *arr, int n, bool (*compare)(int a, int b) = [](int a, int b)
                                     { return a < b; })
{
    for (int i{1}; i < n; ++i)
    {
        int temp{arr[i]};
        for (int j{i - 1}; j >= 0 && compare(temp, arr[j]); --j)
        {
            arr[j + 1] = arr[j];
            arr[j] = temp;
        }
    }
}

int main()
{
    int arr[] = {4, 5, 7, 8, 6, 4, 3, 2, 9};
    size_t n{sizeof arr / sizeof arr[0]};
    for (int i{}; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
    insertion_sort(arr, n, [](int a, int b)
                   { return a > b; });
    for (int i{}; i < 9; ++i)
        cout << arr[i] << " ";
}