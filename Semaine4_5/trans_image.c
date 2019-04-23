#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "image.h"
#include "noyau.h"

void quickSort(int tab[], int s, int n)
{
	int p;
	int i;
	int save;

	if (n - s > 1){
		p = s;

		for (i = s + 1; i < n; i++){
			if (tab[i] <= tab[s]){
				p++;
				save = tab[p];
				tab[p] = tab[i];
				tab[i] = save;
			}
		}
		save = tab[s];
		tab[s] = tab[p];
		tab[p] = save;

		quickSort(tab, s, p);
		quickSort(tab,p + 1, n);
	}
}

image_t *negatif(image_t *src)
{
	image_t *res = copier_image(src);
	if (!src || !res) return NULL;
	int i;
	if(res == NULL)
		return NULL;
	//on parcours ttes les valeurs du buffer et on les inverses
	for (i = 0; i < res->h * res->w; i++)
		(res->buff)[i] = 255 - (res->buff)[i];
	return res;
}

image_t *rotation(image_t *src, int angle)
{
	image_t *img = copier_image(src);
	if (!src || !img) return NULL;
	int i;
	int j;
	//on regarde la validité de l'angle (%90)
	if (angle != 90 && angle != 180 && angle != 270)
	{
		printf("Angle invalide");
		return NULL;
	}
	//on regarde si on doit inverser les dimensions de l'image
	if (angle == 90 || angle == 270)
	{
		img->w = src->h;
		img->h = src->w;
	}
	//on parcours les lignes et les colonnes (ATTENTION LE TABLEAU A UNE SEULE DIMENSION)
	for (i = 0; i < src->h; i++){
		for (j = 0; j < src->w; j++){
			if (angle == 90)
				VAL(img, src->w-j-1,i) = VAL(src, i, j);
			if (angle == 180)
				VAL(img, src->h-i-1,j) = VAL(src, i, j);
			if (angle == 270)
				VAL(img, j, src->h-1-i) = VAL(src, i, j);
		}
	}
	return img;
}

image_t *modifier_lumin(image_t *src, int pourcent)
{
	image_t *img = copier_image(src);
	if (!src || !img) return NULL;
	int color;
	int i;
	//on parcours le buffer et affecte le pourcentage a chaque pixel
	for (i = 0; i < img->h * img->w; i++){
		color = src->buff[i]*pourcent/100;
		if (color < 0)
			color = 0;
		if (color > 255)
			color = 255;
		(img->buff)[i] = color;
	}
	return img;
}

image_t *bruiter_image(image_t *src, int pourcent)
{
	image_t *res = copier_image(src);
	if (!src || !res) return NULL;
	srand(time(NULL));
	int i;
	for (i = 0; i < src->w * src->h; i++){
		if (rand()%100 < pourcent)
			(res->buff)[i] = rand()%256;
	}
	return res;
}

image_t *filtrer_median(image_t *src)
{
	int r = 5;
	int tab[r*r-4];
	int i,j;//coord pixels
	int i2,j2;//coord coeffs
	int i3,j3;//coord pixels voisins
	image_t *res=copier_image(src);
	if(res == NULL)
		return NULL;
		
	for(i=0; i<res->h;i++){
		for(j=0;j<res->w;j++){
			
			for(i2=0; i2<r;i2++){
				for(j2=0; j2<r;j2++){
					if(!((i2==0 && j2==0) || (i2==0 && j2==r-1) || (i2==r-1 && j2==0) || (i2==r-1 && j2 ==r-1))){
						i3=i+i2-(r/2);
						j3=j+j2-(r/2);
					
						// cas depassement d'indice
						if(i3<0)
							i3=0;
						if(i3>=res->h)
							i3=res->h-1;
						if(j3<0)
							j3=0;
						if(j3>=res->w)
							j3=res->w-1;
						
						tab[i2*r+j2]=VAL(src,i3,j3);
					}
				}
			}
			quickSort(tab, 0, r*r-4);
			
			VAL(res,i,j)=tab[(r*r-4)/2];
		}
	}
	return res;
}

image_t *convoluer(image_t *src, noyau_t *pn)
{
	int somme=0;//somme des coeffs pour normaliser
	int calcul;//le calcul du nouveau pixel
	image_t *res;
	int i,j;//coord pixels
	int i2,j2;//coord coeffs
	int i3,j3;//coord pixels voisins 
	
	//on fait la copie qu'on modifiera
	res = copier_image(src);
	if(res == NULL)
		return NULL;
	
	//somme des elements
	for(i=0;i<pn->dim*pn->dim;i++){
		somme+=*(pn->coeffs+i);
	}
	//cas particulier somme nulle 
	if(somme==0)
		somme=1;
	
	//on parcours tous les pixels de l'image
	for(i=0; i<res->h;i++){
		for(j=0;j<res->w;j++){
			calcul=0;
			//pour chaques pixels on regarde chaque pixel autour selon le noyau 
			for(i2=0; i2<pn->dim;i2++){
				for(j2=0; j2<pn->dim;j2++){
					i3=i+i2-((pn->dim)/2);
					j3=j+j2-((pn->dim)/2);
					
					// cas depassement d'indice
					if(i3<0)
						i3=0;
					if(i3>=res->h)
						i3=res->h-1;
					if(j3<0)
						j3=0;
					if(j3>=res->w)
						j3=res->w-1;
						
					//calcul du nouveau
					calcul += pn->coeffs[ i2*(pn->dim) + j2] * VAL(src,i3,j3);
					
				}
			}
			//on normalise
			calcul = (unsigned int)(calcul * (1.0/somme));
			//cas particulier
			if(calcul <0)
				calcul=-calcul;
				
			//on change la valeur de l'image res
			VAL(res,i,j)=calcul;
		}
	}
	return res;
}







































/*
//ROTATION FONCTIONNELLE EN RECURSIVE
image_t *rotation(image_t *src, int angle)
{
	image_t *img = copier_image(src);
	int i;
	int j;

	if (angle == 0)
		return src;

	if (angle != 90 && angle != 180 && angle != 270){
		printf("Angle invalide");
		return NULL;
	}
	img->w = src->h;
	img->h = src->w;
	for (i = 0; i < src->h; i++){ //peut etre inverser les condition d'arrets??????????????
		for (j = 0; j < src->w; j++){
			VAL(img, src->w-j-1,i) = VAL(src, i, j);
		}
	}
	rotation(img, angle - 90);
}

//ROTATION FONCTIONNELLE AVEC QUE DES ROTATIONS DE 90
image_t *rotation(image_t *src, int angle)
{
	image_t *img = copier_image(src);
	int i;
	int j;
	int nb;

	if (angle != 90 && angle != 180 && angle != 270){
		printf("Angle invalide");
		return NULL;
	}
	for (nb = 0; nb < angle / 90; nb++){
		img->w = src->h;
		img->h = src->w;
		for (i = 0; i < src->h; i++){
			for (j = 0; j < src->w; j++){
				VAL(img, src->w-j-1,i) = VAL(src, i, j);
			}
		}
		src = copier_image(img);
	}
	return img;
}


image_t *convoluer(image_t *src, noyau_t *pn)
{
	image_t *img = copier_image(src);
	if (!src || !pn || !img) return NULL;
	int i, j;
	int startPixel, pixel;
	int res;
	int somme = 0;
	
	for (i = 0; i < pn->dim*pn->dim; i++)
		somme += (pn->coeffs)[i];

	//on parcours tous les pixels de l'image
	for (i = 0; i < src->w * src->h; i++){
		//on recupere le pixel de depart auquel appliquer la convolution de i
		startPixel = i - (pn->dim/2 * img->w) - pn->dim/2;
		res = 0;
		//on parcours la matrice de convolution pour faire j calculs
		for (j = 0; j < pn->dim * pn->dim; j++){
			//on trouve la position du pixel que l'on va utiliser en fonction de la largeur...
			pixel = startPixel + ((j % pn->dim) * src->w) + (j % pn->dim);
			//les pixels dépassant de l'image sont considérés comme des 0
			if (pixel < 0 || pixel > src->w * src->h)
				res += 0;
			else
				res += (src->buff)[pixel] * (pn->coeffs)[j];
		}
		if (somme != 0)
			res *= (1.0/somme);
			
		if (res < 0)
			res = -res;

		if (res <= 255 && res >= 0)
			(img->buff)[i] = res;
	}
	return img;
}


image_t *filtrer_median(image_t *src)
{
	image_t *img = copier_image(src);
	if (!src || !img) return NULL;

	int i, j, nbVal;
	int pixel, pixelStart;
	int tab[21];

	for (i = 0; i < src->w * src->h; i++){
		pixelStart = i - 2*src->w - 2;
		nbVal = 0;
		for (j = 0; j < 25; j++){
			pixel = pixelStart + ((j % 5)*src->w) + (j % 5);
			if (pixel > 0 && pixel < (src->w * src->h) && j != 0 && j != 4 && j != 20 && j != 24){
				tab[nbVal] = (src->buff)[pixel];
				nbVal++;
			}
		}
		quickSort(tab, 0, nbVal);
		(img->buff)[i] = tab[nbVal/2];
	}
	return img;
}
*/
