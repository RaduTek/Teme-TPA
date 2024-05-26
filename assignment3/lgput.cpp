#include <fstream>

using namespace std;

ifstream fin("lgput.in");
ofstream fout("lgput.out");

unsigned long long modExp(unsigned long long n, unsigned long long p, unsigned long long q)
{
    unsigned long long r = 1;

    while (p > 0)
    {
        if (p % 2)
        {
            r = (r * n) % q;
        }
        n = (n * n) % q;
        p /= 2;
    }

    return r;
}

int main()
{
    unsigned long long n, p, q = 1999999973;
    fin >> n >> p;

    fout << modExp(n, p, q);

    fin.close();
    fout.close();
    return 0;
}