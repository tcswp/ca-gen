#include <SDL/SDL.h>
#include <math.h>
#include <getopt.h>

#include "elemca.h"
#include "lifeca.h"

#define LIFE 1
#define ELEM 2

void scale_grid(char *new, const char *old, int x, int y, int scale)
{
  int i, j, k, l;
  
  for (i = 0; i < y/scale; i++)
  {
    for (j = 0; j < x/scale; j++)
      for (k = 0; k < scale; k++)
        new[i*scale*x+j*scale+k] = old[i*x+j];
    for (l = 1; l < scale; l++)
      memcpy(new+i*scale*x+l*x, new+i*scale*x, x);
  }
}

static inline void set_pixel(SDL_Surface *screen, int x, int y, SDL_Color *color)
{
  uint32_t *pixels = (uint32_t*) screen->pixels;
  pixels[screen->w*y+x] = SDL_MapRGB(screen->format, color->r, color->g, color->b);
}

int main(int argc, char **argv)
{
  SDL_Surface *screen;
  const SDL_VideoInfo* info;
  SDL_Event event;
  SDL_Color fgcolor = {.r=0,.g=0,.b=0};
  SDL_Color bgcolor = {.r=255,.g=255,.b=255};
  
  int w;
  int h;
  
  int i, j;
  char c;
  
  SDL_Init(SDL_INIT_VIDEO);
  info = SDL_GetVideoInfo();
  w = info->current_w;
  h = info->current_h;
  screen = SDL_SetVideoMode(w, h, 0, SDL_FULLSCREEN);
  SDL_ShowCursor(0);
  
  char grid[w*h];
  char next_gen[w*h];
  char scaled[w*h];
  
  // defaults
  int ca_type = LIFE;
  int scale = 4;
  float density = 0.25;
  char liferule[20] = "B3/S23";
  int elemrule = 30;
  int rand_seed = 0;
  
  memset(grid, 0, w*h);
  
  while ((c = getopt(argc, argv, "l:e:s:d:f:b:r")) != -1)
  {
    switch (c)
    {
      case 'l': ca_type = LIFE;
                strcpy(liferule, optarg);
                break;
      case 'e': ca_type = ELEM;
                elemrule = atoi(optarg);
                break;
      case 'd': density = atof(optarg);
                break;
      case 's': scale = atoi(optarg);
                scale = pow(2, scale-1);
                break;
      case 'f': sscanf(optarg, "%d,%d,%d",
                       fgcolor.r, fgcolor.g, fgcolor.b);
                break;
      case 'b': sscanf(optarg, "%d,%d,%d",
                       bgcolor.r, bgcolor.g, bgcolor.b);
                break;
      case 'r': rand_seed = 1;
                break;
      default:  exit(0);
    }
  }
  
  if (ca_type == LIFE) random_seed(grid, w*h, density);

  while (1)
  {
    if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN) break;
    
    if (ca_type == LIFE)
    {
      evolve_lifelike_ca(next_gen, grid, w, h, liferule);
      memcpy(grid, next_gen, w*h);
    }
    else if (ca_type == ELEM)
      gen_elem_ca(grid, w, h, elemrule, rand_seed);
    
    scale_grid(scaled, grid, w, h, scale);
    for (i = 0; i < h; i++)
      for (j = 0; j < w; j++)
        if (scaled[i*w+j])
         set_pixel(screen, j, i, &fgcolor);
        
    SDL_Flip(screen);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, bgcolor.r, bgcolor.g, bgcolor.b));
  }
  
  return 0;
}
