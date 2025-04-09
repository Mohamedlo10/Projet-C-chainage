#ifndef SUPERMAT_H
#define SUPERMAT_H

typedef struct {
    int nl;          
    int nc;         
    double **ligne;  
} supermat_t, *SUPERMAT;

#define acces(a, i, j) ((a)->ligne[i][j])

SUPERMAT allouerSupermat(int nl, int nc);
SUPERMAT produitSupermat(SUPERMAT a, SUPERMAT b);
void permuterLignes(SUPERMAT a, int i, int j);
SUPERMAT sousMatrice(SUPERMAT a, int l1, int l2, int c1, int c2);
SUPERMAT matSupermat(double *m, int nld, int ncd, int nle, int nce);
int supermatMat(SUPERMAT sm, double *m, int nld, int ncd);
int analyserContiguite(SUPERMAT a);


void rendreSupermat(SUPERMAT sm);

#endif 