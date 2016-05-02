#include <time.h>
#include <stdlib.h>

void gen_elem_ca(char *grid, int x, int y, int rule, int rand_seed)
{
  int i, j;

  if (rand_seed)
    for (srand(time(0)),i = 0; i < x; i++)
      grid[i] = rand()%2;
  else grid[x/2] = 1;
  
  for (i = 1; i < y; i++)
    for (j = 1; j < x; j++)
      grid[i*x+j] = ((rule >> (7 & (grid[(i-1)*x+j-1] << 2
                        | grid[(i-1)*x+j] << 1
                        | grid[(i-1)*x+j+1])))&1)?1:0;
} 
