#pragma once

typedef struct ListeVaccins {
	char* marque;
	unsigned int nombre_vaccins;
	struct ListeVaccins* suivant;
}T_ListeVaccins;

typedef struct ABR {
	char* date;
	T_ListeVaccins* liste_vaccins;
	struct ABR* fils_gauche;
	struct ABR* fils_droit;
}T_ABR;

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins);

void ajouterVaccinA(T_ABR** abr, char* date, char* marque, int nb_vaccins);

void afficherStockL(T_ListeVaccins* listeVaccins);
void afficherStockA(T_ABR* abr);

void afficherStockLArbre(T_ListeVaccins* listeVaccins, int hauteur);
void afficherStockAArbre(T_ABR* abr, int h);

int compterVaccinsListe(T_ListeVaccins* listeVaccins, char* marque);
int compterVaccins(T_ABR* abr, char* marque);

void deduireVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins);
void deduireVaccinA(T_ABR** abr, char* marque, int nb_vaccins);
void supprimerNoeud(T_ABR** abr, char* date);
void viderArbre(T_ABR** abr);
int verifValidDate(char* date);


void viderBuffer();
