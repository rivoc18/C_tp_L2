#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "carre_magique.h"
#include "arbre_lexicographique_tab.h"

Lm_mot *mots_de_longueur_donnee_dico(Lm_mot *dico, int l){
	Lm_mot * res=NULL;//la liste resultante
	Lm_mot * current = dico;//pour le parcours 
	
	//on parcours le dico 
	while(current){
		//si le mot est de la bonne taille
		if(strlen(current->mot)==l){
			//on ajoute a la liste res 
			res=ajouter_Lmot(res, current->mot);
		}
		current = current->suiv;
	}

	return res;
}

void afficher_carre(char **carre, int l){
	//affichage
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			printf("%c ",carre[i][j]);
		}
		printf("\n");
	}
}

void remplir_carre(char **carre, int l, int pos, PNoeudTab dico) {

	if(pos == l){
		//complet donc on laffiche
		afficher_carre(carre,l);
		printf("\n");
		return;
	}

	//on creer la liste des mots possible avec le bon prefixe
	char prefixe[l];
	int i;
	for(i=0;i<pos;i++){
		prefixe[i]=carre[pos][i];
	}
	prefixe[pos]='\0';

	Lm_mot * debut_liste_mot_prefixe= tous_les_mots_longueur_donnee(dico, prefixe,l);
	Lm_mot * liste_mot_prefixe=debut_liste_mot_prefixe;
	while(liste_mot_prefixe){ //parcours de la liste (//impossible a remplir)
		//remplit le carre
		carre[pos][pos]=liste_mot_prefixe->mot[pos];
		for(i=pos+1;i<l;i++){
			carre[pos][i]=liste_mot_prefixe->mot[i];
			carre[i][pos]=liste_mot_prefixe->mot[i];
		}
		remplir_carre(carre,l,pos+1,dico); //appel recursif
		liste_mot_prefixe=liste_mot_prefixe->suiv;
	}

	detruire_Lmot(debut_liste_mot_prefixe);
  	
}

void carre_magique (Lm_mot *dico, int l) {
	//fait appel a remplir avec tout les premiers mots
	int i;

	//on creer dico_tab
	Lm_mot * current =dico;
	PNoeudTab dico_tab = NULL;
	while(current){
		dico_tab = ajouter_mot(dico_tab,current->mot);
		current=current->suiv;
	}

	//initialise carre
	char **carre;
	carre = malloc(sizeof(char *)*l);
	for(i=0;i<l;i++){
		*(carre+i)=malloc(sizeof(char)*l);
	}

	Lm_mot *debut_liste_mot=mots_de_longueur_donnee_dico(dico,l);
	Lm_mot *liste_mot=debut_liste_mot;
	while(liste_mot){
		//on place le mot en 1er ligne/colone
		carre[0][0]=liste_mot->mot[0];
		for(i=1;i<l;i++){
			carre[0][i]=liste_mot->mot[i];
			carre[i][0]=liste_mot->mot[i];
		}

		//on appel remplir  carre
		remplir_carre(carre,l,1,dico_tab);

		liste_mot=liste_mot->suiv;
	}

	//detruit liste mot
	detruire_Lmot(debut_liste_mot);

	//detruit dico_tab
	detruire_dico(dico_tab);

	//detruit carre
	for(i=0;i<l;i++){
		free(carre[i]);
	}
	free(carre);

}
