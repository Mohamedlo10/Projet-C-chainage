/**
 * supermat.h - Bibliothèque pour la gestion des supermatrices
 */

#ifndef SUPERMAT_H
#define SUPERMAT_H

/* Structure pour décrire une supermatrice */
typedef struct {
    int nl;           /* nombre de lignes */
    int nc;           /* nombre de colonnes */
    double **ligne;   /* tableau de pointeurs vers les lignes */
} supermat_t, *SUPERMAT;

/* Macro pour accéder aux éléments d'une supermatrice */
#define acces(a, i, j) ((a)->ligne[i][j])

/* Fonctions de gestion des supermatrices */

/**
 * Alloue une nouvelle supermatrice de taille nl x nc
 * @param nl Nombre de lignes
 * @param nc Nombre de colonnes
 * @return Pointeur vers la supermatrice allouée, NULL en cas d'échec
 */
SUPERMAT allouerSupermat(int nl, int nc);

/**
 * Calcule le produit matriciel a x b
 * @param a Première supermatrice
 * @param b Deuxième supermatrice
 * @return Résultat du produit matriciel, NULL en cas d'échec
 */
SUPERMAT produitSupermat(SUPERMAT a, SUPERMAT b);

/**
 * Permute les lignes i et j de la supermatrice a
 * @param a Supermatrice
 * @param i Première ligne à permuter
 * @param j Deuxième ligne à permuter
 */
void permuterLignes(SUPERMAT a, int i, int j);

/**
 * Extrait une sous-matrice de a
 * @param a Supermatrice source
 * @param l1 Première ligne de la sous-matrice
 * @param l2 Dernière ligne de la sous-matrice
 * @param c1 Première colonne de la sous-matrice
 * @param c2 Dernière colonne de la sous-matrice
 * @return Sous-matrice extraite, NULL en cas d'échec
 */
SUPERMAT sousMatrice(SUPERMAT a, int l1, int l2, int c1, int c2);

/**
 * Convertit une matrice classique en supermatrice
 * @param m Pointeur vers la matrice classique
 * @param nld Nombre de lignes déclarées
 * @param ncd Nombre de colonnes déclarées
 * @param nle Nombre de lignes effectives
 * @param nce Nombre de colonnes effectives
 * @return Supermatrice créée, NULL en cas d'échec
 */
SUPERMAT matSupermat(double *m, int nld, int ncd, int nle, int nce);

/**
 * Copie une supermatrice dans une matrice classique
 * @param sm Supermatrice source
 * @param m Pointeur vers la matrice de destination
 * @param nld Nombre de lignes déclarées
 * @param ncd Nombre de colonnes déclarées
 * @return 0 en cas de succès, -1 en cas d'échec
 */
int supermatMat(SUPERMAT sm, double *m, int nld, int ncd);

/**
 * Analyse la disposition des lignes d'une supermatrice
 * @param a Supermatrice à analyser
 * @return 2: lignes contiguës et dans l'ordre des indices
 *         1: lignes contiguës mais dans le désordre
 *         0: lignes non contiguës
 */
int analyserContiguite(SUPERMAT a);

/**
 * Libère l'espace occupé par une supermatrice
 * @param sm Supermatrice à libérer
 */
void rendreSupermat(SUPERMAT sm);

#endif /* SUPERMAT_H */