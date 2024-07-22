/*
  Name: jeu.h
  Copyright: 2007
  Author: Disclosis
  Date: 31/03/07 18:37
  Description: jeu SNAKE
*/

#ifndef DEF_JEU
#define DEF_JEU
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "constantes.h"
#include "fichiers.h"

int jouer(SDL_Renderer *renderer, long niveau);

Uint32 bouger(Uint32 intervalle, void *param);

Uint32 posePomme(Uint32 intervalle,void *param);

#endif
