/*
  Name: fichiers.h
  Copyright: 2007
  Author: Disclosis
  Date: 25/03/07 13:17
  Description: sauvegardes/chargement
*/

#ifndef DEF_FICHIERS
#define DEF_FICHIERS
#include <stdlib.h>
#include <stdio.h>
#include "constantes.h"

void sauvegarder(int carte[][NOMBRE_BLOCS_HAUTEUR],const int sens,long niveau);

int charger(int carte[][NOMBRE_BLOCS_HAUTEUR],int *sens,long niveau);

#endif
