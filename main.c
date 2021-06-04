
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"

int main() {

	T_ABR* abr = NULL;
	int nb_vaccins;
	char* marque = malloc(50 * sizeof(char));
	char* date = malloc(10 * sizeof(char));

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
			ajouterVaccinA(&abr, "2020-01-10", "Pfizer", 50);
			ajouterVaccinA(&abr, "2020-01-10", "Moderna", 10);
			ajouterVaccinA(&abr, "2020-01-10", "Johnson&Johnson", 25);
			ajouterVaccinA(&abr, "2020-01-10", "BioNTech", 30);
			ajouterVaccinA(&abr, "2020-01-10", "Oxford", 25);

			ajouterVaccinA(&abr, "2020-01-08", "Pfizer", 10);
			ajouterVaccinA(&abr, "2020-01-08", "Moderna", 200);
			ajouterVaccinA(&abr, "2020-01-08", "Johnson&Johnson", 75);
			ajouterVaccinA(&abr, "2020-01-08", "Oxford", 84);

			ajouterVaccinA(&abr, "2020-01-12", "Pfizer", 16);
			ajouterVaccinA(&abr, "2020-01-12", "Johnson&Johnson", 95);
			ajouterVaccinA(&abr, "2020-01-12", "BioNTech", 36);
			ajouterVaccinA(&abr, "2020-01-12", "Oxford", 58);

			ajouterVaccinA(&abr, "2020-01-14", "Pfizer", 70);
			ajouterVaccinA(&abr, "2020-01-14", "Johnson&Johnson", 3);
			ajouterVaccinA(&abr, "2020-01-14", "BioNTech", 45);

			ajouterVaccinA(&abr, "2020-01-06", "Moderna", 65);
			ajouterVaccinA(&abr, "2020-01-06", "Johnson&Johnson", 59);
			ajouterVaccinA(&abr, "2020-01-06", "BioNTech", 30);
			ajouterVaccinA(&abr, "2020-01-06", "Oxford", 45);

			ajouterVaccinA(&abr, "2020-01-07", "Pfizer", 74);
			ajouterVaccinA(&abr, "2020-01-07", "Moderna", 88);
			ajouterVaccinA(&abr, "2020-01-07", "Johnson&Johnson", 62);
			ajouterVaccinA(&abr, "2020-01-07", "BioNTech", 13);
			ajouterVaccinA(&abr, "2020-01-07", "Oxford", 65);

			ajouterVaccinA(&abr, "2020-01-09", "Pfizer", 22);
			ajouterVaccinA(&abr, "2020-01-09", "Johnson&Johnson", 45);
			ajouterVaccinA(&abr, "2020-01-09", "Oxford", 60);

			ajouterVaccinA(&abr, "2020-01-11", "Pfizer", 41);
			ajouterVaccinA(&abr, "2020-01-11", "Moderna", 28);
			ajouterVaccinA(&abr, "2020-01-11", "Johnson&Johnson", 19);
			ajouterVaccinA(&abr, "2020-01-11", "Oxford", 32);

			ajouterVaccinA(&abr, "2020-01-16", "Pfizer", 70);
			ajouterVaccinA(&abr, "2020-01-16", "Moderna", 165);
			ajouterVaccinA(&abr, "2020-01-16", "Johnson&Johnson", 32);
			ajouterVaccinA(&abr, "2020-01-16", "BioNTech", 110);
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
					printf("Attention : le nombre de vaccins de marque %s est strictement inferieur au montant a supprimer.\nSouhaitez-vous quand mme effectuer la modification? (y/n)\n", marque);
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

	//TODO : optimiser parcours suppression (parcours postfixe ou je sais plus trop)
	while (abr != NULL) {
		printf("-------- Reste a liberer la memoire de l'arbre suivant: --------");
		afficherStockAArbre(abr, 0);
		supprimerNoeud(&abr, abr->date);
	}

	printf("Arbre vide, sortie du programme...\n");

	return 0;
}
