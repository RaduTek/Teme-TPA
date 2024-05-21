#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// @brief Read variable from stdin
/// @param prompt Prompt string
/// @return Read value
int read_var(char prompt[])
{
    int n;
    printf(prompt);
    while (scanf("%d", &n) != 1)
        printf("Format input invalid! Introdu numarul din nou!\n");
    return n;
}

/// @brief Afiseaza rezultatul operatiei, ca numere separate de spatii
/// @param k Numarul de elemente al rezultatului
/// @param multime Multimea numerelor
/// @param rezultat Multimea indicilor elementelor rezultate
void afiseaza_rezultat(int k, int *multime, int *rezultat)
{
    for (int i = 0; i < k; i++)
        printf("%d ", multime[rezultat[i]]);
    putchar('\n');
}

/// @brief Verifica daca indicele p a fost folosit in aranjament
/// @param n Numamrul de elemente al rezultatului
/// @param p Indicele de verificat
/// @param rezultat Multimea indicilor elementelor rezultate
/// @return True daca nu a fost gasit
bool verificare(int k, int p, int *rezultat)
{
    for (int i = 0; i < k; i++)
        if (rezultat[i] == p)
            return false;
    return true;
}

/// @brief Genereaza aranjamentele multimii la nivelul p
/// @param n Numarul de elemente al multimii
/// @param k Numarul de elemente de aranjat
/// @param multime Multimea elementelor
/// @param rezultat Multimea rezultatelor
/// @param p Indicele curent
/// @return Numarul de aranjamente generate
int combinari(int n, int k, int *multime, int *rezultat, int p)
{
    if (p == k)
    {
        afiseaza_rezultat(k, multime, rezultat);
        return 1;
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (verificare(p, i, rezultat))
        {
            rezultat[p] = i;
            count += combinari(n, k, multime, rezultat, p + 1);
        }
    }
    return count;
}

int main()
{
    int n, k;

    // Citeste numarul n
    n = read_var("Introdu numarul de elemente n=");
    k = read_var("Introdu numarul de aranjamente k=");

    // Alocare memorie
    int *multime = malloc(n * sizeof(int));
    int *rezultat = malloc(k * sizeof(int));
    if (multime == NULL || rezultat == NULL)
    {
        perror("Eroare la alocare");
        return -1;
    }

    // Citeste elementele multimii
    printf("Introdu elementele multimii:\n");
    for (int i = 0; i < n; i++)
    {
        multime[i] = read_var("");
    }

    printf("Aranjamente de %u luate cate %u ale multimii:\n", n, k);
    int count = combinari(n, k, multime, rezultat, 0);
    printf("Au fost generate %u aranjamente.\n", count);

    return 0;
}