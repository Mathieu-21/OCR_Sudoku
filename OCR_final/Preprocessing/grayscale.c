#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "grayscale.h"

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

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void SDL_FreeSurface(SDL_Surface *surface);

SDL_Surface* grayscale(SDL_Surface* image_surface, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Uint32 pixel1 = get_pixel(image_surface, j, i);
			Uint8 r, g, b;
			SDL_GetRGB(pixel1, image_surface->format, &r, &g, &b);
			int moy = 0.2126*r + 0.7152*g + 0.0722*b;
			r = moy;
			g = moy;
			b = moy;
			Uint32 pixel2 = SDL_MapRGB(image_surface->format, r, g, b);
			put_pixel(image_surface, j, i, pixel2);
		}
	}
	return image_surface;
}	
				
void mat(SDL_Surface* image_surface, int height, int width, int* matrix)
{
	int neww = width/32;
	int newh = height/32;
	int c1 = 0;
	int c2 = 0;
	int moytotal = 0;
	for (int w = 0; w < height - newh; w+=newh)
	{
		for (int x = 0; x < width - neww; x+=neww)
		{

			for (int y = 0; y < newh; y++)
			{
				for (int z = 0; z < neww; z++)
				{

					Uint32 pixel9 = get_pixel(image_surface, z+x, y+w);
					Uint8 r3, g3, b3;
					SDL_GetRGB(pixel9, image_surface->format, &r3, &g3, &b3);
					int moy = 0.2126*r3 + 0.7152*g3 + 0.0722*b3;
					moytotal += moy;
				}
			}
			moytotal = moytotal/(newh * neww);
			matrix[c2 * 32 + c1] = moytotal;  
			moytotal = 0;
			c1++;
		}
		c2++;
	}
	
}

unsigned long moyenne(SDL_Surface* image_surface, int height, int width)
{
	unsigned long sum = 0;
	for (int i = 0; i < height - 1; i++)
	{
		for (int j = 0; j < width - 1; j++)
		{
			Uint32 pixel1 = get_pixel(image_surface, j, i);
			Uint8 r, g, b;
			SDL_GetRGB(pixel1, image_surface->format, &r, &g, &b);
			int moy = 0.2126*r + 0.7152*g + 0.0722*b;
			sum += moy;
		}
	}
	unsigned long moyenne = sum / (width*height);
	return moyenne;
}
			
/*void binarization(SDL_Surface* image_surface, SDL_Surface* image2, int height, int width, int* matrix, int threshold)
{
	int neww = width/32;
	int newh = height/32;
	int c3 = 0;
	int c4 = 0;
	for (int a = 0; a < height - newh; a+=newh)
	{
		for (int b = 0; b < width - neww; b+=neww)
		{

			for (int k = 0; k < newh; k++)
			{
				for (int l = 0; l < neww; l++)
				{
					Uint32 pixel3 = get_pixel(image_surface, l+b, k+a);
					Uint8 r2, g2, b2;
					SDL_GetRGB(pixel3, image_surface->format, &r2, &g2, &b2);
					int moy2 = 0.2126*r2 + 0.7152*g2 + 0.0722*b2;
					if (moy2 < matrix[c4 * 32 + c3] - threshold)
					{
						Uint32 pixel4 = SDL_MapRGB(image_surface->format,255,255,255);
						put_pixel(image2, l+b, k+a, pixel4);
					}
					else
					{
						Uint32 pixel4 = SDL_MapRGB(image_surface->format,0,0,0);
						put_pixel(image2,l+b,k+a, pixel4);
					}
				}
			}
			c3++;
		}
		c4++;
	}
	
}*/

void mat01(SDL_Surface* image_surface,int* mat)
{
	int height = image_surface->h;
	int width = image_surface->w;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Uint32 pix = get_pixel(image_surface, j, i);
			Uint8 red, green, blue;
			SDL_GetRGB(pix, image_surface->format, &red, &green, &blue);
			if (red == 0 && green == 0 && blue == 0)
			{
				mat[i * width + j] = 1;
			}
			else
			{
				mat[i * width + j] = 0;
			}
		}
	}
}

void threshold(SDL_Surface* image_surface, SDL_Surface* image2, int height, int width, int t)
{
	int wh = width * height;
	int s = width/32;
	unsigned long * pointer = (unsigned long *) calloc(wh,sizeof(unsigned long));
	for (int i = 0; i < width;i++)
	{
		unsigned long sum = 0;
		for (int j = 0; j < height;j++)
		{
			Uint32 pixel = get_pixel(image_surface, i, j);
			Uint8 moy;
			SDL_GetRGB(pixel, image_surface->format, &moy, &moy, &moy);
			sum += moy;
			if (i == 0)
			{
				pointer[j * width + i] = sum;
			}
			else
			{
				pointer[j * width + i] = pointer[(j) * width +i-1] + sum;
			}
		}
	}
	for (int k = 0; k < width;k++)
	{
		for (int l = 0; l < height; l++)
		{
			int x1 = k - s/2;
			int x2 = k + s/2;
			int y1 = l - s/2;
			int y2 = l + s/2;
			if(x1 <= 0)
			{
				x1 = 1;
			}
			if(x2 >= width)
			{
				x2 = width -1;
			}
			if (y1 <= 0)
			{
				y1 = 1;
			}
			if (y2 >= height)
			{
				y2 = height-1;
			}
			unsigned long count = (x2 - x1) * (y2 - y1);
			unsigned long sum1 = pointer[y2 * width + x2] - pointer[(y1-1) * width + x2] - pointer[(y2) * width + x1-1] + pointer[(y1 - 1) * width + x1-1];
			Uint32 pixel2 = get_pixel(image_surface, k, l);
			Uint8 moy2;
			SDL_GetRGB(pixel2, image_surface->format, &moy2, &moy2, &moy2);
			if(((unsigned long)(moy2 * count)) <= (double)(sum1 * (100 - t)/100))
			{
				Uint32 pixel4 = SDL_MapRGB(image_surface->format,255,255,255);
				put_pixel(image2, k, l, pixel4);
			}
			else
			{
				Uint32 pixel4 = SDL_MapRGB(image_surface->format,0,0,0);
				put_pixel(image2,k,l, pixel4);
			}
		}
	}
	free(pointer);
}

SDL_Surface* image(SDL_Surface* image_surface,SDL_Surface* image2)
{

    init_sdl();

    int width = image_surface->w;
    int height = image_surface->h;
    //SDL_Surface* image2;
    //SDL_Surface* image3;
    //SDL_Surface* image4;
    //image2 = image_surface;
    //image3 = image_surface;

    image_surface = grayscale(image_surface,height,width);
    //image4 = image_surface;
	
	threshold(image_surface,image2,height,width,60);
	unsigned long moyenne1 = moyenne(image2, height, width);

	if (moyenne1 < 10)
	{
		threshold(image_surface,image2, height, width,15);
	}

    /*int mat[height * width];
    mat01(image2,mat);
    
    for (int i =0; i < height; i++)
    {
	    for (int j = 0; j < width; j++)
	    {
		    printf("%i",mat[i * width + j]);
	    }
	    printf("\n");
    }*/
	return image2;
}

/*int main()
{
	SDL_Surface* image_surface;
	SDL_Surface* image2;
	SDL_Surface* screen_surface;
	init_sdl();
	image_surface = load_image("my_image.jpg");
	image2 = load_image("my_image.jpg");
	screen_surface = display_image(image_surface);
	image_surface = image(image_surface,image2);
	update_surface(screen_surface,image_surface);
	wait_for_keypressed();
	SDL_FreeSurface(image_surface);
	SDL_FreeSurface(screen_surface);
}
*/

int* matrice01(char* filename)
{
	SDL_Surface* image_surface;
	SDL_Surface* image2;
	init_sdl();
	image_surface = load_image(filename);
	image2 = load_image(filename);
	image_surface = image(image_surface,image2);
	int height = image_surface->h;
	int width = image_surface->w;
	int mat[height * width];
	mat01(image_surface,mat);
	return mat;

}









