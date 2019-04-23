#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "image.h"
#define TMP_STR_SIZE 256

image_t *charger_image_pgm(char *nom_fichier)
{
	FILE *f;
	image_t *img;
	unsigned int nb_niveaux_gris;
	char ligne_lue[TMP_STR_SIZE];
	enum format {BIN, ASCII} pgm_form;
	//On ouvre le fichier
	if ((f = fopen(nom_fichier, "r")) == NULL){
		printf("ouverture du fichier impossible\n");
		return NULL;
	}
	//on regarde le format
	char *format = fgets(ligne_lue, TMP_STR_SIZE, f);
	if (strcmp(format, "P2\n") == 0)
		pgm_form = ASCII;
	else if (strcmp(format, "P5\n") == 0)
			pgm_form = BIN;
	else {
		fprintf(stderr, "MAUVAIS FORMAT\n");
		return NULL;
	}
	img = creer_image();
	img->path = strdup(nom_fichier);
	//on parcours les commentaires et on les ignores
	do{
		fgets(ligne_lue, TMP_STR_SIZE,f);
	}while(ligne_lue[0]=='#');
	//on recupere hauteur et largeur
	sscanf(ligne_lue,"%lu %lu",&(img->w), &(img->h));
	//on prend le niveau de gris
	nb_niveaux_gris = atoi(fgets(ligne_lue, TMP_STR_SIZE, f));
	if(nb_niveaux_gris >= 256){
		printf("erreur niveau de gris >= 256");
		return NULL;
	}
	//on parcours toutes les lignes et on ajoutes les valeurs au buffer (que l'on malloc)
	img->buff = (unsigned char*) malloc(img->w*img->h * sizeof(unsigned char));
	int i=0;
	if (pgm_form == ASCII){
		while(i < img->w * img->h){
			fscanf(f, " %hhu ", (img->buff) + i);
			i++;
		}
	}
	if (pgm_form == BIN)
		fread(img->buff, sizeof(unsigned char), img->w * img->h, f);

	fclose(f);
	return (img);
}

int sauver_image_pgm(char *nom_fichier, image_t *img)
{
	if (img == NULL)
		return (-1);
	FILE *f = fopen(nom_fichier, "w");
	if (f == NULL){
		printf("ouverture du fichier impossible\n");
		return (-1);
	}
	//on ecrit ligne par ligne l entete
	fprintf(f, "P2\n");
	fprintf(f, "#%s\n", img->path);
	fprintf(f, "%lu %lu\n", img->w, img->h);
	fprintf(f, "255\n");
	//on ecrit tout le buffer
	int i = 0;
	while (i < img->h * img->w){
		fprintf(f, "%hhu\n", (img->buff)[i] );
		i++;
	}
	fclose(f);
	return (1);
}
