
# Makefile de la semaine 2: tri et compilation séparée.
# à compléter

GCC_FLAGS = -Wall -Werror

all: tri_rapide utilitaires_tableaux.h tri_rapide.h

utilitaires_tableaux.o	: utilitaires_tableaux.c
	gcc $(GCC_FLAGS) -c utilitaires_tableaux.c

tri_rapide.o	: tri_rapide.c
	gcc $(GCC_FLAGS) -c tri_rapide.c

tri_rapide	: tri_rapide.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o tri_rapide tri_rapide.o utilitaires_tableaux.o

clean	:
	rm -f tri_rapide tri_rapide.o utilitaires_tableaux.o
