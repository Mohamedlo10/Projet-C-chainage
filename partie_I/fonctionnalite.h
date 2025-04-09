#ifndef FONCTIONNALITE_H
#define FONCTIONNALITE_H
#define MAX_ETUDIANTS 100

typedef struct Etudiant
{
    int numero;
    char nom[30];
    double note;
} Etudiant;

extern Etudiant VETU[MAX_ETUDIANTS];
extern int SUIVANT[MAX_ETUDIANTS];
extern int ALPHABETIQUE[MAX_ETUDIANTS];
extern int nbEtu;
extern int choix;
extern int DEB;
extern int DEBAlph;
extern char *fichier;

void ajouterEtudiant();                // fait
void supprimerEtudiant();              // fait
void sauvegarderDonnees();             // Fait
void restaurerDonnees();               // Fait
void afficherParMerite();              // fait
void chainageSuivant(Etudiant e);      // fait
void chainageAlphabetique(Etudiant e); // fait
void afficherParOrdreAlphabetique();   // fait
void afficherParOrdreAleatoire();      // fait

#endif