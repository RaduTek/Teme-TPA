#include <stdio.h>
#include <stdlib.h>

/// @brief Swap two int variables' contents
/// @param a Variable a
/// @param b Variable b
void swap(int *a, int *b)
{
    int _a = *a;
    *a = *b;
    *b = _a;
}

/// @brief Afiseaza multimea, ca numere separate de spatii
/// @param n Numarul de elemente a multimii
/// @param multime Pointer catre multime
void afisare(int n, int *multime)
{
    for (int i = 0; i < n; i++)
        printf("%d ", multime[i]);
    putchar('\n');
}

/// @brief Genereaza toate permutarile cu elementul de pe pozitia index-ului
/// @param n Numarul de elemente a multimii
/// @param multime Pointer catre multime
/// @param index Index-ul elementului cu care se permuta
/// @return Numarul de permutari generate
unsigned permutare(int n, int *multime, int index)
{
    if (index == n - 1)
    {
        afisare(n, multime);
        return 1;
    }

    unsigned count = 0;
    for (int i = index; i < n; i++)
    {
        swap(&multime[index], &multime[i]);
        count += permutare(n, multime, index + 1);
        swap(&multime[index], &multime[i]);
    }
    return count;
}

int main()
{
    unsigned n;

    // Citeste numarul n
    printf("Numarul de elemente n=");
    if (scanf("%u", &n) != 1)
    {
        printf("Format input invalid!\n");
        return -1;
    }

    // Alocare memorie
    int *multime = malloc(n * sizeof(int));
    if (multime == NULL)
    {
        perror("Eroare la alocare");
        return -1;
    }

    // Citeste elementele multimii
    printf("Introdu elementele multimii:\n");
    for (int i = 0; i < n; i++)
    {
        while (scanf("%d", &multime[i]) != 1)
            printf("Format input invalid! Introdu numarul din nou!\n");
    }

    printf("Permutari ale multimii:\n");
    unsigned count = permutare(n, multime, 0);
    printf("Au fost generate %u permutari.\n", count);

    return 0;
}