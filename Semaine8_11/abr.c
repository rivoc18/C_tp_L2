#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "abr.h"

/* decoupe liste */
Lm_mot *part_Lmot(Lm_mot **pl)
{
  int nbm = taille_Lmot(*pl);
  Lm_mot *p = *pl;
  Lm_mot *pivot;

  if (nbm < 3)
    {
      *pl = NULL;
      return p;
    }

  nbm /= 2;
  for(p = *pl; nbm-- > 1; p = p->suiv);

  pivot = p->suiv;
  p->suiv = NULL;

  return pivot;
}

/* Creation de l ABR, destruction de la liste*/
Nd_mot *Lm2abr(Lm_mot *l)
{
  	Nd_mot *nd;
	Lm_mot *pivot;
  	nd=malloc(sizeof(Nd_mot));
  	
  	if (l == NULL)
  		return NULL;
  	
  	pivot = part_Lmot(&l);
  	nd->mot=pivot->mot;
  	nd->g=Lm2abr(l);
  	nd->d=Lm2abr(pivot->suiv);
  	free(pivot);
  	
  	return nd;
}


/* destruction de l ABR donnee en argument */
void detruire_abr_mot(Nd_mot *abr)
{
	Nd_mot *nd = abr;
	if (nd != NULL){
		detruire_abr_mot(nd->g);
		detruire_abr_mot(nd->d);
		free(nd->mot);
		free(nd);
	}
}


/* Recherche d'un mot dans ABR */
Nd_mot *chercher_Nd_mot(Nd_mot *abr, const char *mot)
{
	if (abr == NULL)
		return NULL;
	
	if (strcmp(abr->mot, mot) < 0)
		return chercher_Nd_mot(abr->d, mot);
	if (strcmp(abr->mot, mot) > 0)
		return chercher_Nd_mot(abr->g, mot);
	
	return abr;
}
