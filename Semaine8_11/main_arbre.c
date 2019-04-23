#include <stdio.h>
#include "arbre_lexicographique.h"

int main() {
  PNoeud l=lire_dico("../Fournis/french_za");
  char mot1[]="abcde";
  char mot2[]="marin";
  int i;
  for (i=0;i<10000;i++) {
    rechercher_mot(l,mot1);
    rechercher_mot(l,mot2);
  }
  return 0;
}
