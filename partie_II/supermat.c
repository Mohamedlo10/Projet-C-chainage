/**
 * supermat.c - Implémentation de la bibliothèque pour la gestion des supermatrices
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "supermat.h"

/**
 * Alloue une nouvelle supermatrice de taille nl x nc
 * Par YOUSSOU
 */
SUPERMAT allouerSupermat(int nl, int nc) {
    if (nl <= 0 || nc <= 0) {
        return NULL;
    }
    
    // Allouer le descripteur
    SUPERMAT sm = (SUPERMAT)malloc(sizeof(supermat_t));
    if (!sm) {
        return NULL;
    }
    
    // Initialiser les dimensions
    sm->nl = nl;
    sm->nc = nc;
    
    // Allouer le tableau de pointeurs pour les lignes
    sm->ligne = (double **)malloc(nl * sizeof(double *));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    // Allouer l'espace pour tous les éléments en une fois
    double *data = (double *)malloc(nl * nc * sizeof(double));
    if (!data) {
        free(sm->ligne);
        free(sm);
        return NULL;
    }
    
    // Initialiser les pointeurs de lignes
    for (int i = 0; i < nl; i++) {
        sm->ligne[i] = data + (i * nc);
    }
    
    return sm;
}

/**
 * Calcule le produit matriciel a x b
 * Par AMAROU
 */
SUPERMAT produitSupermat(SUPERMAT a, SUPERMAT b) {
    // Vérifier que les dimensions sont compatibles
    if (!a || !b || a->nc != b->nl) {
        return NULL;
    }
    
    // Allouer la matrice résultat
    SUPERMAT c = allouerSupermat(a->nl, b->nc);
    if (!c) {
        return NULL;
    }
    
    // Calculer le produit matriciel
    for (int i = 0; i < a->nl; i++) {
        for (int j = 0; j < b->nc; j++) {
            acces(c, i, j) = 0.0;
            for (int k = 0; k < a->nc; k++) {
                acces(c, i, j) += acces(a, i, k) * acces(b, k, j);
            }
        }
    }
    
    return c;
}

/**
 * Permute les lignes i et j de la supermatrice a
 * Par NDIAGA
 */
void permuterLignes(SUPERMAT a, int i, int j) {
    if (!a || i < 0 || j < 0 || i >= a->nl || j >= a->nl || i == j) {
        return;
    }
    
    // Permuter les pointeurs dans le tableau ligne
    double *temp = a->ligne[i];
    a->ligne[i] = a->ligne[j];
    a->ligne[j] = temp;
}

/**
 * Extrait une sous-matrice de a
 * Par FANTA
 */
SUPERMAT sousMatrice(SUPERMAT a, int l1, int l2, int c1, int c2) {
    // Vérifier les paramètres
    if (!a || l1 < 0 || l2 >= a->nl || l1 > l2 || c1 < 0 || c2 >= a->nc || c1 > c2) {
        return NULL;
    }
    
    // Allouer un nouveau descripteur
    SUPERMAT sm = (SUPERMAT)malloc(sizeof(supermat_t));
    if (!sm) {
        return NULL;
    }
    
    // Initialiser les dimensions
    sm->nl = l2 - l1 + 1;
    sm->nc = c2 - c1 + 1;
    
    // Allouer le tableau de pointeurs pour les lignes
    sm->ligne = (double **)malloc(sm->nl * sizeof(double *));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    // Initialiser les pointeurs de lignes pour pointer vers les données de a
    for (int i = 0; i < sm->nl; i++) {
        sm->ligne[i] = &(a->ligne[l1 + i][c1]);
    }
    
    return sm;
}

/**
 * Convertit une matrice classique en supermatrice
 * Par ALIOUNE
 */
SUPERMAT matSupermat(double *m, int nld, int ncd, int nle, int nce) {
    // Vérifier les paramètres
    if (!m || nld <= 0 || ncd <= 0 || nle <= 0 || nce <= 0 || nle > nld || nce > ncd) {
        return NULL;
    }
    
    // Allouer un nouveau descripteur
    SUPERMAT sm = (SUPERMAT)malloc(sizeof(supermat_t));
    if (!sm) {
        return NULL;
    }
    
    // Initialiser les dimensions
    sm->nl = nle;
    sm->nc = nce;
    
    // Allouer le tableau de pointeurs pour les lignes
    sm->ligne = (double **)malloc(nle * sizeof(double *));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    // Initialiser les pointeurs de lignes pour pointer vers les données de m
    for (int i = 0; i < nle; i++) {
        sm->ligne[i] = m + (i * ncd);
    }
    
    return sm;
}

/**
 * Copie une supermatrice dans une matrice classique
 * Par ALIOUNE
 */
int supermatMat(SUPERMAT sm, double *m, int nld, int ncd) {
    // Vérifier les paramètres
    if (!sm || !m || nld <= 0 || ncd <= 0 || sm->nl > nld || sm->nc > ncd) {
        return -1;
    }
    
    // Copier les éléments
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            m[i * ncd + j] = acces(sm, i, j);
        }
    }
    
    return 0;
}

/**
 * Analyse la disposition des lignes d'une supermatrice
 * Par LO
 */
int analyserContiguite(SUPERMAT a) {
    if (!a || a->nl <= 1) {
        return 2;  // Trivial 
    }
    
    //contigus et dans l'ordre
    int contigues = 1;
    for (int i = 1; i < a->nl; i++) {
        if (a->ligne[i] != a->ligne[i-1] + a->nc) {
            contigues = 0;
            break;
        }
    }
    
// c'est

    if (contigues==1) {
        return 2;  //contigus et dans l'ordre
    }

    double **sorted = (double **)malloc(a->nl * sizeof(double *));
    if (!sorted) {
        return 0; 
    }
    

    for (int i = 0; i < a->nl; i++) {
        sorted[i] = a->ligne[i];
    }


    
    for (int i = 0; i < a->nl - 1; i++) {
        for (int j = 0; j < a->nl - i - 1; j++) {
            if (sorted[j] > sorted[j+1]) {
                double *temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }

    contigues = 1;
    for (int i = 1; i < a->nl; i++) {
        if (sorted[i] != sorted[i-1] + a->nc) {
            contigues = 0;
            break;
        }
    }
    
    free(sorted);
        
    if (contigues==1) {
        return 1;  // contigus et dans le desordre 
    }
    else return 0; //pas contigus
}

/**
 * Libère l'espace occupé par une supermatrice
 * Par LO
 */
void rendreSupermat(SUPERMAT sm) {
    if (!sm) {
        return;
    }
    
    int cont = analyserContiguite(sm);
    
    if (cont == 2) {
        // Lignes contiguës et dans l'ordre: on peut libérer la première ligne
        free(sm->ligne[0]);
    } else if (cont == 0) {
        // Lignes non contiguës: libérer chaque ligne séparément
        for (int i = 0; i < sm->nl; i++) {
            free(sm->ligne[i]);
        }
    } else {
        // Lignes contiguës mais dans le désordre
        // Trouver la première adresse
        double *min_ptr = sm->ligne[0];
        for (int i = 1; i < sm->nl; i++) {
            if (sm->ligne[i] < min_ptr) {
                min_ptr = sm->ligne[i];
            }
        }
        free(min_ptr);
    }
    
    // Libérer le tableau des pointeurs
    free(sm->ligne);
    
    // Libérer le descripteur
    free(sm);
}
