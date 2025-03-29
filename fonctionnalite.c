#include <stdio.h>
#include "fonctionnalite.h"
#include <string.h>

Etudiant VETU[MAX_ETUDIANTS];
int SUIVANT[MAX_ETUDIANTS];
int ALPHABETIQUE[MAX_ETUDIANTS];
int nbEtu = 0;
int choix;
int DEB = -1;
int DEBAlph = -1;

void ajouterEtudiant()
{
    double note;

    if (nbEtu >= 99)
    {
        printf("Erreur, Espace insufisant: le nombre limite d'etudiant a ete atteint");
        return;
    }
    if (nbEtu < 0)
    {
        printf("Erreur, la valeur fournie pournbEtu est invalide");
        return;
    };

    printf("Veuillez saisir le nom de l'etudiant : ");
    scanf("%29s", VETU[nbEtu].nom);
    getchar();
    printf("Veuillez saisir la note sur 100 de l'etudiant : ");
    scanf("%lf", &note);
    getchar();

    while (note < 0 || note > 100)
    {
        printf("Erreur, Veuillez saisir une note comprise entre 0 et 100 : ");
        scanf("%lf", &note);
    }

    VETU[nbEtu].note = note;
    VETU[nbEtu].numero = nbEtu;
    printf("Insertion de l'etudiant %s reussi \n", VETU[nbEtu].nom);

    chainageAlphabetique(VETU[nbEtu]);
    chainageSuivant(VETU[nbEtu]);
}

void chainageSuivant(Etudiant e)
{
    int i = nbEtu++;
    SUIVANT[i] = -1;
    if (DEB == -1 || e.note > VETU[DEB].note)
    {
        SUIVANT[i] = DEB;
        DEB = i;
    }
    else
    {
        int prec = DEB;
        int cour = SUIVANT[DEB];
        while (cour != -1 && VETU[cour].note >= e.note)
        {
            prec = cour;
            cour = SUIVANT[cour];
        }
        SUIVANT[prec] = i;
        SUIVANT[i] = cour;
    }
}

void chainageAlphabetique(Etudiant e)
{
    int i = nbEtu;
    ALPHABETIQUE[i] = -1;
    if (DEBAlph == -1 || strcmp(e.nom, VETU[DEBAlph].nom) < 0) // deuxieme chaine superieure  a la premiere
    {
        ALPHABETIQUE[i] = DEBAlph;
        DEBAlph = i;
    }
    else
    {
        int prec = DEBAlph;
        int cour = ALPHABETIQUE[DEBAlph];
        while (cour != -1 && strcmp(VETU[cour].nom, e.nom) <= 0) // deuxieme chaine superieure ou egale a la premiere
        {
            prec = cour;
            cour = ALPHABETIQUE[cour];
        }
        ALPHABETIQUE[prec] = i;
        ALPHABETIQUE[i] = cour;
    }
}

void supprimerEtudiant()
{
    int numero;
    printf("veuillez saisir le numero de l'etudiant : ");
    scanf("%d", &numero);
    if (numero >= nbEtu)
    {
        printf("Cet etudiant n'existe pas");
        return;
    }
    int successeur = SUIVANT[numero];
    int precedent;
    for (int i = 0; i < nbEtu; i++)
    {
        if (SUIVANT[i] == numero)
        {
            precedent = i;
            break;
        }
    }
    SUIVANT[precedent] = successeur;

    int successeur2 = ALPHABETIQUE[numero];
    int precedent2;
    for (int i = 0; i < nbEtu; i++)
    {
        if (ALPHABETIQUE[i] == numero)
        {
            precedent2 = i;
            break;
        }
    }

    ALPHABETIQUE[precedent2] = successeur2;

    for (int i = numero; i < nbEtu - 1; i++)
    {
        VETU[i] = VETU[i + 1];
    }
    nbEtu--;
    printf("Suppression reussi !\n");
}

void afficherParMerite()
{
    if (nbEtu == 0)
    {
        printf("Aucun etudiant a afficher.\n");
    }
    else
    {
        int i = DEB;
        while (i != -1)
        {
            printf("%d Numero: %d, Nom: %s, Note: %.1f\n", i,
                   VETU[i].numero, VETU[i].nom, VETU[i].note);
            i = SUIVANT[i];
        }
    }
}

void afficherParOrdreAlphabetique()
{
    if (nbEtu == 0)
    {
        printf("Aucun etudiant a afficher.\n");
    }
    else
    {
        int i = DEBAlph;
        while (i != -1)
        {
            printf("%d Numero: %d, Nom: %s, Note: %.1f\n", i,
                   VETU[i].numero, VETU[i].nom, VETU[i].note);
            i = ALPHABETIQUE[i];
        }
    }
}

void afficherParOrdreAleatoire()
{
    if (nbEtu == 0)
    {
        printf("Aucun etudiant a afficher.\n");
    }
    else
    {
        for (int i = 0; i < nbEtu; i++)
        {
            printf("Numero: %d, Nom: %s, Note: %.1f\n",
                   VETU[i].numero, VETU[i].nom, VETU[i].note);
        }
    }
}
