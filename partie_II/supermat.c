
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "supermat.h"


SUPERMAT allouerSupermat(int nl, int nc) {
    if (nl <= 0 || nc <= 0) {
        return NULL;
    }
    
    SUPERMAT sm = (SUPERMAT)malloc(sizeof(supermat_t));
    if (!sm) {
        return NULL;
    }
    
    sm->nl = nl;
    sm->nc = nc;
    
    sm->ligne = (double **)malloc(nl * sizeof(double *));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    double *data = (double *)malloc(nl * nc * sizeof(double));
    if (!data) {
        free(sm->ligne);
        free(sm);
        return NULL;
    }
    
    for (int i = 0; i < nl; i++) {
        sm->ligne[i] = data + (i * nc);
    }
    
    return sm;
}

SUPERMAT produitSupermat(SUPERMAT a, SUPERMAT b) {
    if (!a || !b || a->nc != b->nl) {
        return NULL;
    }
    
    SUPERMAT c = allouerSupermat(a->nl, b->nc);
    if (!c) {
        return NULL;
    }
    
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

void permuterLignes(SUPERMAT a, int i, int j) {
    if (!a || i < 0 || j < 0 || i >= a->nl || j >= a->nl || i == j) {
        return;
    }
    
    double *temp = a->ligne[i];
    a->ligne[i] = a->ligne[j];
    a->ligne[j] = temp;
}

SUPERMAT sousMatrice(SUPERMAT a, int l1, int l2, int c1, int c2) {
    if (!a || l1 < 0 || l2 >= a->nl || l1 > l2 || c1 < 0 || c2 >= a->nc || c1 > c2) {
        return NULL;
    }
    
    SUPERMAT sm = (SUPERMAT)malloc(sizeof(supermat_t));
    if (!sm) {
        return NULL;
    }
    
    sm->nl = l2 - l1 + 1;
    sm->nc = c2 - c1 + 1;
    
    sm->ligne = (double **)malloc(sm->nl * sizeof(double *));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    for (int i = 0; i < sm->nl; i++) {
        sm->ligne[i] = &(a->ligne[l1 + i][c1]);
    }
    
    return sm;
}

SUPERMAT matSupermat(double *m, int nld, int ncd, int nle, int nce) {
    if (!m || nld <= 0 || ncd <= 0 || nle <= 0 || nce <= 0 || nle > nld || nce > ncd) {
        return NULL;
    }
    
    SUPERMAT sm = (SUPERMAT)malloc(sizeof(supermat_t));
    if (!sm) {
        return NULL;
    }
    
    sm->nl = nle;
    sm->nc = nce;
    
    sm->ligne = (double **)malloc(nle * sizeof(double *));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    for (int i = 0; i < nle; i++) {
        sm->ligne[i] = m + (i * ncd);
    }
    
    return sm;
}


int supermatMat(SUPERMAT sm, double *m, int nld, int ncd) {
    if (!sm || !m || nld <= 0 || ncd <= 0 || sm->nl > nld || sm->nc > ncd) {
        return -1;
    }
    
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            m[i * ncd + j] = acces(sm, i, j);
        }
    }
    
    return 0;
}


int analyserContiguite(SUPERMAT a) {
    if (!a || a->nl <= 1) {
        return 2;  // Trivial 
    }
    
    int contigues = 1;
    for (int i = 1; i < a->nl; i++) {
        if (a->ligne[i] != a->ligne[i-1] + a->nc) {
            contigues = 0;
            break;
        }
    }
    

    if (contigues==1) {
        return 2;  
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
        return 1;  
    }
    else return 0; 
}


void rendreSupermat(SUPERMAT sm) {
    if (!sm) {
        return;
    }
    
    int cont = analyserContiguite(sm);
    
    if (cont == 2) {
        free(sm->ligne[0]);
    } else if (cont == 0) {
        for (int i = 0; i < sm->nl; i++) {
            free(sm->ligne[i]);
        }
    } else {
        double *min_ptr = sm->ligne[0];
        for (int i = 1; i < sm->nl; i++) {
            if (sm->ligne[i] < min_ptr) {
                min_ptr = sm->ligne[i];
            }
        }
        free(min_ptr);
    }
    
    free(sm->ligne);
    
    free(sm);
}
