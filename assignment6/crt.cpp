#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

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

ll modInv(ll base, ll mod)
{
    return modExp(base, phi(mod) - 1, mod);
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
    if (k > n)
        return 0;
    ll n_f = factorial(n, mod);
    ll nk_f = (factorial(k, mod) * factorial(n - k, mod)) % mod;

    ll result = (n_f * modInv(nk_f, mod)) % mod;
    return result;
}

ll lucas(ll n, ll k, ll mod)
{
    ll result = 1;
    while (max(n, k) > 0)
    {
        ll tn = n % mod;
        ll tk = k % mod;
        result *= combinations(tn, tk, mod);
        result %= mod;
        n /= mod;
        k /= mod;
    }
    return result;
}

ll crt(ll primes[], ll remainder[], int count)
{
    ll product = 1;
    for (ll i = 0; i < count; i++)
        product *= primes[i];

    ll result = 0;

    for (ll i = 0; i < count; i++)
    {
        ll pdiv = product / primes[i];
        result += remainder[i] * modInv(pdiv, primes[i]) * pdiv;
    }

    return result % product;
}

int prime_factors(ll primes[], ll n)
{
    int k = 0;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            primes[k++] = i;
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        primes[k++] = n;
    return k;
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

int solve(int n, int r, int m)
{
    ll primes[50];
    int count = prime_factors(primes, m);

    ll remainders[50];

    for (int i = 0; i < count; i++)
    {
        ll p = primes[i];

        ll factorials[p + 1] = {1, 1};
        precalc_factorials(factorials, p);

        remainders[i] = lucas(n, r, p);
    }

    return crt(primes, remainders, count);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);
        int r = stoi(first_multiple_input[1]);
        int m = stoi(first_multiple_input[2]);

        int result = solve(n, r, m);

        fout << result << "\n";
    }

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
