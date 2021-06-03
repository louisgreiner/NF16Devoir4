
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"

// https://github.com/martinWANG2014?tab=repositories -> TutorielABR / TutorielListeChainee

int main() {

	T_ABR* abr = NULL;
	int nb_vaccins;
	char* marque = malloc(50 * sizeof(char));
	char* date = malloc(10 * sizeof(char));

	// insertion ordre chronologique croissante, pas de problème
	//ajouterVaccinA(&abr, "2020-01-01", "Moderna", 34);
	//ajouterVaccinA(&abr, "2020-01-01", "Pfizer", 127);

	//ajouterVaccinA(&abr, "2020-01-02", "Pfizer", 10);
	//ajouterVaccinA(&abr, "2020-01-02", "Moderna", 300);
	//ajouterVaccinA(&abr, "2020-01-02", "Pfizer", 99);

	//ajouterVaccinA(&abr, "2020-01-03", "Moderna", 34);

	//ajouterVaccinA(&abr, "2020-01-06", "Pfizer", 127);

	//ajouterVaccinA(&abr, "2020-01-10", "Pfizer", 10);

	//ajouterVaccinA(&abr, "2020-01-15", "Astrazeneca", 4532);

	//ajouterVaccinA(&abr, "2020-01-20", "Pfizer", 99);

	//ajouterVaccinA(&abr, "2020-01-21", "Astrazeneca", 50);

	//ajouterVaccinA(&abr, "2020-01-25", "Moderna", 142);


	// insertion ordre chronologique décroissante, mène à une segmentation fault
	ajouterVaccinA(&abr, "2020-01-25", "Moderna", 142);

	ajouterVaccinA(&abr, "2020-01-21", "Astrazeneca", 50);

	ajouterVaccinA(&abr, "2020-01-20", "Pfizer", 99);

	ajouterVaccinA(&abr, "2020-01-15", "Astrazeneca", 4532);

	ajouterVaccinA(&abr, "2020-01-10", "Pfizer", 10);

	ajouterVaccinA(&abr, "2020-01-06", "Pfizer", 127);

	ajouterVaccinA(&abr, "2020-01-03", "Moderna", 34);

	ajouterVaccinA(&abr, "2020-01-02", "Pfizer", 10);
	ajouterVaccinA(&abr, "2020-01-02", "Moderna", 300);
	ajouterVaccinA(&abr, "2020-01-02", "Pfizer", 99);

	ajouterVaccinA(&abr, "2020-01-01", "Moderna", 34);
	ajouterVaccinA(&abr, "2020-01-01", "Pfizer", 127);

	int choix = 0;
	do {
		printf("\n======================================\n");
		printf("1. Initialiser un ABR\n");
		printf("2. Ajouter un nombre de vaccins d'une marque dans un ABR par une date indiquee\n");
		printf("3. Afficher tous les stocks disponibles dans un ABR (affichage en ligne)\n");
		printf("4. Afficher tous les stocks disponibles dans un ABR (affichage en arbre)\n");
		printf("5. Compter le nombre de vaccins disponibles pour une marque indiquee\n");
		printf("6. Deduire un nombre de vaccins d'une marque indiquee dans un ABR\n");
		printf("7. Quitter\n");
		printf("\n======================================\n");

		choix = getchar();

		switch (choix) {
		case '1':
			printf("Choix 1\n");
			printf("(L'initialisation manuelle n'est pas necessaire car les noeuds sont initialises dynamiquement, on peut passer directement par l'option 2. Ajout)\n");
			break;
		case '2':
			printf("Choix 2\n");
			printf("date ? ");
			scanf("%s", date);
			if (verifValidDate(date) == 1) {
				printf("marque ? ");
				scanf("%s", marque);
				printf("nb_vaccins ? ");
				scanf("%d", &nb_vaccins);
				if (nb_vaccins > 0) {
					ajouterVaccinA(&abr, date, marque, nb_vaccins);
					printf("Insertion OK!");
				}
				else {
					printf("Erreur : le nombre de vaccins doit etre strictement positif!");
				}
			}
			else {
				printf("Erreur : format de date incorrect! Format attendu : AAAA-MM-JJ (soit YYYY-MM-DD)");
			}
			break;
		case '3':
			printf("Choix 3\n");
			printf("Affichage de tous les stocks disponibles (affichage en ligne):");
			afficherStockA(abr);
			break;
		case '4':
			printf("Choix 4\n");
			printf("Affichage de tous les stocks disponibles (affichage en arbre):");
			afficherStockAArbre(abr, 0);
			break;
		case '5':
			printf("Choix 5\n");
			printf("De quelle marque voulez-vous connaitre le stock?");
			scanf("%s", marque);
			printf("\nNombre total de vaccins %s : %d\n", marque, compterVaccins(abr, marque));
			break;
		case '6':
			printf("Choix 6\n");
			printf("marque ? ");
			scanf("%s", marque);
			printf("nb_vaccins ? ");
			scanf("%d", &nb_vaccins);
			viderBuffer();
			if (nb_vaccins > 0) {
				//NB SOUSTRAIT OK
				int nb_total = compterVaccins(abr, marque);
				if (nb_total == 0) {
					//VACCIN INEXISTANT
					printf("Erreur : aucun vaccin de marque %s n'est present dans la base de donnees\n",marque);
				}else if (nb_total < nb_vaccins) {
					//NB SOUSTRAIT SUPERIEUR A QTE
					printf("Attention : le nombre de vaccins de marque %s est strictement inferieur au montant a supprimer.\nSouhaitez-vous quand même effectuer la modification? (y/n)\n", marque);
					char validation;
					scanf("%c", &validation);
					if (validation == 'y' || validation == 'Y') {
						deduireVaccinA(&abr, marque, nb_vaccins);
					}
				}else {
					//TOUT OK
					deduireVaccinA(&abr, marque, nb_vaccins);
				}
			}else {
				//NB SOUSTRAIT INFERIEUR OU EGAL A ZERO
				printf("Erreur : le nombre de vaccins doit etre strictement positif!\n");
			}
			break;
		case '7':
			printf("Choix 7 : Quitter\n");
			break;
		default:
			printf("Choix invalide\n");
		}
		viderBuffer();


	} while (choix != '7');

	return 0;
}
