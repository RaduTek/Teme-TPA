#include <fstream>

using namespace std;

int euclid_gcd(int &x, int &y, int a, int b)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1, d;
    d = euclid_gcd(x1, y1, b, a % b);

    x = y1;
    y = x1 - (a / b) * y1;

    return d;
}

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

int main()
{
    int n;
    fin >> n;

    for (; n; n--)
    {
        int a, b, c;
        fin >> a >> b >> c;

        int x = 0, y = 0;
        int d = euclid_gcd(x, y, a, b);

        if (c % d == 0)
        {
            x *= c / d;
            y *= c / d;
        }
        else
        {
            x = y = 0;
        }

        fout << x << ' ' << y << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
