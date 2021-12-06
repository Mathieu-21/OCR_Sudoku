#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "grayscale.h"
/*
void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
*/
int _cx(int width, int bx);
int _cy(int heigth, int by);
int _bx(int width, int cx);
int _by(int heigth, int cy);
SDL_Surface* rotate(SDL_Surface* img, int angle);


#endif
