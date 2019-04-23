#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre_lexicographique_tab.h"
#include "liste.h"
#include "mot_le_plus_long.h"

int estValide(char *lettres,char mot_courant[]){
	int i=0;
	int j=0;
	while(mot_courant[i]!='\0'){
		j=0;
		while(lettres[j]!='\0'){
			if(lettres[j]==mot_courant[i]){
				return 1;
			}
			j++;
		}
		i++;
	}
	return 0;
}

Lm_mot *trouver_les_mots_rec(char *lettres, PNoeudTab dico,char mot_courant[],int index, Lm_mot * liste)
{
	int i;
	if(dico==NULL) return liste;
	if(dico->lettre != '.')
		mot_courant[index++]=dico->lettre;
	
	for(i=0;i<26;i++){
		liste = trouver_les_mots_rec(lettres, dico->fils[i], mot_courant, index, liste);
	}
	
	if((dico->fin_de_mot==fin)){
		mot_courant[index]='\0';
		if(estValide(lettres,mot_courant))
			liste = ajouter_Lmot(liste, mot_courant);
	}
	
	return liste;
}


Lm_mot *trouver_les_mots(char *lettres, PNoeudTab dico) {
	Lm_mot *res=NULL;
	char mot_courant[LONGUEUR_MAX_MOT];
	if(dico==NULL) return NULL;
	res = trouver_les_mots_rec(lettres,dico,mot_courant,0,NULL);
	return res;
}

void le_mot_le_plus_long(char *lettres, PNoeudTab dico, char *res) {

	Lm_mot *liste = trouver_les_mots(lettres, dico);
	Lm_mot *current = liste;
	char *motPlusGrand = "";

	while(current){//on parcours tous les mots qui contiennent au moins une des lettres
		if(strlen(current->mot) > strlen(motPlusGrand))//si la longueur est > au mot le plus grand
			motPlusGrand = current->mot;	//on le remplace
		current = current->suiv;
	}
	strcpy(res, motPlusGrand);	//on l'attribue a res
	detruire_Lmot(liste);		//on detruit la liste
}

Lm_mot *mots_de_longueur_donnee(char *lettres, PNoeudTab dico, int l) {
	Lm_mot *liste = trouver_les_mots(lettres, dico);
	Lm_mot *current = liste;
	Lm_mot *res;
	int check = 0;

	while(current){ //on parcours tous les mots qui contiennent au moins une des lettres
		if(strlen(current->mot)==l){ //si la longueur correspond
			if(check == 0){	//si c'est le premier on cree une liste
				res = creer_Lm_mot(current->mot);
				check = 1;
			}
			else res = ajouter_Lmot(res, current->mot); //sinon on ajoute à cette liste
		}
		current = current->suiv;
	}
	detruire_Lmot(liste);
	return res;
}
