#include <stdio.h>
#include <stdlib.h>
#include "sudoku_solver.h"

char m[81];

void read_text(){
	char ch;
	char grid[83];
	FILE *f;
	f = fopen("grid.txt","r");
	if(f==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		exit(1);
	}
	
	int i = 0;
	while((ch=fgetc(f))!=EOF){
		if((int)ch>=48 && (int)ch<=57){
			grid[i] = ch;
            printf("%c \n",grid[i]);
			i+=1;
		}
	}
	fclose(f);
    int k = 0;
	for(size_t i = 0; i<9 ; i++){
		for(size_t j = 0; j<9 ; j++){
			m[i*9+j] = grid[k];
            printf("%c \n",m[i*9+j]);
			k+=1;
		}
	}
}



void print_matrix(){
	for(size_t i = 0 ; i<9 ; i++){
        for(size_t j = 0 ; j<9 ; j++){
           printf("%c",m[i*9+j]); 
        }
        printf("\n");
    }
}


int main(){
	read_text();
    print_matrix();
}


