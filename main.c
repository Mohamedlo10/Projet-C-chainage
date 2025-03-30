#include <stdio.h>
#include "fonctionnalite.h"

int main()
{
    restaurerDonnees();
    printf("=== Test de la fonction ajouterEtudiant ===\n");

    do
    {
        printf("\n1. Ajouter un etudiant\n");
        printf("2. Afficher les etudiants par ordre de merite\n");
        printf("3. Afficher les etudiants aleatoirement\n");
        printf("4. Afficher les etudiants par ordre de alphabetique\n");
        printf("5. Supprimer un etudiant\n");
        printf("6. Quitter\n");
        printf("\nChoix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            ajouterEtudiant();
            break;

        case 2:
            afficherParMerite();
            break;
        case 3:
            afficherParOrdreAleatoire();
            break;
        case 4:
            afficherParOrdreAlphabetique();
            break;
        case 5:
            supprimerEtudiant();
            break;

        case 6:
            sauvegarderDonnees();
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide, reessayez.\n");
        }
    } while (choix != 6);

    return 0;
}