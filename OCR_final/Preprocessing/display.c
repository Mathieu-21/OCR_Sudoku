#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "grayscale.h"
#include "display.h"

/*
void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}


void SDL_FreeSurface(SDL_Surface *surface);

*/
int _cx(int width, int bx)
{
	return(bx - width/2);
}

int _cy(int heigth, int by)
{
	return(-by + heigth/2);
}

int _bx(int width, int cx)
{
	return(cx + width/2);
}

int _by(int heigth, int cy)
{
	return(-cy + heigth/2);
}

SDL_Surface* rotate(SDL_Surface* img, int angle)
{
	int h = img->w;
	int w = img->h;
	double pi = 3.14159265;
	double rad = (angle * pi) / 180;
	double c = cos(rad);
	double s = sin(rad);
	int w2 = w * c + h * s;
	int h2 = w * s + h * c;
	SDL_Surface* new_image = SDL_CreateRGBSurface(0,h2, w2,32,0,0,0,0);

	if (angle > 90)
	{
		rotate(rotate(img,90),angle - 90);
	}
	for (int bxp = 0; bxp < w2; bxp++)
	{
		for(int byp = 0; byp < h2; byp++)
		{
		int cxp = _cx(w2,bxp);
			int cyp = _cy(h2,byp);
			int cx = cxp * c - cyp * s;
			int cy = cxp * s + cyp * c;
			int bx = _bx(w,cx);
			int by = _by(h,cy);
			if (bx >= 0 && bx < w && by >= 0 && by < h)
			{
				Uint32 p = get_pixel(img,by,bx);
				put_pixel(new_image,byp,bxp,p);
			}
		}
	}
	return new_image;
}
