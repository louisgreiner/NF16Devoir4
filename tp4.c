#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tp4.h"

// 1) Ajouter un nombre de vaccin dans une liste de vaccins donne, pour une marque donne
void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins) {
    if (*listeVaccins == NULL) {     //liste nulle / arriv en bout de liste sans insrer -> on insre un nouveau maillon
        *listeVaccins = malloc(sizeof(T_ListeVaccins));
        (*listeVaccins)->nombre_vaccins = nb_vaccins;
        (*listeVaccins)->marque = malloc(51 * sizeof(char));
        strcpy((*listeVaccins)->marque, marque);
        (*listeVaccins)->suivant = NULL;
    }
    else if (strcmp((*listeVaccins)->marque, marque) == 0) {      //marque existante : on ajoute les vaccins  son total de vaccins
        (*listeVaccins)->nombre_vaccins += nb_vaccins;
    }
    else {      //pas de correspondance, pas en bout de liste -> on passe  l'lment suivant
        ajouterVaccinL(&(*listeVaccins)->suivant, marque, nb_vaccins);
    }
}

// 2) Ajouter un nombre de vaccin dans un ABR, pour une marque  une date donne
void ajouterVaccinA(T_ABR** abr, char* date, char* marque, int nb_vaccins) {
    if (*abr == NULL) {      //arbre nul / pas insr au niveau des feuilles -> nouvelle feuille
        *abr = (T_ABR*)malloc(sizeof(T_ABR));
        (*abr)->date = (char*)malloc(11 * sizeof(char));
        (*abr)->liste_vaccins = NULL;
        strcpy((*abr)->date, date);
        (*abr)->fils_droit = NULL;
        (*abr)->fils_gauche = NULL;
        ajouterVaccinL(&(*abr)->liste_vaccins, marque, nb_vaccins);
    }
    else if (comparerDates(date, (*abr)->date) > 0) {       //cl  insrer suprieure  cl parcourue -> insertion dans arbre droit
        ajouterVaccinA(&(*abr)->fils_droit, date, marque, nb_vaccins);
    }
    else if (comparerDates(date, (*abr)->date) < 0) {       //cl  insrer infrieure  cl parcourue -> insertion dans arbre gauche
        ajouterVaccinA(&(*abr)->fils_gauche, date, marque, nb_vaccins);
    }
    else {      //cl  insrer gale  cl parcourue : on ajoute les vaccins au noeud parcouru
        ajouterVaccinL(&(*abr)->liste_vaccins, marque, nb_vaccins);
    }
}

// 3.1) Afficher tous les stocks disponibles pour un ABR par ordre croissant de date, affichage en ligne
void afficherStockL(T_ListeVaccins* listeVaccins)
{
    T_ListeVaccins* temp_listeVaccins = listeVaccins;
    while (temp_listeVaccins != NULL) {
        if (temp_listeVaccins->nombre_vaccins > 0) { // test pas forcment utile
            printf("\n\t- %s (%d vaccins)", temp_listeVaccins->marque, temp_listeVaccins->nombre_vaccins);
        }
        temp_listeVaccins = temp_listeVaccins->suivant;
    }
    printf("\n");
}

// 4.1) Afficher tous les stocks disponibles dans un ABR pour une marque donne, affichage en ligne
void afficherStockA(T_ABR* abr)
{
    if (abr == NULL) {
        return;
    }
    if (abr->fils_gauche != NULL) { // fils gauche existe, on y va
        afficherStockA(abr->fils_gauche);
    }
    // on a pas / plus de fils gauche, donc on affiche ce noeud
    printf("\n- %s", abr->date);
    afficherStockL(abr->liste_vaccins);
    if (abr->fils_droit != NULL) { // fils gauche n'existe pas, mais fils droit existe, on y va
        afficherStockA(abr->fils_droit);
    }
}

// 3.2) Afficher tous les stocks disponibles pour un ABR par ordre croissant de date, affichage en arbre
void afficherStockLArbre(T_ListeVaccins* listeVaccins, int hauteur)
{
    T_ListeVaccins* temp_listeVaccins = listeVaccins;
    while (temp_listeVaccins != NULL) {
        if (temp_listeVaccins->nombre_vaccins > 0) { // test pas forcment utile
            for (int i = 0; i < hauteur; i++) {
                printf("\t\t");
            }
            printf("\t- %s (%d vaccins)\n", temp_listeVaccins->marque, temp_listeVaccins->nombre_vaccins);
        }
        temp_listeVaccins = temp_listeVaccins->suivant;
    }
    printf("\n");
}

// 4.2) Afficher tous les stocks disponibles dans un ABR pour une marque donne, affichage en arbre
void afficherStockAArbre(T_ABR* abr, int hauteur)
{
    if (abr == NULL) {
        return;
    }
    if (abr->fils_gauche != NULL) { // fils gauche existe, on y va
        afficherStockAArbre(abr->fils_gauche, hauteur + 1);
    }
    // on a pas / plus de fils gauche, donc on affiche ce noeud
    printf("\n ");
    for (int i = 0; i < hauteur; i++) {
        printf("\t\t");
    }
    printf("- %s (hauteur du noeud = %d)\n", abr->date, hauteur);
    afficherStockLArbre(abr->liste_vaccins, hauteur);
    if (abr->fils_droit != NULL) { // fils gauche n'existe pas, mais fils droit existe, on y va
        afficherStockAArbre(abr->fils_droit, hauteur + 1);
    }
}

// 5) Compter le nombre de vaccins disponibles dans un ABR pour une marque donne
int compterVaccinsListe(T_ListeVaccins* listeVaccins, char* marque)
{
    T_ListeVaccins* temp_listeVaccins = listeVaccins;
    while (temp_listeVaccins != NULL) {
        if (strcmp(temp_listeVaccins->marque, marque) == 0) { // on a trouv un vaccin de la bonne marque
            return temp_listeVaccins->nombre_vaccins;
        }
        temp_listeVaccins = temp_listeVaccins->suivant;
    }
    return(0);
}

int compterVaccins(T_ABR* abr, char* marque)
{
    if (abr == NULL) {
        return 0;
    }
    int total = 0;
    // On parcourt l'arbre en infixe pour parcourir tous les noeuds (tre sr d'en oublier aucun)
    if (abr->fils_gauche != NULL) { // fils gauche existe, on y va
        total += compterVaccins(abr->fils_gauche, marque);
    }
    // on a pas / plus de fils gauche, donc on compte dans ce noeud
    total += compterVaccinsListe(abr->liste_vaccins, marque);
    if (abr->fils_droit != NULL) { // fils gauche n'existe pas, mais fils droit existe, on y va
        total += compterVaccins(abr->fils_droit, marque);
    }
    return(total);
}

// 6) Dduire un nombre de vaccins d'une marque donne dans une liste de vaccins
void deduireVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins)
{
    if (*listeVaccins == NULL) { // cas liste nulle (ne devrait pas arriver)
        printf("impossible");
        return;
    }
    if (strcmp((*listeVaccins)->marque, marque) == 0) { // si la bonne marque se trouve en dbut de liste
        if ((*listeVaccins)->nombre_vaccins <= nb_vaccins) { // on veut retirer autant ou plus de vaccins que ce qu'il y en a => suppression du maillon
            (*listeVaccins) = (*listeVaccins)->suivant;
            return;
        }
        else { // on retire seulement une partie du stock de vaccin de ce jour
            (*listeVaccins)->nombre_vaccins -= nb_vaccins;
            return;
        }
    }

    T_ListeVaccins* temp_listeVaccins = (*listeVaccins); // peut-tre : "temp_listeVaccins = listeVaccins->suivant" pour optimiser et gagner 1 opration
    T_ListeVaccins* temp_listeVaccins_precedent = (*listeVaccins);

    // si la bonne marque ne se trouve pas en dbut de liste
    while (temp_listeVaccins != NULL) {
        if (strcmp(temp_listeVaccins->marque, marque) == 0) { // on a trouv un vaccin de la bonne marque
            if (temp_listeVaccins->nombre_vaccins <= nb_vaccins) { // on veut retirer autant ou plus de vaccins que ce qu'il y en a => suppression du maillon
                temp_listeVaccins_precedent->suivant = temp_listeVaccins->suivant;
                free(temp_listeVaccins->marque);
                free(temp_listeVaccins);
                return;
            }
            else { // on retire seulement une partie du stock de vaccin de ce jour
                temp_listeVaccins->nombre_vaccins -= nb_vaccins;
                return;
            }
        }
        temp_listeVaccins_precedent = temp_listeVaccins;
        temp_listeVaccins = temp_listeVaccins->suivant;
    }
}


void deduireVaccinA(T_ABR** abr, char* marque, int nb_vaccins) {
    if (*abr == NULL) {
        return;
    }
    //On dduit les vaccins du sous-arbre gauche
    if ((*abr)->fils_gauche != NULL) {
        int temp_nb = compterVaccins((*abr)->fils_gauche, marque);
        deduireVaccinA(&(*abr)->fils_gauche, marque, nb_vaccins);
        nb_vaccins -= temp_nb - compterVaccins((*abr)->fils_gauche, marque);
    }
    if (nb_vaccins > 0) { //Il reste des vaccins  dduire => on dduit dans le noeud parcouru
        int temp_nb = compterVaccinsListe((*abr)->liste_vaccins, marque);
        deduireVaccinL(&(*abr)->liste_vaccins, marque, nb_vaccins);
        int total_noeud_courant = compterVaccinsListe((*abr)->liste_vaccins, marque);
        nb_vaccins -= temp_nb - total_noeud_courant;
        if ((*abr)->liste_vaccins==NULL) { //Plus aucun vaccin contenu dans le noeud courant => on le supprime
            printf("Plus de vaccins dans le noeud courant ! noeud : %s\n",(*abr)->date);
            supprimerNoeud(abr, (*abr)->date);
        }
    }
    if (*abr!=NULL && nb_vaccins > 0 && (*abr)->fils_droit != NULL) { //Il reste des vaccins  dduire => on dduit dans le sous-arbre droit
        deduireVaccinA(&(*abr)->fils_droit, marque, nb_vaccins);
    }
    // ce moment, les vaccins ont t dduits dans tout le sous arbre pass en paramtre.
    //S'il reste des vaccins  dduire dans l'arbre, alors ils le seront dans l'appel de fonction ayant appel l'itration courante
}

// Renvoie le noeud dont la date (= cl) est la plus petite de l'arbre aprs celle entre en paramtre
T_ABR** plusPetiteDate(T_ABR** abr, char* date)
{
    T_ABR** temp_abr = abr;
    while (&(*temp_abr) && &(*temp_abr)->fils_gauche != NULL && comparerDates(&(*temp_abr)->date, date) != 0) {
        (*temp_abr) = (*temp_abr)->fils_gauche;
    }
    return(temp_abr);
}


T_ABR** successeur(T_ABR* abr) {
    T_ABR** succ = NULL;
    if (abr->fils_droit != NULL) {
        succ = &abr->fils_droit;
        while ((*succ)->fils_gauche != NULL) {
            succ = &(*succ)->fils_gauche;
        }
    }
    else {
        succ = &abr->fils_gauche;
        while ((*succ)->fils_droit != NULL) {
            succ = &(*succ)->fils_droit;
        }
    }
    return succ;
}

/*
Supprime un noeud de date donne dans l'arbre donn
*/
void supprimerNoeud(T_ABR** abr, char* date)
{

    if (*abr == NULL) {
        return;
    }
    // si la date en entre est plus grande que celle du noeud actuel
    if (comparerDates(date, (*abr)->date) > 0) {
        supprimerNoeud(&((*abr)->fils_droit), date);
        return;
    }
    // sinon
    if (comparerDates(date, (*abr)->date) < 0) {
        supprimerNoeud(&((*abr)->fils_gauche), date);
        return;
    }

    //On ne librera rellement de noeud que si le noeud  supprimer a zro ou un fils
    if ((*abr)->fils_gauche == NULL) {
        free((*abr)->date);
        T_ABR* fils_droit = (*abr)->fils_droit;
        while ((*abr)->liste_vaccins != NULL) {
            deduireVaccinL(&(*abr)->liste_vaccins, (*abr)->liste_vaccins->marque, (*abr)->liste_vaccins->nombre_vaccins);
        }
        free(*abr);
        *abr = fils_droit;

    }else if((*abr)->fils_droit == NULL){
        free(((*abr)->date));
        T_ABR* fils_gauche = (*abr)->fils_gauche;
        while ((*abr)->liste_vaccins != NULL) {
            deduireVaccinL(&(*abr)->liste_vaccins, (*abr)->liste_vaccins->marque, (*abr)->liste_vaccins->nombre_vaccins);
        }
        free(*abr);

        *abr = fils_gauche;
    }
    else {
        //Dans le cas o le noeud a deux racines, on ne librera pas immdiatement de noeud :
        //On remplacera le noeud  supprimer par son successeur et on supprimera le successeur recopi (soit plus bas dans l'arbre)
        //La libration de mmoire aura donc lieu  ce moment
        T_ABR** succ = successeur(*abr);
        while ((*abr)->liste_vaccins != NULL){
            free((*abr)->liste_vaccins->marque);
            T_ListeVaccins* temp_liste = (*abr)->liste_vaccins;
            (*abr)->liste_vaccins = (*abr)->liste_vaccins->suivant;
            free(temp_liste);
        }
        strcpy((*abr)->date, (*succ)->date);
        (*abr)->liste_vaccins = (*succ)->liste_vaccins;
        supprimerNoeud(succ, (*succ)->date);

    }

}

/*
Permet de vider le buffer de l'entree standard, afin d'eviter des problomes a la saisie
*/
void viderBuffer()
{
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/*
ATTENTION ! Il faut bien vrifier le format des deux dates avant d'appeler cette fonction!
Compare deux dates : si la premire est suprieure  la deuxime, renvoie 1 ; si elle est infrieure  la deuxime, renvoie 2 ; et renvoie 0 en cas d'galit
Cette comparaison est possible de cette manire car les dates sont en format YYYY-MM-DD (ou AAAA-MM-JJ)
En effet, les premiers caractres de la date sont les plus significatifs, et les derniers sont les moins significatifs
Les tirets sparant annes, mois et jours n'auront pas d'incidence sur le rsultat, car ils sont toujours gaux entre eux
*/
int comparerDates(char* date1, char* date2) {
    //On compare chaque caractre de chaque chane
    for (int i = 0; i < 10; i++) {
        if (date1[i] > date2[i]) {
            return(1);   //un chiffre est suprieur dans la date 1 => la date 1 est suprieure  la 2
        }
        else if (date1[i] < date2[i]) {
            return(-1);  //un chiffre est infrieur dans la date 1 => la date 1 est infrieure  la 2
        }
    }
    return 0;       //aucune diffrence trouve => les dates sont identiques
}

int verifValidDate(char* date) {
    for (int i = 0; i < 10 ; i++) {
        if (date[i] == '\0') {
            printf("trop court\n");
            return 0;
        }
        else {
            if (i < 4 || i>4 && i < 7 || i>7) {
                if (date[i] < '0' || date[i]>'9') {
                    printf("nan\n");
                    return 0;
                }
            }
            else {
                if (date[i] != '-') {
                    printf("not a tiret\n");
                    return 0;
                }
            }
        }
    }
    if (date[5] > '1') {                        //limitation de la dizaine du mois  1 (pour 10)
        return 0;
    }
    if (date[5] == '1' && date[6] > 2) {        //limitation du mois  12
        return 0;
    }
    if (date[8] > '3') {                        //limitation de la dizaine du jour  3 (pour 30)
        return 0;
    }
    if (date[8] == '3' && date[9] > 1) {        //limitation du jour  31
        return 0;
    }
    //TODO : ajouter vrification pousse (ex : anne bissextile, 31 fvrier, ...)

    return 1;   //arriv ici, la date a pass toutes les vrifications avec succs : elle est donc valide (bien que pas forcment cohrente!)
}
