#include <stdio.h>

int main()
{
    int SUIVANT[] = {1, 4, 3, 0, 5};
    int nbEtu = 0;
    int choix;

    for (int i = 0; i < (sizeof(SUIVANT) / sizeof(int)); i++)
    {
        printf("%d\t", SUIVANT[i]);
    }

    for (int i = 1; i < (sizeof(SUIVANT) / sizeof(int)); i++)
    {
        int j = i - 1;
        while (j >= 0)
        {
            int Cle = SUIVANT[j + 1];
            if (SUIVANT[j + 1] > SUIVANT[j])
            {
                SUIVANT[j + 1] = SUIVANT[j];

                SUIVANT[j] = Cle;
            }
            j--;
        }
    }
    printf(" Apres \n");

    for (int i = 0; i < (sizeof(SUIVANT) / sizeof(int)); i++)
    {
        printf("%d\t", SUIVANT[i]);
    }
    printf("  \n");
}