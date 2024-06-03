#include <fstream>
#include <vector>

using namespace std;

ifstream fin("inv.in");
ofstream fout("inv.out");

int mergeCount(int *S, int left, int mid, int right)
{
    int LSlen = mid - left + 1;
    int *LS = new int[LSlen];
    for (int i = 0; i < LSlen; ++i)
        LS[i] = S[left + i];

    int RSlen = right - mid;
    int *RS = new int[RSlen];
    for (int i = 0; i < RSlen; ++i)
        RS[i] = S[mid + 1 + i];

    int i = 0, j = 0, k = left;
    int count = 0;

    while (i < LSlen && j < RSlen)
    {
        if (LS[i] <= RS[j])
            S[k] = LS[i++];
        else
        {
            // Inversion condition matches
            S[k] = RS[j++];
            count += LSlen - i;
        }
        k++;
    }

    while (i < LSlen)
        S[k++] = LS[i++];

    while (j < RSlen)
        S[k++] = RS[j++];

    // fix memory leak
    delete[] LS;
    delete[] RS;

    return count;
}

int countInversions(int *S, int left, int right)
{
    if (left >= right)
        return 0;

    int mid = (left + right) / 2;

    int invCount = countInversions(S, left, mid);
    invCount += countInversions(S, mid + 1, right);
    invCount += mergeCount(S, left, mid, right);

    return invCount;
}

int main()
{
    unsigned n;
    unsigned count = 0;

    fin >> n;

    int *S = new int[n];
    for (unsigned i = 0; i < n; i++)
        fin >> S[i];

    count = countInversions(S, 0, n - 1);

    fout << count % 9917 << endl;

    fin.close();
    fout.close();
    return 0;
}