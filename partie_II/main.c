/**
 * supermat_interactive.c - Application console interactive pour la gestion des supermatrices
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermat.h"

// Tableau global pour stocker les supermatrices
#define MAX_MATRICES 10
SUPERMAT matrices[MAX_MATRICES] = {NULL};
char matrixNames[MAX_MATRICES][20];

// Fonction pour afficher une supermatrice
void afficherSupermat(SUPERMAT sm, const char* nom) {
    if (!sm) {
        printf("%s est NULL\n", nom);
        return;
    }
    
    printf("%s (%dx%d):\n", nom, sm->nl, sm->nc);
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            printf("%8.2f ", acces(sm, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

// Fonction pour initialiser une matrice avec des valeurs aléatoires
void initialiserAleatoire(SUPERMAT sm) {
    if (!sm) return;
    
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            acces(sm, i, j) = (double)(rand() % 100) / 10.0;
        }
    }
}

// Fonction pour initialiser une matrice à partir de valeurs saisies par l'utilisateur
void initialiserManuel(SUPERMAT sm) {
    if (!sm) return;
    
    printf("Entrez les valeurs pour la matrice %dx%d:\n", sm->nl, sm->nc);
    for (int i = 0; i < sm->nl; i++) {
        printf("Ligne %d: ", i);
        for (int j = 0; j < sm->nc; j++) {
            scanf("%lf", &acces(sm, i, j));
        }
    }
}

// Fonction pour trouver l'indice d'une matrice par son nom
int trouverMatrice(const char* nom) {
    for (int i = 0; i < MAX_MATRICES; i++) {
        if (matrices[i] != NULL && strcmp(matrixNames[i], nom) == 0) {
            return i;
        }
    }
    return -1;
}

// Fonction pour trouver un emplacement libre
int trouverEmplacementLibre() {
    for (int i = 0; i < MAX_MATRICES; i++) {
        if (matrices[i] == NULL) {
            return i;
        }
    }
    return -1;
}

// Afficher le menu principal
void afficherMenu() {
    printf("\n=== GESTION DES SUPERMATRICES ===\n");
    printf("1. Créer une nouvelle matrice\n");
    printf("2. Afficher une matrice\n");
    printf("3. Calculer le produit de deux matrices\n");
    printf("4. Permuter des lignes\n");
    printf("5. Extraire une sous-matrice\n");
    printf("6. Supprimer une matrice\n");
    printf("7. Analyser la contiguïté d'une matrice\n");
    printf("8. Lister toutes les matrices\n");
    printf("9. Modifier une valeur dans une matrice\n");
    printf("0. Quitter\n");
    printf("Votre choix: ");
}

// Créer une nouvelle matrice
void creerMatrice() {
    int index = trouverEmplacementLibre();
    if (index == -1) {
        printf("Impossible de créer plus de matrices. Supprimez-en d'abord.\n");
        return;
    }
    
    char nom[20];
    int nl, nc;
    
    printf("Nom de la matrice: ");
    scanf("%19s", nom);
    
    // Vérifier si le nom existe déjà
    if (trouverMatrice(nom) != -1) {
        printf("Une matrice avec ce nom existe déjà.\n");
        return;
    }
    
    printf("Nombre de lignes: ");
    scanf("%d", &nl);
    printf("Nombre de colonnes: ");
    scanf("%d", &nc);
    
    SUPERMAT sm = allouerSupermat(nl, nc);
    if (!sm) {
        printf("Échec de l'allocation de la matrice.\n");
        return;
    }
    
    printf("Initialisation:\n");
    printf("1. Aléatoire\n");
    printf("2. Manuelle\n");
    printf("Votre choix: ");
    
    int choix;
    scanf("%d", &choix);
    
    switch(choix) {
        case 1:
            initialiserAleatoire(sm);
            break;
        case 2:
            initialiserManuel(sm);
            break;
        default:
            printf("Choix invalide. Initialisation aléatoire par défaut.\n");
            initialiserAleatoire(sm);
    }
    
    matrices[index] = sm;
    strcpy(matrixNames[index], nom);
    
    printf("Matrice '%s' créée avec succès.\n", nom);
    afficherSupermat(sm, nom);
}

// Afficher une matrice
void afficherMatriceExistante() {
    char nom[20];
    printf("Nom de la matrice à afficher: ");
    scanf("%19s", nom);
    
    int index = trouverMatrice(nom);
    if (index == -1) {
        printf("Matrice '%s' introuvable.\n", nom);
        return;
    }
    
    afficherSupermat(matrices[index], nom);
}

// Calculer le produit de deux matrices
void calculerProduit() {
    char nom1[20], nom2[20], nomResultat[20];
    
    printf("Nom de la première matrice: ");
    scanf("%19s", nom1);
    printf("Nom de la deuxième matrice: ");
    scanf("%19s", nom2);
    
    int index1 = trouverMatrice(nom1);
    int index2 = trouverMatrice(nom2);
    
    if (index1 == -1 || index2 == -1) {
        printf("Une ou plusieurs matrices introuvables.\n");
        return;
    }
    
    printf("Nom de la matrice résultat: ");
    scanf("%19s", nomResultat);
    
    // Vérifier si le nom existe déjà
    if (trouverMatrice(nomResultat) != -1) {
        printf("Une matrice avec ce nom existe déjà.\n");
        return;
    }
    
    SUPERMAT a = matrices[index1];
    SUPERMAT b = matrices[index2];
    
    if (a->nc != b->nl) {
        printf("Dimensions incompatibles pour le produit matriciel.\n");
        return;
    }
    
    SUPERMAT c = produitSupermat(a, b);
    if (!c) {
        printf("Échec du calcul du produit matriciel.\n");
        return;
    }
    
    int indexResultat = trouverEmplacementLibre();
    if (indexResultat == -1) {
        printf("Plus d'espace disponible pour stocker le résultat. Supprimez d'abord une matrice.\n");
        rendreSupermat(c);
        return;
    }
    
    matrices[indexResultat] = c;
    strcpy(matrixNames[indexResultat], nomResultat);
    
    printf("Produit matriciel calculé avec succès.\n");
    afficherSupermat(c, nomResultat);
}

// Permuter des lignes dans une matrice
void permuterLignesMatrice() {
    char nom[20];
    int i, j;
    
    printf("Nom de la matrice: ");
    scanf("%19s", nom);
    
    int index = trouverMatrice(nom);
    if (index == -1) {
        printf("Matrice '%s' introuvable.\n", nom);
        return;
    }
    
    SUPERMAT sm = matrices[index];
    printf("Première ligne à permuter (0-%d): ", sm->nl - 1);
    scanf("%d", &i);
    printf("Deuxième ligne à permuter (0-%d): ", sm->nl - 1);
    scanf("%d", &j);
    
    if (i < 0 || i >= sm->nl || j < 0 || j >= sm->nl) {
        printf("Indices de ligne invalides.\n");
        return;
    }
    
    permuterLignes(sm, i, j);
    printf("Lignes permutées avec succès.\n");
    afficherSupermat(sm, nom);
    
    // Analyser et afficher la contiguïté après permutation
    int cont = analyserContiguite(sm);
    printf("Contiguïté après permutation: ");
    switch(cont) {
        case 2:
            printf("lignes contiguës et dans l'ordre\n");
            break;
        case 1:
            printf("lignes contiguës mais dans le désordre\n");
            break;
        case 0:
            printf("lignes non contiguës\n");
            break;
    }
}

// Extraire une sous-matrice
void extraireSousMatrice() {
    char nom[20], nomResultat[20];
    int l1, l2, c1, c2;
    
    printf("Nom de la matrice source: ");
    scanf("%19s", nom);
    
    int index = trouverMatrice(nom);
    if (index == -1) {
        printf("Matrice '%s' introuvable.\n", nom);
        return;
    }
    
    SUPERMAT sm = matrices[index];
    printf("Première ligne (0-%d): ", sm->nl - 1);
    scanf("%d", &l1);
    printf("Dernière ligne (0-%d): ", sm->nl - 1);
    scanf("%d", &l2);
    printf("Première colonne (0-%d): ", sm->nc - 1);
    scanf("%d", &c1);
    printf("Dernière colonne (0-%d): ", sm->nc - 1);
    scanf("%d", &c2);
    
    printf("Nom de la sous-matrice: ");
    scanf("%19s", nomResultat);
    
    // Vérifier si le nom existe déjà
    if (trouverMatrice(nomResultat) != -1) {
        printf("Une matrice avec ce nom existe déjà.\n");
        return;
    }
    
    SUPERMAT sub = sousMatrice(sm, l1, l2, c1, c2);
    if (!sub) {
        printf("Échec de l'extraction de la sous-matrice.\n");
        return;
    }
    
    int indexResultat = trouverEmplacementLibre();
    if (indexResultat == -1) {
        printf("Plus d'espace disponible pour stocker le résultat. Supprimez d'abord une matrice.\n");
        rendreSupermat(sub);
        return;
    }
    
    matrices[indexResultat] = sub;
    strcpy(matrixNames[indexResultat], nomResultat);
    
    printf("Sous-matrice extraite avec succès.\n");
    afficherSupermat(sub, nomResultat);
    
    printf("Attention: Modifier cette sous-matrice modifiera également la matrice source.\n");
}

// Supprimer une matrice
void supprimerMatrice() {
    char nom[20];
    printf("Nom de la matrice à supprimer: ");
    scanf("%19s", nom);
    
    int index = trouverMatrice(nom);
    if (index == -1) {
        printf("Matrice '%s' introuvable.\n", nom);
        return;
    }
    
    rendreSupermat(matrices[index]);
    matrices[index] = NULL;
    matrixNames[index][0] = '\0';
    
    printf("Matrice '%s' supprimée avec succès.\n", nom);
}

// Analyser la contiguïté d'une matrice
void analyserContiguiteMat() {
    char nom[20];
    printf("Nom de la matrice à analyser: ");
    scanf("%19s", nom);
    
    int index = trouverMatrice(nom);
    if (index == -1) {
        printf("Matrice '%s' introuvable.\n", nom);
        return;
    }
    
    int cont = analyserContiguite(matrices[index]);
    printf("Contiguïté de la matrice '%s': ", nom);
    switch(cont) {
        case 2:
            printf("lignes contiguës et dans l'ordre\n");
            break;
        case 1:
            printf("lignes contiguës mais dans le désordre\n");
            break;
        case 0:
            printf("lignes non contiguës\n");
            break;
    }
}

// Lister toutes les matrices
void listerMatrices() {
    printf("\nListe des matrices disponibles:\n");
    int count = 0;
    
    for (int i = 0; i < MAX_MATRICES; i++) {
        if (matrices[i] != NULL) {
            printf("%d. %s (%dx%d)\n", i+1, matrixNames[i], matrices[i]->nl, matrices[i]->nc);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Aucune matrice disponible.\n");
    }
}

// Modifier une valeur dans une matrice
void modifierValeur() {
    char nom[20];
    int i, j;
    double val;
    
    printf("Nom de la matrice: ");
    scanf("%19s", nom);
    
    int index = trouverMatrice(nom);
    if (index == -1) {
        printf("Matrice '%s' introuvable.\n", nom);
        return;
    }
    
    SUPERMAT sm = matrices[index];
    printf("Ligne (0-%d): ", sm->nl - 1);
    scanf("%d", &i);
    printf("Colonne (0-%d): ", sm->nc - 1);
    scanf("%d", &j);
    
    if (i < 0 || i >= sm->nl || j < 0 || j >= sm->nc) {
        printf("Indices invalides.\n");
        return;
    }
    
    printf("Valeur actuelle: %.2f\n", acces(sm, i, j));
    printf("Nouvelle valeur: ");
    scanf("%lf", &val);
    
    acces(sm, i, j) = val;
    printf("Valeur modifiée avec succès.\n");
    afficherSupermat(sm, nom);
}

// Libérer toute la mémoire avant de quitter
void libererToutesMatrices() {
    for (int i = 0; i < MAX_MATRICES; i++) {
        if (matrices[i] != NULL) {
            rendreSupermat(matrices[i]);
            matrices[i] = NULL;
        }
    }
}

int main() {
    int choix = -1;
    
    printf("GESTION DES SUPERMATRICES - Application Interactive\n");
    printf("=================================================\n\n");

    
    do {
        afficherMenu();
        scanf("%d", &choix);
        
        printf("\n");
        
        switch(choix) {
            case 1:
                creerMatrice();
                break;
            case 2:
                afficherMatriceExistante();
                break;
            case 3:
                calculerProduit();
                break;
            case 4:
                permuterLignesMatrice();
                break;
            case 5:
                extraireSousMatrice();
                break;
            case 6:
                supprimerMatrice();
                break;
            case 7:
                analyserContiguiteMat();
                break;
            case 8:
                listerMatrices();
                break;
            case 9:
                modifierValeur();
                break;
            case 0:
                printf("Fermeture de l'application...\n");
                libererToutesMatrices();
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
        
        printf("\n");
        
    } while (choix != 0);
    
    return 0;
}