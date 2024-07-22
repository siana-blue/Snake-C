
#include "editeur.h"

void editeur(SDL_Renderer *renderer,long niveau)
{
    SDL_Texture *corps = NULL,*casegrise = NULL,*queue = NULL,*caserose = NULL;
    SDL_Texture *tete[4];
    SDL_Texture *teteActuel;
    SDL_Rect position, positionSerpent = {30,30};
    SDL_Event event;
    SDL_ShowCursor(SDL_ENABLE);
    int cnt=1,clicGauche=0,clicDroit=0,serpent = 0,alt = 0,sens = GAUCHE;
    int carte[NOMBRE_BLOCS_LARGEUR][NOMBRE_BLOCS_HAUTEUR];
    long i,j,k;

    corps = createTextureFromFile(renderer, "corpsserpent.gif");
    casegrise = createTextureFromFile(renderer, "casebleue.gif");
    caserose = createTextureFromFile(renderer, "caseviolette.gif");
    queue = createTextureFromFile(renderer, "queueserpent.gif");
    tete[HAUT] = createTextureFromFile(renderer, "tetehaut.gif");
    tete[BAS] = createTextureFromFile(renderer, "tetebas.gif");
    tete[DROITE] = createTextureFromFile(renderer, "tetedroite.gif");
    tete[GAUCHE] = createTextureFromFile(renderer, "tetegauche.gif");

    if(!charger(carte,&sens,niveau))
    {
      for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
      {
          for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
          {
              carte[i][j] = 0;
              if (i==0 || j==0 || i==NOMBRE_BLOCS_LARGEUR-1 || j==NOMBRE_BLOCS_HAUTEUR-1) carte[i][j] = CASEROSE;
          }
      }
    }
    else serpent = 1;

    for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
    {
      for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
      {
          if (carte[i][j] == SERPENT)
          {
            positionSerpent.x = i;
            positionSerpent.y = j;
            serpent = 1;
          }
      }
    }

    while(cnt)
    {
              switch (sens)
              {
              case GAUCHE :
                   teteActuel = tete[GAUCHE];
                   break;
              case DROITE :
                   teteActuel = tete[DROITE];
                   break;
              case HAUT :
                   teteActuel = tete[HAUT];
                   break;
              case BAS :
                   teteActuel = tete[BAS];
                   break;
              }
              SDL_WaitEvent(&event);
              switch(event.type)
              {
                                case SDL_KEYDOWN :
                                     switch(event.key.keysym.sym)
                                     {
                                                                 case SDLK_s :
                                                                      if (serpent)
                                                                      sauvegarder(carte,sens,niveau);
                                                                      else attention(renderer,1);
                                                                      break;
                                                                 case SDLK_c :
                                                                      niveau = chargerEdit(renderer);
                                                                      if(!charger(carte,&sens,niveau))
                                                                      {
                                                                      for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
                                                                      {
                                                                      for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
                                                                      {
                                                                      carte[i][j] = 0;
                                                                      if (i==0 || j==0 || i==NOMBRE_BLOCS_LARGEUR-1 || j==NOMBRE_BLOCS_HAUTEUR-1) carte[i][j] = CASEROSE;
                                                                      }
                                                                      }
                                                                      serpent = 0;
                                                                      }
                                                                      else serpent = 1;
                                                                      break;
                                                                 case SDLK_SPACE :
                                                                      if (!serpent)
                                                                      {
                                                                                   carte[positionSerpent.x][positionSerpent.y] = SERPENT;
                                                                                   serpent = 1;
                                                                                   if (teteActuel == tete[GAUCHE])
                                                                                   {
                                                                                                  for (i=1;i<=4;i++)
                                                                                                  {
                                                                                                  if (positionSerpent.x+i >= NOMBRE_BLOCS_LARGEUR-1 || carte[positionSerpent.x+i][positionSerpent.y] == CASEGRISE)
                                                                                                  {
                                                                                                  serpent = 0;
                                                                                                  carte[positionSerpent.x][positionSerpent.y] = VIDE;
                                                                                                  }
                                                                                                  }
                                                                                                  sens = GAUCHE;
                                                                                   }
                                                                                   if (teteActuel == tete[HAUT])
                                                                                   {
                                                                                                  for (i=1;i<=4;i++)
                                                                                                  {
                                                                                                  if (positionSerpent.y+i >= NOMBRE_BLOCS_HAUTEUR-1 || carte[positionSerpent.x][positionSerpent.y+i] == CASEGRISE)
                                                                                                  {
                                                                                                  serpent = 0;
                                                                                                  carte[positionSerpent.x][positionSerpent.y] = VIDE;
                                                                                                  }
                                                                                                  }
                                                                                                  sens = HAUT;
                                                                                   }
                                                                                   if (teteActuel == tete[DROITE])
                                                                                   {
                                                                                                  for (i=1;i<=4;i++)
                                                                                                  {
                                                                                                  if (positionSerpent.x-i< 1 || carte[positionSerpent.x-i][positionSerpent.y] == CASEGRISE)
                                                                                                  {
                                                                                                  serpent = 0;
                                                                                                  carte[positionSerpent.x][positionSerpent.y] = VIDE;
                                                                                                  }
                                                                                                  }
                                                                                                  sens = DROITE;
                                                                                   }
                                                                                   if (teteActuel == tete[BAS])
                                                                                   {
                                                                                                  for (i=1;i<=4;i++)
                                                                                                  {
                                                                                                  if (positionSerpent.y-i < 1 || carte[positionSerpent.x][positionSerpent.y-i] == CASEGRISE)
                                                                                                  {
                                                                                                  serpent = 0;
                                                                                                  carte[positionSerpent.x][positionSerpent.y] = VIDE;
                                                                                                  }
                                                                                                  }
                                                                                                  sens = BAS;
                                                                                   }
                                                                      }
                                                                      break;
                                                                 case SDLK_LALT :
                                                                      alt = 1;
                                                                      break;
                                                                default:
                                                                    break;
                                     }
                                     break;
                                case SDL_KEYUP :
                                     switch(event.key.keysym.sym)
                                     {
                                                                 case SDLK_LALT :
                                                                      alt = 0;
                                                                      break;
                                                                 case SDLK_ESCAPE :
                                                                      cnt = 0;
                                                                      break;
                                                                default:
                                                                    break;
                                     }
                                     break;
                                case SDL_MOUSEBUTTONDOWN :
                                     switch(event.button.button)
                                     {
                                                                case SDL_BUTTON_LEFT :
                                                                     if (!alt)
                                                                     {
                                                                     if (carte[event.button.x/TAILLE_BLOC][event.button.y/TAILLE_BLOC] == CASEROSE) break;
                                                                     if (carte[event.button.x/TAILLE_BLOC][event.button.y/TAILLE_BLOC] == SERPENT) serpent = 0;
                                                                     carte[event.button.x/TAILLE_BLOC][event.button.y/TAILLE_BLOC] = CASEGRISE;
                                                                     clicGauche = 1;
                                                                     }

                                                                     else if (carte[event.button.x/TAILLE_BLOC][event.button.y/TAILLE_BLOC] == SERPENT)
                                                                     {
                                                                          if (teteActuel == tete[GAUCHE])
                                                                          {
                                                                          teteActuel = tete[HAUT];
                                                                          sens = HAUT;
                                                                          }
                                                                          else if (teteActuel == tete[HAUT])
                                                                          {
                                                                          teteActuel = tete[DROITE];
                                                                          sens = DROITE;
                                                                          }
                                                                          else if (teteActuel == tete[DROITE])
                                                                          {
                                                                          teteActuel = tete[BAS];
                                                                          sens = BAS;
                                                                          }
                                                                          else if (teteActuel == tete[BAS])
                                                                          {
                                                                          teteActuel = tete[GAUCHE];
                                                                          sens = GAUCHE;
                                                                          }
                                                                     }
                                                                     break;
                                                                case SDL_BUTTON_RIGHT :
                                                                     if (carte[event.button.x/TAILLE_BLOC][event.button.y/TAILLE_BLOC] == CASEROSE) break;
                                                                     if (carte[event.button.x/TAILLE_BLOC][event.button.y/TAILLE_BLOC] == SERPENT) serpent = 0;
                                                                     carte[event.button.x/TAILLE_BLOC][event.button.y/TAILLE_BLOC] = VIDE;
                                                                     clicDroit = 1;
                                                                     break;
                                                                default:
                                                                    break;
                                     }
                                     break;
                                case SDL_MOUSEBUTTONUP :
                                     switch(event.button.button)
                                     {
                                                                case SDL_BUTTON_LEFT :
                                                                     clicGauche = 0;
                                                                     break;
                                                                case SDL_BUTTON_RIGHT :
                                                                     clicDroit = 0;
                                                                     break;
                                                                default:
                                                                    break;
                                     }
                                     break;
                                case SDL_MOUSEMOTION :
                                     if (carte[event.motion.x/TAILLE_BLOC][event.motion.y/TAILLE_BLOC] == CASEROSE) break;
                                     if ((clicGauche || clicDroit) && carte[event.motion.x/TAILLE_BLOC][event.motion.y/TAILLE_BLOC] == SERPENT) serpent = 0;
                                     if (clicGauche) carte[event.motion.x/TAILLE_BLOC][event.motion.y/TAILLE_BLOC] = CASEGRISE;
                                     if (clicDroit) carte[event.motion.x/TAILLE_BLOC][event.motion.y/TAILLE_BLOC] = VIDE;

                                     if (!serpent)
                                     {
                                     positionSerpent.x = event.motion.x/TAILLE_BLOC;
                                     positionSerpent.y = event.motion.y/TAILLE_BLOC;
                                     }
                                     break;
                                default:
                                    break;
              }

              for (i=1;i<=4;i++)
              {
                  if (serpent)
                  {
                  switch (sens)
                  {
                         case GAUCHE :
                              if (carte[positionSerpent.x+i][positionSerpent.y] == CASEGRISE || carte[positionSerpent.x+i][positionSerpent.y] == CASEROSE)
                              {
                              carte[positionSerpent.x][positionSerpent.y] = VIDE;
                              serpent = 0;
                              }
                              break;
                         case DROITE :
                              if (carte[positionSerpent.x-i][positionSerpent.y] == CASEGRISE || carte[positionSerpent.x-i][positionSerpent.y] ==CASEROSE)
                              {
                              carte[positionSerpent.x][positionSerpent.y] = VIDE;
                              serpent = 0;
                              }
                              break;
                         case BAS :
                              if (carte[positionSerpent.x][positionSerpent.y-i] == CASEGRISE || carte[positionSerpent.x][positionSerpent.y-i] == CASEROSE)
                              {
                              carte[positionSerpent.x][positionSerpent.y] = VIDE;
                              serpent = 0;
                              }
                              break;
                         case HAUT :
                              if (carte[positionSerpent.x][positionSerpent.y+i] == CASEGRISE || carte[positionSerpent.x][positionSerpent.y+i] == CASEROSE)
                              {
                              carte[positionSerpent.x][positionSerpent.y] = VIDE;
                              serpent = 0;
                              }
                              break;
                  }
                  }
              }

              //SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
              SDL_RenderClear(renderer);
              for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
              {
                  for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
                  {

                      position.x = i*TAILLE_BLOC;
                      position.y = j*TAILLE_BLOC;
                      position.w = TAILLE_BLOC;
                      position.h = TAILLE_BLOC;

                      switch (carte[i][j])
                      {
                             case CASEGRISE :
                                  //SDL_BlitSurface(casegrise,NULL,ecran,&position);
                                  SDL_RenderCopy(renderer, casegrise, NULL, &position);
                                  break;
                             case SERPENT :
                                  //SDL_BlitSurface(teteActuel,NULL,ecran,&position);
                                  SDL_RenderCopy(renderer, teteActuel, NULL, &position);
                                  for (k=0;k<3;k++)
                                  {
                                      if (teteActuel == tete[GAUCHE])
                                      {
                                                     position.x += TAILLE_BLOC;
                                                     //SDL_BlitSurface(corps,NULL,ecran,&position);
                                                     SDL_RenderCopy(renderer, corps, NULL, &position);
                                      }
                                      else if (teteActuel == tete[HAUT])
                                      {
                                           position.y += TAILLE_BLOC;
                                           //SDL_BlitSurface(corps,NULL,ecran,&position);
                                           SDL_RenderCopy(renderer, corps, NULL, &position);
                                      }
                                      else if (teteActuel == tete[DROITE])
                                      {
                                           position.x -= TAILLE_BLOC;
                                           //SDL_BlitSurface(corps,NULL,ecran,&position);
                                           SDL_RenderCopy(renderer, corps, NULL, &position);
                                      }
                                      else
                                      {
                                          position.y -= TAILLE_BLOC;
                                          //SDL_BlitSurface(corps,NULL,ecran,&position);
                                          SDL_RenderCopy(renderer, corps, NULL, &position);
                                      }
                                  }
                                  if (teteActuel == tete[GAUCHE])
                                  {
                                                 position.x += TAILLE_BLOC;
                                                 //SDL_BlitSurface(queue,NULL,ecran,&position);
                                                 SDL_RenderCopy(renderer, queue, NULL, &position);
                                  }
                                  else if (teteActuel == tete[HAUT])
                                  {
                                       position.y += TAILLE_BLOC;
                                       //SDL_BlitSurface(queue,NULL,ecran,&position);
                                       SDL_RenderCopy(renderer, queue, NULL, &position);
                                  }
                                  else if (teteActuel == tete[DROITE])
                                  {
                                       position.x -= TAILLE_BLOC;
                                       //SDL_BlitSurface(queue,NULL,ecran,&position);
                                       SDL_RenderCopy(renderer, queue, NULL, &position);
                                  }
                                  else
                                  {
                                      position.y -= TAILLE_BLOC;
                                      //SDL_BlitSurface(queue,NULL,ecran,&position);
                                      SDL_RenderCopy(renderer, queue, NULL, &position);
                                  }
                                  break;
                             case CASEROSE :
                                  //SDL_BlitSurface(caserose,NULL,ecran,&position);
                                  SDL_RenderCopy(renderer, caserose, NULL, &position);
                                  break;
                      }
                  }
              }
              //SDL_Flip(ecran);
              SDL_RenderPresent(renderer);
    }

    SDL_ShowCursor(SDL_DISABLE);
    SDL_DestroyTexture(corps);
    SDL_DestroyTexture(casegrise);
    SDL_DestroyTexture(caserose);
    SDL_DestroyTexture(queue);
    SDL_DestroyTexture(teteActuel);
    for (i=0;i<4;i++)
    {
        SDL_DestroyTexture(tete[i]);
    }
}


