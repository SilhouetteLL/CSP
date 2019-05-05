#include <bits/stdc++.h>

int main()
{
    long long n;
    scanf("%lld",&n);
    long long arr[n];
    for(long long i = 0; i < n; i++)
    {
        scanf("%lld", arr + i);
    }
    std::sort(arr, arr + n);
    long long maxVal = arr[n - 1], minVal = arr[0];
    double midVal;
    if(n & 1)
    {
        midVal = arr[n / 2];
        printf("%lld %lld %lld", maxVal, arr[n / 2], minVal);
    }
    else
    {
        if(((arr[n / 2] + arr[n / 2 - 1]) % 2) ^ 1)
        {
            printf("%lld %lld %lld", maxVal, (arr[n / 2] + arr[n / 2 - 1]) / 2, minVal);
        }
        else
        {
            double val = double(arr[n / 2] + arr[n / 2 - 1]) / 2;
            printf("%lld %.1f %lld", maxVal, val, minVal);
        }
    }
}
