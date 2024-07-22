/*
  Name: fonctions.h
  Copyright: 2007
  Author: Disclosis
  Date: 23/04/07 19:09
  Description: fonctions diverses SNAKE :
                         * options création éditeur
*/

#ifndef DEF_FONCTIONS
#define DEF_FONCTIONS
#include <stdlib.h>
#include <stdio.h>
#include "constantes.h"

long chargerEdit(SDL_Renderer *renderer);

void attention(SDL_Renderer *renderer, int parametre);

#endif
