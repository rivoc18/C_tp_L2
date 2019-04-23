#ifndef _JEUX_DE_MOTS_H_
#define _JEUX_DE_MOTS_H_

#include "liste.h"
#include "arbre_lexicographique_tab.h"


Lm_mot *trouver_les_mots(char *lettres, PNoeudTab dico);
void le_mot_le_plus_long(char *lettres, PNoeudTab dico, char *res);
Lm_mot *mots_de_longueur_donnee(char *lettres, PNoeudTab dico, int l);

#endif
