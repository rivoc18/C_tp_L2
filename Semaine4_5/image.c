#include<stdlib.h>
#include<string.h>
#include "image.h"

image_t *creer_image()
{
	image_t *img;
	img = (image_t *)malloc(sizeof(image_t));
	if (img == NULL)
		return NULL;
	img->w = 0;
	img->h = 0;
	img->path = NULL;
	img->buff = NULL;
	return img;
}

image_t *copier_image(image_t *src)
{
	if (src == NULL)
		return NULL;
	image_t *cpy = creer_image();
	if (cpy == NULL)
		return NULL;
	cpy->w = src->w;
	cpy->h = src->h;
	cpy->path = strdup(src->path);
	cpy->buff = (unsigned char*) malloc(cpy->w*cpy->h*sizeof(unsigned char));
	memcpy(cpy->buff, src->buff, cpy->w*cpy->h*sizeof(unsigned char));
	return cpy;
}

void detruire_image(image_t *p)
{
	if (p==NULL)
		return ;
	free(p->path);
	free(p->buff);
	free(p);
}
