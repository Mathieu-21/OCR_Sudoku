#ifndef SDL_H_
#define SDL_H_

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

#endif
