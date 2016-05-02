#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void random_seed(char *grid, int res, float p)
{
  int i;
  for (srand(time(0)), i=0; i<res; i++)
    grid[i] = (rand()%100 > p*100)?1:0;
}

void evolve_lifelike_ca(char *nextgen, const char *grid,
                          int xres, int yres, const char *rule)
{
  int p, n;
  int res = xres*yres;
  
  char b[9], s[9], c, *cp;
  if (sscanf(rule, "%*[Bb]%[^/]/%*[Ss]%s", b, s) != 2)
  {
    fprintf(stderr, "rule did not match\n");
    exit(0);
  }
  
  for (p=0,n=0; p<res; p++,n=0)
  {
    /* Get state of cells in the Moore neighborhood and make grid finite */
    
    if (p > xres && p%xres != 0)            n+=grid[p-1-xres];
    if (p > xres)                           n+=grid[p-xres];
    if (p > xres && p%(xres-1) != 0)        n+=grid[p+1-xres];
    
    if (p % xres != 0)                      n+=grid[p-1];
    if (p % (xres-1) != 0)                  n+=grid[p+1];
    
    if (p < res-xres && p%xres != 0)        n+=grid[p-1+xres];
    if (p < res-xres)                       n+=grid[p+xres];
    if (p < res-xres && p%(xres-1) != 0)    n+=grid[p+1+xres];
    
    if (grid[p])
    {
      nextgen[p] = 0;
      cp = s;
      while (c = *cp++)
        if (n == c-48)
        {
          nextgen[p] = 1;
          break;
        }
    }
    else
    {
      cp = b;
      while (c = *cp++)
        if (n == c-48)
        {
          nextgen[p] = 1;
          break;
        }
    }
  }
}
