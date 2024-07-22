#include "constantes.h"

SDL_Texture* createTextureFromFile(SDL_Renderer* renderer, const char* fileName)
{
  SDL_Surface* surface = IMG_Load(fileName);
  SDL_Texture* texture = NULL;
  if (surface)
  {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }
  
  return texture;
}