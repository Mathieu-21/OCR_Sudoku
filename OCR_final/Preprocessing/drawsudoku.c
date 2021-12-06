#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "sdl.h"

void numero(SDL_Surface* grille, SDL_Surface* num, int w2, int h2, int a, int b)
{
	for(int k = 0; k < w2; k++)
	{
		for (int l = 0; l < h2; l++)
		{
			Uint32 pixel1 = get_pixel(num, k, l);
			put_pixel(grille, k + a, l + b, pixel1);
		}
	}
}

SDL_Surface* draw(char* filename, SDL_Surface* grille)
{
	SDL_Surface* img1;
	SDL_Surface* img2;
	SDL_Surface* img3;
	SDL_Surface* img4;
	SDL_Surface* img5;
	SDL_Surface* img6;
	SDL_Surface* img7;
	SDL_Surface* img8;
	SDL_Surface* img9;
	
	
	img1 = load_image("../grid/1.jpg");
	img2 = load_image("../grid/2.jpg");
	img3 = load_image("../grid/3.jpg");
	img4 = load_image("../grid/4.jpg");
	img5 = load_image("../grid/5.jpg");
	img6 = load_image("../grid/6.jpg");
	img7 = load_image("../grid/7.jpg");
	img8 = load_image("../grid/8.jpg");
	img9 = load_image("../grid/9.jpg");
	
	
	int width = grille->w;
	int height = grille->h;
	int w2 = 100;
	int h2 = 100;
	
	int ch;
	FILE *f;
	int gridd[83];
	int grid[9*9];
	f = fopen(filename,"r");
	if(f==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		exit(1);
	}

	int i = 0;
	while((ch=fgetc(f))!=EOF)
	{
		if(ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6'
				|| ch == '7' || ch == '8' || ch=='9')
		{
			gridd[i] = ch-48;
			i+=1;
		}
	}
	fclose(f);

	int k = 0;
	for(size_t i = 0; i<9 ; i++)
	{
		for(size_t j = 0; j<9 ; j++)
		{
			grid[i*9 +j] = gridd[k];
			k+=1;
		}
	}

	

	int index = 0;
	
	for (int i = 0; i < width; i += w2)
	{
		for (int j = 0; j < height; j += h2)
		{
			if (grid[index] == 1)
			{
				numero(grille,img1,w2,h2,j,i);
				
			}
			if (grid[index] == 2)
			{
				numero(grille,img2,w2,h2,j,i);
				
			}
			if (grid[index] == 3)
			{
				numero(grille,img3,w2,h2,j,i);
				
			}
			if (grid[index] == 4)
			{
				numero(grille,img4,w2,h2,j,i);
				
			}
			if (grid[index] == 5)
			{
				numero(grille,img5,w2,h2,j,i);
				
			}
			if (grid[index] == 6)
			{
				numero(grille,img6,w2,h2,j,i);
				
			}
			if (grid[index] == 7)
			{
				numero(grille,img7,w2,h2,j,i);
				
			}
			if (grid[index] == 8)
			{
				numero(grille,img8,w2,h2,j,i);
				
			}
			if (grid[index] == 9)
			{
				numero(grille,img9,w2,h2,j,i);
				
			}
			index++;
		}
		return grille;
	}
}
/*
int main()
{
	init_sdl();
	SDL_Surface* grille;
	SDL_Surface* screen_surface;
	grille = load_image("grid.jpg");
	screen_surface = display_image(grille);
	draw("grid_00.result",grille);
	update_surface(screen_surface,grille);
	wait_for_keypressed();
	SDL_FreeSurface(grille);
	SDL_FreeSurface(screen_surface);
}
	



*/




	
	
	
