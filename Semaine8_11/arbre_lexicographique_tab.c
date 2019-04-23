#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "arbre_lexicographique_tab.h"


PNoeudTab creer_noeud(char lettre) {
  int i;
  
  PNoeudTab res = (PNoeudTab)malloc(sizeof(NoeudTab) * 1);
  if(res == NULL) return NULL;
  res->lettre = lettre;
  res->fin_de_mot = non_fin;
  for(i=0;i<26;i++){
  	res->fils[i]=NULL;
  }
  return res;
}

PNoeudTab ajouter_mot(PNoeudTab racine, char *mot) {
	
	if(strlen(mot) == 0)
		return racine;

	if(racine==NULL)
		racine = creer_noeud('.');
	
	PNoeudTab current = racine;
	int i = 0;
	
	while(mot[i] != '\0'){
		if(current->fils[mot[i] - 'a'] == NULL){
			current->fils[mot[i] - 'a'] = creer_noeud(mot[i]); 
		}
		current = current->fils[mot[i] - 'a'];
		i++;
	}
	current->fin_de_mot = fin;
	return racine;
}

void afficher_mots(PNoeudTab n, char mot_en_cours[LONGUEUR_MAX_MOT], int index) {
  if (n==NULL)
    return;

  if(n->fin_de_mot==fin) {
    mot_en_cours[index]='\0';
    printf("%s\n",mot_en_cours);
  }

  int i;
  for(i=0;i<26;i++) {
    // On affiche les fils
    if (n->fils[i]!=NULL) {
      mot_en_cours[index] = n->fils[i]->lettre;
      afficher_mots(n->fils[i],mot_en_cours,index+1);
    }
  }
}

void afficher_dico(PNoeudTab racine) {
	char mot[LONGUEUR_MAX_MOT];
	afficher_mots(racine,mot,0);
}

void detruire_dico(PNoeudTab dico) {
	if (dico == NULL)
		return ;
	int i;
	for(i = 0; i<26; i++){
		detruire_dico(dico->fils[i]);
	}
	free(dico);
}

int rechercher_mot(PNoeudTab dico, char *mot) {
	if(dico ==NULL)
		return 0;
	if(strlen(mot)==0)
		return 0;
	if(dico->lettre == '.')
		return rechercher_mot(dico->fils[mot[0]-'a'],mot);
	if(strlen(mot)==1)
		return dico->lettre == mot[0] && dico->fin_de_mot==fin;
	if(dico->lettre == mot[0])
		return rechercher_mot(dico->fils[mot[1]-'a'],mot+1);
	return 0;
}

PNoeudTab lire_dico(const char *nom_fichier) {
	
	FILE *f = fopen(nom_fichier, "r");  
	if (f == NULL) return NULL;
	
	PNoeudTab dico = creer_noeud('.');
	
	char ligne_lue[LONGUEUR_MAX_MOT];
	while(fgets(ligne_lue,LONGUEUR_MAX_MOT,f)){
		ligne_lue[strlen(ligne_lue)-1]='\0';
		ajouter_mot(dico, ligne_lue);
	}
	
	fclose(f);
	
	return dico;
}

Lm_mot *tous_les_mots_longueur_donnee_rec(PNoeudTab n, char mot_en_cours[LONGUEUR_MAX_MOT], 
                                                 int index, int l, Lm_mot *res) {
	int i;
	if(n==NULL)
		return res;
	if(n->lettre!='.')
		mot_en_cours[index++] = n->lettre;
	if(n->fin_de_mot==fin){
		mot_en_cours[index]='\0';
		if(strlen(mot_en_cours)==l)
			res=ajouter_Lmot(res,mot_en_cours);
	}
	for(i=0;i<26;i++){
		res=tous_les_mots_longueur_donnee_rec(n->fils[i],mot_en_cours,index,l,res);
	}
	return res;
}

Lm_mot *tous_les_mots_longueur_donnee(PNoeudTab racine, const char* prefixe, int l) {
	int i=0;
	char mot_en_cours[LONGUEUR_MAX_MOT];
	strcpy(mot_en_cours,prefixe);
	while(prefixe[i]!='\0' && racine != NULL){
		racine=racine->fils[prefixe[i]-'a'];
		i++;
	}
	return tous_les_mots_longueur_donnee_rec(racine,mot_en_cours,i-1,l,NULL);
}

Lm_mot *mots_commencant_par(const char *mot_a_completer, PNoeudTab dico) {
	Lm_mot *res=NULL;
	
	/*int i;
	if(n==NULL)
		return res;
	if(n->lettre!='.')
		mot_en_cours[index ++] = n->lettre;
	if(n->fin_de_mot==fin){
		mot_en_cours[index]='\0';
		ajouter_Lm_mot(res,mot_en_cours);
	}
	for(i=0;i<26;i++){
		tous_les_mots_longueur_donnee_rec(n->fils[i],mot_en_cours,index,l,res);
	}
	return res;*/

	return res;
}
