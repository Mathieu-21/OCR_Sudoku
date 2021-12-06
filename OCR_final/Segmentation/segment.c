#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include "hough.h"
#include <gtk/gtk.h> 
int segment(int *mat, size_t width, size_t height)
{
  int matr[width * height];

  for (int p = 0; p < width * height; p++)
    {
      matr[p] = *(mat + p);
    }
  
  char res[81];

  // Creation off the hough accumulator

  float max_dist = sqrt((float) ((int) width * (int) width + (int) height * (int) height));

  int houg[180 * (size_t) max_dist];

  for (size_t p = 0; p < 180 * (size_t) max_dist; p++)
    houg[p] = 0;

  hough(matr, houg, width, height, 180);
  g_print("hough good ");

  // Find the 10 horizontal lines in the grid
  
  size_t rho_hori[10];
  size_t teta_hori[10];

  size_t r = 0;
  int i = 0;

  while (r < (size_t) max_dist && i < 10)
    {
      int found = 0;
      
      for (size_t teta = 45; teta < 135; teta++)
	{
	   if (houg[r*180 + teta] >= 300 && found == 0)
	      {
		rho_hori[i] = r;
		teta_hori[i] = teta;
		i++;
      	        r += 10;
         	found = 1;
	      }
	}
      r++;
    }
  g_print("ligne good ");

  // Find the cross points between the lines of the grid
  
  size_t x_inter[100];
  size_t y_inter[100];

  size_t in = 0;

  for (size_t line = 0; line < 10; line++)
    {
      size_t x = 0;

      while(x < width && in < 101)
	{
	  double rad = (double) (teta_hori[line] - 90) * M_PI / 180;
	  size_t y = (size_t)(((double) rho_hori[line] - ((double) x * cos(rad))) / sin(rad));

	  if (matr[y * width + x] == 0)
	    {
	      size_t teta = 45;
	      while (teta <= 135)
		{
		  size_t rho = (size_t) ((double) x * cos(rad) + (double) y * sin(rad));

		  if (houg[rho * 180 + teta] > 300)
		    {
		      x_inter[in] = x;
		      y_inter[in] = y;
		      teta = 145;
		      in++;
		      x += 10;
		    }
		  
		  teta++;
		}
	    }
	  
	  x++;
	}
    }

  // Cuts the cases of the grid and passes them trough the neural network

  i = 0;
  int j = 0;

  while (i < 90)
    {
      size_t bound_x = x_inter[i + 11] - x_inter[i];
      size_t bound_y = y_inter[i + 11] - y_inter[i];

      int ch[bound_x * bound_y];

      cut(matr, ch, x_inter[i], y_inter[i], x_inter[i+11], y_inter[i+11], width);

      if (test_cas(ch, bound_x, bound_y) == 1)
	{
	  res[j] = '.';
	}
      else
	{
	  res[j] = '0';
	}

      i++;
      j++;

      if(i % 10 == 0)
	i++;
    }

  // Saves the results in a .txt file
  
  FILE *out = fopen("sudoku.txt","w");
  fputs(res, out);
  fclose(out);
  
  return 0;
}

