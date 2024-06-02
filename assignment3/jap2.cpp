#include <fstream>
#include <iostream>

using namespace std;

ifstream fin("jap2.in");
ofstream fout("jap2.out");

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

ll combinations(ll n, ll k, ll mod, ll f[])
{
    ll n_f = f[n % mod];
    ll k_f = f[k % mod];
    ll nk_f = f[(n - k) % mod];

    ll result = (n_f * modInv((k_f * nk_f) % mod, mod)) % mod;
    return result;
}

void precalc_factorials(ll f[], ll P)
{
    if (P < 2)
        return;
    for (ll i = 2; i <= P; i++)
    {
        f[i] = (f[i - 1] * i) % P;
    }
}

int main()
{
    ll P, Q, A, B;

    fin >> P >> Q;

    ll factorials[P + 1] = {1, 1};
    precalc_factorials(factorials, P);

    for (; Q; Q--)
    {
        fin >> A >> B;
        fout << combinations(A, B, P, factorials) << endl;
    }

    fin.close();
    fout.close();
    return 0;
}