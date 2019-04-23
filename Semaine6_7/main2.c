#include "ecosys.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


  /* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float d_proie=1;
float d_predateur=1;
float p_manger=0.2;
float p_reproduce=0.01;
float energie=50;


int main(void) {

  srand(time(NULL));

  
	Animal **liste_proie = malloc(sizeof(Animal *));
	Animal **liste_predateur = malloc(sizeof(Animal *));
	int i=0;
  	srand(time(NULL));
	
	for(i=0;i<NB_PROIES;i++)
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,liste_proie);
 	for(i=0;i<NB_PREDATEURS;i++)	
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,liste_predateur);
	
	while(1){	
		afficher_ecosys(*liste_proie, *liste_predateur);
		rafraichir_proies(liste_proie);
		rafraichir_predateurs(liste_predateur, liste_proie);
		usleep(100000);
		system("clear");
	}

	liberer_liste_animaux(*liste_predateur);
	liberer_liste_animaux(*liste_proie);
	free(liste_predateur);
	free(liste_proie);
	
  return 0;
}

