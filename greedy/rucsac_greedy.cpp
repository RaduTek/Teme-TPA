#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("rucsac.in");
ofstream fout("rucsac.out");

typedef struct
{
    int w, p;
    double r;
} object_t;

int sortCompare(const object_t &a, const object_t &b)
{
    return a.r > b.r;
}

int main()
{
    int N, G;
    fin >> N >> G;

    vector<object_t> B(N);

    for (int i = 0; i < N; i++)
    {
        fin >> B[i].w >> B[i].p;
        B[i].r = (double)B[i].p / B[i].w;
    }

    // Sort objects by profit
    sort(B.begin(), B.end(), sortCompare);

    int remW = G;
    int curP = 0;
    for (int i = 0; i < N; i++)
    {
        if (remW - B[i].w >= 0)
        {
            remW -= B[i].w;
            curP += B[i].p;
        }
        else
        {
            double ratio = (double)remW / B[i].w;
            remW = 0;
            curP += ratio * B[i].p;
            break;
        }
    }

    fout << curP << endl;

    fin.close();
    fout.close();
    return 0;
}