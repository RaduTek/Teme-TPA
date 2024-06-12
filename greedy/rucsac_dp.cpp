#include <fstream>

using namespace std;

ifstream fin("rucsac.in");
ofstream fout("rucsac.out");

int N, G, j;
int W[5001], P[5001];
int D[2][10001];

int main()
{
    fin >> N >> G;

    for (int i = 1; i <= N; i++)
    {
        fin >> W[i] >> P[i];
    }

    for (int i = 1; i <= N; i++)
    {
        j ^= 1;
        for (int cw = 1; cw <= G; cw++)
        {
            if (W[i] > cw)
                D[j ^ 1][cw] = D[j][cw];
            else
                D[j ^ 1][cw] = max(D[j ^ 1][cw], D[j][cw - W[i]] + P[i]);
        }
    }

    fout << D[j][G] << endl;

    fin.close();
    fout.close();
    return 0;
}