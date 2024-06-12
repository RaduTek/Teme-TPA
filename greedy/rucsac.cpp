#include <fstream>

using namespace std;

ifstream fin("rucsac.in");
ofstream fout("rucsac.out");

int N, G;
int W[5001], P[5001];
int D[5001][10001];

int main()
{
    fin >> N >> G;

    for (int i = 1; i <= N; i++)
    {
        fin >> W[i] >> P[i];
    }

    for (int i = 1; i <= N; i++)
    {
        for (int cw = 1; cw <= G; cw++)
        {
            if (W[i] > cw)
                D[i][cw] = D[i - 1][cw];
            else
                D[i][cw] = max(D[i - 1][cw], D[i - 1][cw - W[i]] + P[i]);
        }
    }

    fout << D[N][G] << endl;

    fin.close();
    fout.close();
    return 0;
}