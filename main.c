#include <stdlib.h>
#include <stdio.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "fonctions.h"
#include "fichiers.h"

int main(int argc,char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_Surface *accueil = NULL;
    SDL_Event event;
    //SDL_Window *ecran = SDL_CreateWindow("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LF, HF, SDL_WINDOW_FULLSCREEN);
    SDL_Window *ecran = SDL_CreateWindow("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LF, HF, 0);
    if (ecran == NULL)
    {
        printf("%s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(ecran, -1, 0);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(renderer, LF, HF);

    if (renderer == NULL)
    {
        printf("%s\n", SDL_GetError());
        return 1;
    }
    SDL_ShowCursor(SDL_DISABLE);
    int cnt = 1,gagne=1;
    long niveau = 1;

    accueil = IMG_Load("serpent.jpg");
    SDL_Texture* textureAccueil = SDL_CreateTextureFromSurface(renderer, accueil);

    while (cnt)
    {
          SDL_WaitEvent(&event);
          switch(event.type)
          {
                            case SDL_KEYUP :
                                 switch(event.key.keysym.sym)
                                 {
                                                             case SDLK_ESCAPE :
                                                                  cnt = 0;
                                                                  break;
                                                             case SDLK_KP_1 :
                                                                  do
                                                                  {
                                                                  if (gagne) gagne = jouer(renderer, niveau);
                                                                  niveau++;
                                                                  }
                                                                  while (niveau <= 10);
                                                                  niveau = 1;
                                                                  gagne = 1;
                                                                  break;
                                                             case SDLK_KP_2 :
                                                                  niveau = chargerEdit(renderer);
                                                                  if (niveau == -1)
                                                                  {
                                                                             niveau = 1;
                                                                             break;
                                                                  }
                                                                  editeur(renderer,niveau);
                                                                  niveau = 1;
                                                                  break;
                                                                default:
                                                                    break;
                                 }
                                 break;
                                 default:
                                    break;
          }
          SDL_RenderClear(renderer);
          SDL_RenderCopy(renderer, textureAccueil, NULL, NULL);
          SDL_RenderPresent(renderer);
    }

    printf("Sortie normale");
    SDL_FreeSurface(accueil);
    SDL_DestroyTexture(textureAccueil);
    SDL_Quit();
    return EXIT_SUCCESS;
}
