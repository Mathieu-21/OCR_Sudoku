#include <stdio.h>
#include "sudoku_solver.h"

int main(int argc, char *argv[]){
	FILE* fichier = NULL;

	fichier = fopen("grid.txt", "r+");
	char chaine[TAILLE_MAX] = "";

	if(fichier!=NULL){
		//On peut lire et écrire dans le fichier
		fgets(str, TAILLE_MAX, fichier); //On lit les caractères du fichier que l'on stock dans chaine
		printf("%s",chaine); //On affiche la chaine
	}
	else{
		//On affiche un message d'erreur si on veut
		printf("Impossible d'ouvrir le fichier test.txt");
	}

	return 0;
}
