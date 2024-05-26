#include <iostream>
#include <fstream>

using namespace std;

#define VARTYPE unsigned long long

#pragma region Matrix Utilities

VARTYPE **newMatrix()
{
    VARTYPE **M = new VARTYPE *[2];
    M[0] = new VARTYPE[2];
    M[1] = new VARTYPE[2];

    // Initialize with 2x2 identity matrix
    M[0][0] = 1;
    M[0][1] = 0;
    M[1][0] = 0;
    M[1][1] = 1;

    return M;
}

VARTYPE **copyMatrix(VARTYPE A[2][2])
{
    VARTYPE **M = newMatrix();
    M[0][0] = A[0][0];
    M[0][1] = A[0][1];
    M[1][0] = A[1][0];
    M[1][1] = A[1][1];
    return M;
}

void deleteMatrix(VARTYPE **A)
{
    delete[] A[0];
    delete[] A[1];
    delete[] A;
}

#pragma endregion

#pragma region Matrix Multiplication

VARTYPE **matrixMultiply(VARTYPE **A, VARTYPE **B)
{
    VARTYPE **M = newMatrix();

    M[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    M[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    M[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    M[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];

    return M;
}

VARTYPE **matrixMultiplyMod(VARTYPE **A, VARTYPE **B, VARTYPE q)
{
    VARTYPE **M = newMatrix();

    M[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % q;
    M[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % q;
    M[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % q;
    M[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % q;

    return M;
}

int iterationsCount = 0;

VARTYPE **matrixExpLog(VARTYPE A[2][2], VARTYPE n, VARTYPE q)
{
    VARTYPE **M = newMatrix();
    VARTYPE **B = copyMatrix(A);

    while (n > 0)
    {
        iterationsCount++;
        if (n % 2)
        {
            VARTYPE **T = matrixMultiplyMod(M, B, q);
            deleteMatrix(M);
            M = T;
        }
        VARTYPE **T = matrixMultiplyMod(B, B, q);
        deleteMatrix(B);
        B = T;
        n /= 2;
    }

    return M;
}

#pragma endregion

ifstream fin("kfib.in");
ofstream fout("kfib.out");

int main()
{
    VARTYPE k = 0;

    fin >> k;

    VARTYPE Z[2][2] = {{0, 1}, {1, 1}};
    VARTYPE modulus = 666013;

    VARTYPE **Fn = matrixExpLog(Z, k - 1, modulus);

    fout << Fn[1][1] << endl;

    fin.close();
    fout.close();

    return 0;
}