#include <stdio.h>
#include "fonctionnalite.h"
#include <string.h>
#include <stdlib.h>

Etudiant VETU[MAX_ETUDIANTS];
int SUIVANT[MAX_ETUDIANTS];
int ALPHABETIQUE[MAX_ETUDIANTS];
int nbEtu = 0;
int choix;
int DEB = -1;
int DEBAlph = -1;
int dernierNumero = 0;
char *fichier = "etudiants.txt";


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
        printf("Erreur, la valeur fournie pour nbEtu est invalide");
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
    VETU[nbEtu].numero = ++dernierNumero;
    printf("Insertion de l'etudiant %s reussi (numero %d)\n", VETU[nbEtu].nom, VETU[nbEtu].numero);
    
    chainageAlphabetique(VETU[nbEtu]);
    chainageSuivant(VETU[nbEtu]);
    nbEtu++;
}
void chainageSuivant(Etudiant e)
{
    int i = nbEtu;
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

    if (DEBAlph == -1 || strcmp(e.nom, VETU[DEBAlph].nom) <= 0)
    {
        ALPHABETIQUE[i] = DEBAlph;
        DEBAlph = i;
    }
    else
    {
        int prec = DEBAlph;
        int cour = ALPHABETIQUE[DEBAlph];
        while (cour != -1 && strcmp(VETU[cour].nom, e.nom) <= 0)
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
    int numeroSuppression;
    int indiceEtudiant = -1;
    
    if (nbEtu == 0)
    {
        printf("Erreur: Aucun etudiant a supprimer.\n");
        return;
    }
    
    printf("Veuillez saisir le numero de l'etudiant a supprimer : ");
    scanf("%d", &numeroSuppression);
    getchar();
    

    for (int i = 0; i < nbEtu; i++)
    {
        if (VETU[i].numero == numeroSuppression)
        {
            indiceEtudiant = i;
            break;
        }
    }
    
    if (indiceEtudiant == -1)
    {
        printf("Erreur: Aucun etudiant avec le numero %d n'a ete trouve.\n", numeroSuppression);
        return;
    }
    
 
    if (DEB == indiceEtudiant)
    {
   
        DEB = SUIVANT[indiceEtudiant];
    }
    else
    {
        int precedent = DEB;
        while (SUIVANT[precedent] != indiceEtudiant && SUIVANT[precedent] != -1)
        {
            precedent = SUIVANT[precedent];
        }
        
        if (SUIVANT[precedent] == indiceEtudiant)
        {
            SUIVANT[precedent] = SUIVANT[indiceEtudiant];
        }
    }
    
  
    if (DEBAlph == indiceEtudiant)
    {
   
        DEBAlph = ALPHABETIQUE[indiceEtudiant];
    }
    else
    {
  
        int precedent = DEBAlph;
        while (ALPHABETIQUE[precedent] != indiceEtudiant && ALPHABETIQUE[precedent] != -1)
        {
            precedent = ALPHABETIQUE[precedent];
        }
        
        if (ALPHABETIQUE[precedent] == indiceEtudiant)
        {
            ALPHABETIQUE[precedent] = ALPHABETIQUE[indiceEtudiant];
        }
    }
    
    printf("L'etudiant %s (numero %d) a ete supprime avec succes.\n", 
           VETU[indiceEtudiant].nom, VETU[indiceEtudiant].numero);
    

    if (indiceEtudiant < nbEtu - 1)
    {
        VETU[indiceEtudiant] = VETU[nbEtu - 1];
 
        if (DEB == nbEtu - 1)
        {
            DEB = indiceEtudiant;
        }
        else 
        {
            int i = DEB;
            while (i != -1)
            {
                if (SUIVANT[i] == nbEtu - 1)
                {
                    SUIVANT[i] = indiceEtudiant;
                    break;
                }
                i = SUIVANT[i];
            }
        }
        

        if (DEBAlph == nbEtu - 1)
        {
            DEBAlph = indiceEtudiant;
        }
        else
        {
            int i = DEBAlph;
            while (i != -1)
            {
                if (ALPHABETIQUE[i] == nbEtu - 1)
                {
                    ALPHABETIQUE[i] = indiceEtudiant;
                    break;
                }
                i = ALPHABETIQUE[i];
            }
        }
        

        SUIVANT[indiceEtudiant] = SUIVANT[nbEtu - 1];
        ALPHABETIQUE[indiceEtudiant] = ALPHABETIQUE[nbEtu - 1];
    }
    
    nbEtu--;
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
        int rang = 1;
        while (i != -1)
        {
            printf("rang :%d Numero: %d, Nom: %s, Note: %.1f\n", rang,
                   VETU[i].numero, VETU[i].nom, VETU[i].note);
            i = SUIVANT[i];
            rang++;
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

            printf("Numero: %d, Nom: %s, Note: %.1f\n",
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
        return;
    }
    
    int dejaAffiches[nbEtu];
    for (int i = 0; i < nbEtu; i++)
    {
        dejaAffiches[i] = 0;  
    }
    
    int compteur = 0;
    
    while (compteur < nbEtu)
    {
        int idx = rand() % nbEtu;
        
        if (dejaAffiches[idx] == 0)
        {
            printf("Numero: %d, Nom: %s, Note: %.1f\n",
                   VETU[idx].numero, VETU[idx].nom, VETU[idx].note);
            
            dejaAffiches[idx] = 1;  // Marquer comme affiché
            compteur++;
        }
    }
}

void sauvegarderDonnees()
{
    FILE *f = fopen(fichier, "w");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s pour sauvegarde.\n", fichier);
        return;
    }


    fprintf(f, "%d %d %d %d\n", nbEtu, DEB, DEBAlph,dernierNumero);

    
    for (int i = 0; i < nbEtu; i++)
    {
        fprintf(f, "%d %s %lf\n", VETU[i].numero, VETU[i].nom, VETU[i].note);
    }

    
    for (int i = 0; i < nbEtu; i++)
    {
        fprintf(f, "%d \n", SUIVANT[i]);
    }

    
    for (int i = 0; i < nbEtu; i++)
    {
        fprintf(f, "%d ", ALPHABETIQUE[i]);
    }
    fprintf(f, "\n");

    fclose(f);
    printf("Donnees sauvegardees avec succes dans %s.\n", fichier);
}

void restaurerDonnees()
{
    FILE *f = fopen(fichier, "r");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s pour restauration.\n", fichier);
        return;
    }

    
    if (fscanf(f, "%d %d %d %d\n", &nbEtu, &DEB, &DEBAlph,&dernierNumero) != 4)
    {
        printf("Erreur lors de la lecture de nbEtu ,DEB, DEBAlph et dernierNumero.\n");
        fclose(f);
        return;
    }

    if (nbEtu < 0 || nbEtu > MAX_ETUDIANTS)
    {
        printf("Valeur de nbEtu invalide dans le fichier.\n");
        fclose(f);
        return;
    }

  
    for (int i = 0; i < nbEtu; i++)
    {
        if (fscanf(f, "%d %s %lf\n", &VETU[i].numero, VETU[i].nom, &VETU[i].note) != 3)
        {
            printf("Erreur lors de la lecture de VETU.\n");
            fclose(f);
            return;
        }
    }

    for (int i = 0; i < nbEtu; i++)
    {
        if (fscanf(f, "%d ", &SUIVANT[i]) != 1)
        {
            printf("Erreur lors de la lecture de SUIVANT.\n");
            fclose(f);
            return;
        }
    }

    for (int i = 0; i < nbEtu; i++)
    {
        if (fscanf(f, "%d ", &ALPHABETIQUE[i]) != 1)
        {
            printf("Erreur lors de la lecture de ALPHABETIQUE.\n");
            fclose(f);
            return;
        }
    }


    fclose(f);
    printf("Donnees restaurees avec succes depuis %s.\n", fichier);
}