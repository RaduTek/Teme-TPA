#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

ifstream fin("inversmodular.in");
ofstream fout("inversmodular.out");

#define ll long long

ll modExp(ll base, ll power, ll mod)
{
    ll result = 1;

    while (power > 0)
    {
        if (power % 2)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        power /= 2;
    }

    return result;
}

ll phi(ll n)
{
    ll result = n;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main()
{
    ll A, N, X;
    fin >> A >> N;

    X = modExp(A, phi(N) - 1, N);

    fout << X;

    fin.close();
    fout.close();
    return 0;
}