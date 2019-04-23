
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ecosys.h"

/* Pour utiliser la correction automatique:
   cavecorrector 6-7 repertoire
 */

void liberer_liste_animaux(Animal *liste){
	Animal *np = liste;
	if (!liste) return;
	assert(!liste->precedent);
	do {
		np = liste->suivant;
		free(liste);
		liste = np;
	} while (liste);
}

Animal *creer_animal(int x, int y, float energie) {
	Animal *new = (Animal *)malloc(sizeof(Animal));
	assert(new);
	new->x = x;
	new->y = y;
	new->dir[0] = (-1) + rand() % 3;
	new->dir[1] = (-1) + rand() % 3;
	new->energie = energie;
	new->precedent = NULL;
	new->suivant = NULL;
	return new;
} 

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {

	animal->suivant = liste;
	animal->precedent = NULL;
	if (liste)
		liste->precedent = animal;
	return animal;
}

void ajouter_animal(int x, int y, Animal **liste_animal) {
	if( !(x<0 || y<0 || x>=SIZE_X || y>=SIZE_Y)){
		Animal *new = creer_animal(x, y, energie);
		*liste_animal = ajouter_en_tete_animal(*liste_animal,new);
	}
}


void enlever_animal(Animal **liste, Animal *animal) {

	if(animal->suivant != NULL)
		animal->suivant->precedent = animal->precedent;
	if(animal->precedent != NULL)
		animal->precedent->suivant = animal->suivant;
	if(*liste==animal)
		*liste= animal->suivant;
	free(animal);
}

unsigned int compte_animal_rec(Animal *la) {
	if(la==NULL){
		return 0;
	}
	return 1+compte_animal_rec(la->suivant);
}

unsigned int compte_animal_it(Animal *la) {
	unsigned int n= 0;
	Animal *current = la;
	while(current){
		n++;
		current = current->suivant;
	}
	return n;
}

void bouger_animaux(Animal *la) {
	Animal *current;
	for (current = la; current != NULL; current = current->suivant){
		current->x = (current->x + current->dir[0]) % SIZE_X;
		current->y = (current->y + current->dir[1]) % SIZE_Y;
		
		if (rand()*1.0 / RAND_MAX <= p_ch_dir){
			current->dir[0] = (-1) + rand() % 3;
			current->dir[1] = (-1) + rand() % 3;
		}
	}
}

void reproduce(Animal **liste_animal) {
	
	Animal *current;
	
	for (current = *liste_animal; current != NULL; current = current->suivant){
		if(rand()*1.0/RAND_MAX <= p_reproduce)
			ajouter_animal(current->x,current->y,liste_animal);
	}
}

void rafraichir_proies(Animal **liste_proie) {
	bouger_animaux(*liste_proie);
	Animal *current;
	Animal *cp;
	for (current = *liste_proie; current != NULL;){
		current->energie -= d_proie;
		if (current->energie <= 0){
			cp = current->suivant;
			enlever_animal(liste_proie,current);
			current = cp;
		}
		else
			current = current->suivant;
	}
	reproduce(liste_proie);
}

Animal *animal_en_XY(Animal *l, int x, int y) {
	Animal *current = l;
	while (current){
		if(current->x == x && current->y == y){
			return current;
		}
		current = current->suivant;
	}
	return NULL;
} 

void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
	bouger_animaux(*liste_predateur);
	Animal *current;
	Animal *proie;
	Animal *cp;
	for (current = *liste_predateur; current != NULL;){
		if (((proie = animal_en_XY(*liste_proie, current->x, current->y))!=NULL) && (rand()*1.0 / RAND_MAX <= p_manger)){
			enlever_animal(liste_proie,proie);
		}
		current->energie -= d_predateur;
		if (current->energie <= 0){
			cp = current->suivant;
			enlever_animal(liste_predateur,current);
			current = cp;
		}
		else
			current = current->suivant;
	}
	reproduce(liste_predateur);

}

void afficher_ecosys(Animal *liste_proie,Animal *liste_predateur) {
	int x,y;
	int boolPredator, boolProie;
	Animal *current;
	for(x=0;x<SIZE_X;x++){
		for(y=0;y<SIZE_Y;y++){
			boolPredator =0;
			boolProie =0;
			current = liste_proie;
			while(current){
				if(current->x==x && current->y==y){
					boolProie=1;
					break;
				}
				current = current->suivant;
			}
			current = liste_predateur;
			while(current){
				if(current->x==x && current->y==y){
					boolPredator=1;
					break;
				}
				current = current->suivant;
			}
			if (boolProie && boolPredator)	printf("@");
			else if (boolProie && !boolPredator)	printf("*");
			else if (!boolProie && boolPredator)	printf("O");
			else printf(" ");
		}
		printf("\n");
	}
}

void clear_screen() {
	printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}
