
# Makefile de la semaine 2: tri et compilation séparée.
# à compléter

GCC_FLAGS = -Wall -Werror

all: main_triBulle main_triBulleAmeliore utilitaires_tableaux.h tri_bulle.h

utilitaires_tableaux.o	: utilitaires_tableaux.c
	gcc $(GCC_FLAGS) -c utilitaires_tableaux.c

tri_bulle.o	: tri_bulle.c
	gcc $(GCC_FLAGS) -c tri_bulle.c

main_triBulle.o	: main_triBulle.c
	gcc $(GCC_FLAGS) -c main_triBulle.c

main_triBulle	: tri_bulle.o main_triBulle.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o main_triBulle main_triBulle.o tri_bulle.o utilitaires_tableaux.o 

main_triBulleAmeliore.o	: main_triBulleAmeliore.c
	gcc $(GCC_FLAGS) -c main_triBulleAmeliore.c

main_triBulleAmeliore	: tri_bulle.o main_triBulleAmeliore.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o main_triBulleAmeliore main_triBulleAmeliore.o tri_bulle.o \
utilitaires_tableaux.o

clean	:
	rm -f utilitaires_tableaux.o tri_bulle.o main_triBulle.o main_triBulle \
main_triBulleAmeliore.o main_triBulleAmeliore
