#ifndef DRAWSUDOKU_H_
#define DRAWSUDOKU_H_

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "sdl.h"

void numero(SDL_Surface* grille, SDL_Surface* num, int w2, int h2, int a, int b);
SDL_Surface* draw(char* filename, SDL_Surface* grille);

#endif
