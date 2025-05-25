#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ETUDIANTS 100
#define NOM_FICHIER "etudiants.txt"

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    float moyenne;
} Etudiant;

Etudiant etudiants[MAX_ETUDIANTS];
int totalEtudiants = 0;

// Fonction pour ajouter un étudiant
void ajouterEtudiant() {
    if (totalEtudiants >= MAX_ETUDIANTS) {
        printf("Nombre maximal d'étudiants atteint.\n");
        return;
    }
    Etudiant e;
    e.id = totalEtudiants + 1;
    printf("Nom : ");
    scanf("%s", e.nom);
    printf("Prénom : ");
    scanf("%s", e.prenom);
    printf("Moyenne : ");
    scanf("%f", &e.moyenne);
    etudiants[totalEtudiants++] = e;
    printf("Étudiant ajouté avec succès.\n");
}

// Fonction pour afficher tous les étudiants
void afficherEtudiants() {
    if (totalEtudiants == 0) {
        printf("Aucun étudiant enregistré.\n");
        return;
    }
    printf("\nListe des étudiants :\n");
    for (int i = 0; i < totalEtudiants; i++) {
        printf("ID: %d | Nom: %s | Prénom: %s | Moyenne: %.2f\n",
               etudiants[i].id, etudiants[i].nom, etudiants[i].prenom, etudiants[i].moyenne);
    }
}

// Fonction pour trier les étudiants par moyenne décroissante
void trierEtudiants() {
    if (totalEtudiants < 2) {
        printf("Pas assez d'étudiants pour trier.\n");
        return;
    }
    for (int i = 0; i < totalEtudiants - 1; i++) {
        for (int j = i + 1; j < totalEtudiants; j++) {
            if (etudiants[i].moyenne < etudiants[j].moyenne) {
                Etudiant temp = etudiants[i];
                etudiants[i] = etudiants[j];
                etudiants[j] = temp;
            }
        }
    }
    printf("Étudiants triés par moyenne décroissante.\n");
}

// Fonction pour sauvegarder les étudiants dans un fichier
void sauvegarderEtudiants() {
    FILE *fichier = fopen(NOM_FICHIER, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    for (int i = 0; i < totalEtudiants; i++) {
        fprintf(fichier, "%d %s %s %.2f\n",
                etudiants[i].id, etudiants[i].nom, etudiants[i].prenom, etudiants[i].moyenne);
    }
    fclose(fichier);
    printf("Données sauvegardées dans '%s'.\n", NOM_FICHIER);
}

// Fonction pour charger les étudiants depuis un fichier
void chargerEtudiants() {
    FILE *fichier = fopen(NOM_FICHIER, "r");
    if (fichier == NULL) {
        printf("Fichier '%s' introuvable. Aucune donnée chargée.\n", NOM_FICHIER);
        return;
    }
    totalEtudiants = 0;
    while (fscanf(fichier, "%d %s %s %f",
                  &etudiants[totalEtudiants].id,
                  etudiants[totalEtudiants].nom,
                  etudiants[totalEtudiants].prenom,
                  &etudiants[totalEtudiants].moyenne) == 4) {
        totalEtudiants++;
        if (totalEtudiants >= MAX_ETUDIANTS) {
            printf("Limite maximale d'étudiants atteinte lors du chargement.\n");
            break;
        }
    }
    fclose(fichier);
    printf("Données chargées depuis '%s'.\n", NOM_FICHIER);
}

int main() {
    int choix;
    chargerEtudiants();
    do {
        printf("\n--- MENU ---\n");
        printf("1. Ajouter un étudiant\n");
        printf("2. Afficher les étudiants\n");
        printf("3. Trier les étudiants par moyenne\n");
        printf("4. Sauvegarder les étudiants\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                afficherEtudiants();
                break;
            case 3:
                trierEtudiants();
                break;
            case 4:
                sauvegarderEtudiants();
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 5);
    return 0;
}
