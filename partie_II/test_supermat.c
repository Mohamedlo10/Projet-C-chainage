/**
 * test_supermat.c - Programme de test pour la bibliothèque supermat
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "supermat.h"

// Fonction d'affichage d'une supermatrice
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

// Test de l'allocation et de l'accès aux éléments
void testerAllocation() {
    printf("=== TEST D'ALLOCATION ===\n");
    
    SUPERMAT sm = allouerSupermat(3, 4);
    if (!sm) {
        printf("Échec de l'allocation\n");
        return;
    }
    
    // Initialiser avec des valeurs de test
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            acces(sm, i, j) = i * 10 + j;
        }
    }
    
    afficherSupermat(sm, "Matrice allouée");
    
    // Afficher les adresses des lignes pour vérification
    printf("Adresses des lignes:\n");
    for (int i = 0; i < sm->nl; i++) {
        printf("Ligne %d: %p\n", i, (void *)sm->ligne[i]);
    }
    
    rendreSupermat(sm);
    printf("Matrice libérée\n\n");
}

// Test du produit matriciel
void testerProduit() {
    printf("=== TEST DU PRODUIT MATRICIEL ===\n");
    
    SUPERMAT a = allouerSupermat(2, 3);
    SUPERMAT b = allouerSupermat(3, 2);
    
    if (!a || !b) {
        printf("Échec de l'allocation\n");
        if (a) rendreSupermat(a);
        if (b) rendreSupermat(b);
        return;
    }
    
    // Initialiser a
    acces(a, 0, 0) = 1.0; acces(a, 0, 1) = 2.0; acces(a, 0, 2) = 3.0;
    acces(a, 1, 0) = 4.0; acces(a, 1, 1) = 5.0; acces(a, 1, 2) = 6.0;
    
    // Initialiser b
    acces(b, 0, 0) = 7.0; acces(b, 0, 1) = 8.0;
    acces(b, 1, 0) = 9.0; acces(b, 1, 1) = 10.0;
    acces(b, 2, 0) = 11.0; acces(b, 2, 1) = 12.0;
    
    afficherSupermat(a, "Matrice A");
    afficherSupermat(b, "Matrice B");
    
    SUPERMAT c = produitSupermat(a, b);
    if (!c) {
        printf("Échec du produit matriciel\n");
        rendreSupermat(a);
        rendreSupermat(b);
        return;
    }
    
    afficherSupermat(c, "Produit A×B");
    
    rendreSupermat(a);
    rendreSupermat(b);
    rendreSupermat(c);
    printf("Matrices libérées\n\n");
}

// Test de la permutation de lignes
void testerPermutation() {
    printf("=== TEST DE PERMUTATION DE LIGNES ===\n");
    
    SUPERMAT sm = allouerSupermat(4, 3);
    if (!sm) {
        printf("Échec de l'allocation\n");
        return;
    }
    
    // Initialiser avec des valeurs de test
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            acces(sm, i, j) = i * 10 + j;
        }
    }
    
    afficherSupermat(sm, "Matrice originale");
    
    // Permuter les lignes 1 et 3
    permuterLignes(sm, 1, 3);
    
    afficherSupermat(sm, "Après permutation des lignes 1 et 3");
    
    // Vérifier la contiguïté
    int cont = analyserContiguite(sm);
    printf("Contiguïté après permutation: %d\n", cont);
    
    rendreSupermat(sm);
    printf("Matrice libérée\n\n");
}

// Test de l'extraction de sous-matrice
void testerSousMatrice() {
    printf("=== TEST D'EXTRACTION DE SOUS-MATRICE ===\n");
    
    SUPERMAT sm = allouerSupermat(4, 5);
    if (!sm) {
        printf("Échec de l'allocation\n");
        return;
    }
    
    // Initialiser avec des valeurs de test
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            acces(sm, i, j) = i * 10 + j;
        }
    }
    
    afficherSupermat(sm, "Matrice originale");
    
    // Extraire une sous-matrice
    SUPERMAT sub = sousMatrice(sm, 1, 3, 1, 3);
    if (!sub) {
        printf("Échec de l'extraction de sous-matrice\n");
        rendreSupermat(sm);
        return;
    }
    
    afficherSupermat(sub, "Sous-matrice (1:3, 1:3)");
    
    // Modifier la sous-matrice et vérifier que la matrice originale est aussi modifiée
    printf("Modification de la sous-matrice...\n");
    acces(sub, 1, 1) = 999.0;
    
    afficherSupermat(sub, "Sous-matrice modifiée");
    afficherSupermat(sm, "Matrice originale après modification de la sous-matrice");
    
    rendreSupermat(sub);
    rendreSupermat(sm);
    printf("Matrices libérées\n\n");
}

// Test de la conversion matrice <-> supermatrice
void testerConversion() {
    printf("=== TEST DE CONVERSION MATRICE <-> SUPERMATRICE ===\n");
    
    // Allouer une matrice classique
    int nld = 4;
    int ncd = 5;
    double *mat = (double *)malloc(nld * ncd * sizeof(double));
    if (!mat) {
        printf("Échec de l'allocation de la matrice classique\n");
        return;
    }
    
    // Initialiser la matrice classique
    for (int i = 0; i < nld; i++) {
        for (int j = 0; j < ncd; j++) {
            mat[i * ncd + j] = i * 10 + j;
        }
    }
    
    // Afficher la matrice classique
    printf("Matrice classique originale (%dx%d):\n", nld, ncd);
    for (int i = 0; i < nld; i++) {
        for (int j = 0; j < ncd; j++) {
            printf("%8.2f ", mat[i * ncd + j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Convertir en supermatrice
    SUPERMAT sm = matSupermat(mat, nld, ncd, 3, 4);
    if (!sm) {
        printf("Échec de la conversion matrice -> supermatrice\n");
        free(mat);
        return;
    }
    
    afficherSupermat(sm, "Supermatrice convertie");
    
    // Modifier la supermatrice
    printf("Modification de la supermatrice...\n");
    acces(sm, 1, 2) = 777.0;
    
    // Vérifier que la matrice classique a aussi été modifiée
    printf("Matrice classique après modification de la supermatrice:\n");
    for (int i = 0; i < nld; i++) {
        for (int j = 0; j < ncd; j++) {
            printf("%8.2f ", mat[i * ncd + j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Convertir la supermatrice modifiée en une nouvelle matrice classique
    double *new_mat = (double *)malloc(nld * ncd * sizeof(double));
    if (!new_mat) {
        printf("Échec de l'allocation de la nouvelle matrice classique\n");
        rendreSupermat(sm);
        free(mat);
        return;
    }
    
    // Initialiser à zéro
    for (int i = 0; i < nld * ncd; i++) {
        new_mat[i] = 0.0;
    }
    
    // Convertir
    int result = supermatMat(sm, new_mat, nld, ncd);
    if (result != 0) {
        printf("Échec de la conversion supermatrice -> matrice\n");
        free(new_mat);
        rendreSupermat(sm);
        free(mat);
        return;
    }
    
    // Afficher la nouvelle matrice classique
    printf("Nouvelle matrice classique après conversion:\n");
    for (int i = 0; i < nld; i++) {
        for (int j = 0; j < ncd; j++) {
            printf("%8.2f ", new_mat[i * ncd + j]);
        }
        printf("\n");
    }
    
    rendreSupermat(sm);
    free(mat);
    free(new_mat);
    printf("Mémoire libérée\n\n");
}

// Test de l'analyse de contiguïté
void testerContiguite() {
    printf("=== TEST D'ANALYSE DE CONTIGUÏTÉ ===\n");
    
    // Cas 1: Matrice normale (lignes contiguës et dans l'ordre)
    SUPERMAT sm1 = allouerSupermat(3, 4);
    if (!sm1) {
        printf("Échec de l'allocation\n");
        return;
    }
    
    int cont1 = analyserContiguite(sm1);
    printf("Contiguïté cas 1 (normale): %d\n", cont1);
    
    // Cas 2: Matrice avec lignes permutées
    permuterLignes(sm1, 0, 2);
    int cont2 = analyserContiguite(sm1);
    printf("Contiguïté cas 2 (permutée): %d\n", cont2);
    
    // Cas 3: Matrice avec lignes non contiguës
    SUPERMAT sm3 = (SUPERMAT)malloc(sizeof(supermat_t));
    sm3->nl = 3;
    sm3->nc = 4;
    sm3->ligne = (double **)malloc(3 * sizeof(double *));
    
    for (int i = 0; i < 3; i++) {
        sm3->ligne[i] = (double *)malloc(4 * sizeof(double));
    }
    
    int cont3 = analyserContiguite(sm3);
    printf("Contiguïté cas 3 (non contiguë): %d\n", cont3);
    
    // Libérer la mémoire
    rendreSupermat(sm1);
    
    // Libération manuelle pour sm3 car rendreSupermat() ne peut pas gérer ce cas spécial
    for (int i = 0; i < 3; i++) {
        free(sm3->ligne[i]);
    }
    free(sm3->ligne);
    free(sm3);
    
    printf("Mémoire libérée\n\n");
}

int main() {
    printf("PROGRAMME DE TEST DE LA BIBLIOTHÈQUE SUPERMAT\n\n");
    
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));
    
    // Exécuter les tests
    testerAllocation();
    testerProduit();
    testerPermutation();
    testerSousMatrice();
    testerConversion();
    testerContiguite();
    
    printf("Tous les tests ont été effectués.\n");
    
    return 0;
}