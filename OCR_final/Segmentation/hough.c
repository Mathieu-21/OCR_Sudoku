#include <stddef.h>
#include <math.h>

//Creation de l'accumulateur de hough

void hough(int mat[], int houg[], size_t matcolls, size_t matlines, size_t hougcolls)
{
  for (size_t y = 0; y < matlines; y++)
    {
      for (size_t x = 0; x < matcolls; x++)
	{
	  if (mat[y * matcolls + x] == 0)
	    {
	      for (size_t teta = 0; teta < hougcolls; teta++)
		{
		  double rad = (double) (teta - 90) * M_PI / 180;
		  size_t rho =(size_t) ((double) x * cos(rad) + (double) y * sin(rad));
		  houg[(int)rad * hougcolls + rho] += 1;
		}
	    }
	}
    }
}

//Retourne l'angle de la droite sur laquel est le point (x,y)

size_t angle(int houg[], size_t x, size_t y)
{
  for (size_t teta = 0; teta < 180; teta++)
    {
      double rad = (double) (teta - 90) * M_PI / 180;
      size_t rho = (size_t) ((double) x * cos(rad) + (double) y * sin(rad));

      if (houg[(int)rad * 180 + teta] >= 30)
	{
	  return teta;
	}
    }
  return 180;
}

//Decoupe un fragment de l'image

void cut(int mat[], int cas[], size_t x1, size_t y1, size_t x2, size_t y2, size_t matcolls)
{
  for (size_t x = 0; x < (x2 - x1); x++)
    {
      for (size_t y = 0; y < (y2 - y1); y++)
	{
	  cas[y * (x2 - x1) + x] = mat[(y1 + y) * matcolls + x1 + x];
 	}
    }
}

//Test si l'image n'est pas vide de caractere a traiter

int test_cas(int mat[], size_t colls, size_t lines)
{
  int res = 0;
  for (size_t x = 0; x < colls; x++)
    {
      for (size_t y = 0; y < lines; y++)
	{
	  res += mat[y * (colls * lines) + x];
	}
    }

  res = (res * 100) / (colls * lines);

  if (res >= 90)
    {
      return 0;
    }
  return 1;
}

