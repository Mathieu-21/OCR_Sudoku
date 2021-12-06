#ifndef GRAYSCALE_H_
#define GRAYSCALE_H_

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void SDL_FreeSurface(SDL_Surface *surface);
SDL_Surface* grayscale(SDL_Surface* image_surface, int height, int width);
void mat(SDL_Surface* image_surface, int height, int width, int* matrix);
unsigned long moyenne(SDL_Surface* image_surface, int height, int width);
void threshold(SDL_Surface* image_surface, SDL_Surface* image2, int height, int width, int threshold);
void mat01(SDL_Surface* image_surface, int* mat);
SDL_Surface* image(SDL_Surface* image_surface,SDL_Surface* image2);
int* matrice01(char* filename);

#endif
