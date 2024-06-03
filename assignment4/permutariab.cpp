#include <fstream>

using namespace std;

ifstream fin("permutariab.in");
ofstream fout("permutariab.out");

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
    int n;
    fin >> n;

    int *A = new int[n];
    int *B = new int[n];

    for (int i = 0; i < n; i++)
        fin >> A[i];
    for (int i = 0; i < n; i++)
        fin >> B[i];

    // Create index array for items of A
    int *I = new int[n];
    for (int i = 0; i < n; i++)
        I[A[i] - 1] = i;

    // Translate B array using index array map
    int *D = new int[n];
    for (int i = 0; i < n; i++)
        D[i] = I[B[i] - 1];

    // Count inversions in translated array
    int count = countInversions(D, 0, n - 1);

    fout << count;

    fin.close();
    fout.close();
    return 0;
}