#include <fstream>
#include <iostream>

using namespace std;

ifstream fin("functii.in");
ofstream fout("functii.out");

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

ll modInv(ll base, ll mod)
{
    return modExp(base, mod - 2, mod);
}

ll factorial(ll n, ll mod)
{
    ll result = 1;
    for (ll i = 2; i <= n; i++)
        result = (result * i) % mod;
    return result;
}

ll combinations(ll n, ll k, ll mod)
{
    ll n_f = factorial(n, mod);
    ll nk_f = (factorial(k, mod) * factorial(n - k, mod)) % mod;

    ll result = (n_f * modInv(nk_f, mod)) % mod;
    return result;
}

int main()
{
    const ll mod = 30103;
    ll n, S, r, p;
    fin >> n >> S;

    r = combinations(n, S, mod);
    p = abs(modExp(2, S, mod) - 2);
    r = (r * p) % mod;

    fout << r;

    fin.close();
    fout.close();
    return 0;
}