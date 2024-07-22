
#include "jeu.h"

int jouer(SDL_Renderer *renderer, long niveau)
{
     //FMOD_System_Create(&//FMODsystem);
     //FMOD_System_Init(//FMODsystem, 32, //FMOD_INIT_NORMAL, NULL);

     TTF_Init();
     SDL_Texture *corps = NULL,*casegrise = NULL,*queue = NULL,*caserose = NULL,*pomme = NULL;
     SDL_Surface *fond_chateau = NULL,*chargement=NULL, *perdu = NULL,*pause = NULL,*gagne = NULL,*txtnbpomme = NULL;
     chargement = IMG_Load("chargement.gif");
     SDL_Texture *tete[4];
     SDL_Texture *teteActuel;
     //SDL_BlitSurface(chargement,NULL,ecran,&position);
     SDL_Texture *textureChargement = SDL_CreateTextureFromSurface(renderer, chargement);

     SDL_Rect position={LF/2-chargement->w/2,HF/2-chargement->h/2}, positionSerpent;
     SDL_RenderCopy(renderer, textureChargement, NULL, &position);
     SDL_RenderPresent(renderer);

     SDL_TimerID timer,timer2;
     SDL_Event event;
     SDL_Color gris = {210,210,210};
     //FMOD_SOUND *musique_chateau_01 = NULL, *musique_chateau_02 = NULL;
     //FMOD_SOUND *son_perdu = NULL,*son_gagne = NULL;
     //FMOD_SOUND *bomb = NULL;
     //FMOD_CHANNELGROUP *channelGroup;
     int cnt = 1,sens,modif = 0,keydown=0,stop=0,p_up = 0,resultat=0;
     int carte[NOMBRE_BLOCS_LARGEUR][NOMBRE_BLOCS_HAUTEUR];
     long i,j,k;
     long pommesRestantes = 10,vitesse = 500;
     char nbpomme[3];
     Uint32 currentTick = 0, lastTick = 0; // ajout 2024 pour réintégration thread "bouger" dans la boucle principale
     Mouvement mouv;
     Pose pose;
     TTF_Font *actionj;

     gagne = IMG_Load("gagne.jpg");
     perdu = IMG_Load("perdu.jpg");
     pause = IMG_Load("pause.gif");
     fond_chateau = IMG_Load("chateau.jpg");

     corps = createTextureFromFile(renderer, "corpsserpent.gif");
     casegrise = createTextureFromFile(renderer, "casebleue.gif");
     caserose = createTextureFromFile(renderer, "caseviolette.gif");
     queue = createTextureFromFile(renderer, "queueserpent.gif");
     pomme = createTextureFromFile(renderer, "pomme.gif");
     tete[HAUT] = createTextureFromFile(renderer, "tetehaut.gif");
     tete[BAS] = createTextureFromFile(renderer, "tetebas.gif");
     tete[DROITE] = createTextureFromFile(renderer, "tetedroite.gif");
     tete[GAUCHE] = createTextureFromFile(renderer, "tetegauche.gif");
     actionj = TTF_OpenFont("fullhouse.ttf",20);

     SDL_Texture *textureChateau = SDL_CreateTextureFromSurface(renderer, fond_chateau);
     SDL_Texture *texturePerdu = SDL_CreateTextureFromSurface(renderer, perdu);
     SDL_Texture *textureGagne = SDL_CreateTextureFromSurface(renderer, gagne);
     SDL_Texture *texturePause = SDL_CreateTextureFromSurface(renderer, pause);
     SDL_Texture *textureTxtNbPomme = NULL;
/*
     //FMOD_System_CreateSound(//FMODsystem, "chateau_01.mp3", //FMOD_SOFTWARE | //FMOD_2D | //FMOD_CREATESTREAM | //FMOD_LOOP_NORMAL, 0, &musique_chateau_01);
     //FMOD_System_CreateSound(//FMODsystem, "chateau_02.mp3", //FMOD_SOFTWARE | //FMOD_2D | //FMOD_CREATESTREAM, 0, &musique_chateau_02);

     //FMOD_System_CreateSound(//FMODsystem, "tube.wav", //FMOD_CREATESAMPLE, 0, &(mouv.avance));
     //FMOD_System_CreateSound(//FMODsystem, "apparition.wav", //FMOD_CREATESAMPLE, 0, &(pose.son_pomme));
     //FMOD_System_CreateSound(//FMODsystem, "croc.wav", //FMOD_CREATESAMPLE, 0, &(mouv.croc));
     //FMOD_System_CreateSound(//FMODsystem, "bomb.wav", //FMOD_CREATESAMPLE, 0, &bomb);
     //FMOD_System_CreateSound(//FMODsystem, "gagne.wav", //FMOD_CREATESAMPLE, 0, &son_gagne);
     //FMOD_System_CreateSound(//FMODsystem, "perdu.wav", //FMOD_CREATESAMPLE, 0, &son_perdu);
*/
     if (!charger(carte,&sens,niveau))
     {
                                     printf("Erreur lors du chargement du niveau %ld", niveau);
                                     return 0;
     }

     mouv.tailleSerpent = 4;

     for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
     {
         for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
         {
             if (carte[i][j] == SERPENT)
             {
                             positionSerpent.x = i;
                             positionSerpent.y = j;
                             switch(sens)
                             {
                                         case GAUCHE :
                                              for (k=1;k<=mouv.tailleSerpent;k++)
                                              {
                                                  carte[i+k][j] = CORPS;
                                              }
                                              carte[i+mouv.tailleSerpent][j] = QUEUE;
                                              break;
                                         case DROITE :
                                              for (k=1;k<=mouv.tailleSerpent;k++)
                                              {
                                                  carte[i-k][j] = CORPS;
                                              }
                                              carte[i-mouv.tailleSerpent][j] = QUEUE;
                                              break;
                                         case HAUT :
                                              for (k=1;k<=mouv.tailleSerpent;k++)
                                              {
                                                  carte[i][j+k] = CORPS;
                                              }
                                              carte[i][j+mouv.tailleSerpent] = QUEUE;
                                              break;
                                         case BAS :
                                              for (k=1;k<=mouv.tailleSerpent;k++)
                                              {
                                                  carte[i][j-k] = CORPS;
                                              }
                                              carte[i][j-mouv.tailleSerpent] = QUEUE;
                                              break;
                             }
             }
         }
     }

     // initialisation Mouvement et Pose

     mouv.perdu = 0;
     mouv.pomme = 1;
     mouv.fleche = 1;
     mouv.dir = sens;
     mouv.dirQ = sens;
     mouv.posT = positionSerpent;
     for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
     {
         for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
         {
             if (carte[i][j] == QUEUE)
             {
                             mouv.posQ.x = i;
                             mouv.posQ.y = j;
             }
         }
     }
     for (i=0;i<2500;i++)
     {
         mouv.cmpt[i].valeur = -1;
         mouv.cmpt[i].dir = sens;
     }
     for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
     {
         for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
         {
             mouv.carte[i][j] = carte[i][j];
         }
     }

     pose.pomme = 0;
     pose.debut = 1;
     for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
     {
         for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
         {
             pose.carte[i][j] = carte[i][j];
         }
     }

     //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, musique_chateau_01, 0, NULL);

     // Boucle principale

     timer = SDL_AddTimer(vitesse,bouger,&mouv);
     timer2 = SDL_AddTimer(5000,posePomme,&pose);
     while (cnt)
     {
           // tests musique

            //FMOD_Sound_SetLoopCount(musique_chateau_01, -1);

//           if (FSOUND_Stream_GetTime(musique_chateau_01) >= 114000)
//           {
//                                                         FSOUND_Stream_Stop(musique_chateau_01);
//                                                         //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, musique_chateau_02, 0, NULL);
//           }
//           if (FSOUND_Stream_GetTime(musique_chateau_02) >= 134000)
//           {
//                                                         FSOUND_Stream_Stop(musique_chateau_02);
//                                                         //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, musique_chateau_01, 0, NULL);
//           }

           // tests issue mouvement

           if (mouv.perdu)
           {
                          SDL_RemoveTimer(timer);
                          SDL_RemoveTimer(timer2);
//                          FSOUND_Stream_Stop(musique_chateau_01);
//                          FSOUND_Stream_Stop(musique_chateau_02);
                          //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, son_perdu, 0, NULL);
                          position.x = LF/2-perdu->w/2;
                          position.y = HF/2-perdu->h/2;
                          position.w = perdu->w;
                          position.h = perdu->h;
                          //SDL_BlitSurface(perdu,NULL,ecran,&position);
                          SDL_RenderCopy(renderer, texturePerdu, NULL, &position);
                          SDL_RenderPresent(renderer);
                          //SDL_Flip(ecran);
                          SDL_Delay(3000);
                          cnt=0;
                          resultat = 0;
           }

           else
           {
            for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
            {
                for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
                {
                  carte[i][j] = mouv.carte[i][j];
                }
            }
            if (!pose.debut && mouv.pomme)
            {
            carte[pose.x][pose.y] = POMME;
            }
            if (!mouv.pomme)
            {
                              SDL_RemoveTimer(timer);
                              carte[pose.x][pose.y] = mouv.carte[pose.x][pose.y];
                              pommesRestantes--;
                              pose.pomme = 0;
                              pose.debut = 1;
                              mouv.tailleSerpent++;
                              vitesse -= 20;
                              timer = SDL_AddTimer(vitesse,bouger,&mouv);
                              mouv.pomme = 1;
            }
           }

           switch(mouv.dir)
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

           for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
           {
               for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
               {
                   mouv.carte[i][j] = carte[i][j];
                   pose.carte[i][j] = carte[i][j];
               }
           }

           // -----------------------
           /* 2024 : Je déplace ici le contenu de la fonction bouger, gérée par timer, car la structure mouv était alors modifiée par deux threads en même temps
           Cela donnait lieu à de gros bugs de dislocation du serpent si le thread du timer intervenait en plein milieu de la boucle principale.
           La dynamique liée à la vitesse du serpent est donc plutôt gérer par SDL_GetTicks*/

      currentTick = SDL_GetTicks();
      if (currentTick - lastTick > vitesse) {

       switch(mouv.dir)
       {
                        case GAUCHE :
                             mouv.posT.x--;
                             break;
                        case DROITE :
                             mouv.posT.x++;
                             break;
                        case HAUT :
                             mouv.posT.y--;
                             break;
                        case BAS :
                             mouv.posT.y++;
                             break;
       }

       // test collision

       if (mouv.carte[mouv.posT.x][mouv.posT.y] == CASEGRISE || mouv.carte[mouv.posT.x][mouv.posT.y] == CASEROSE || mouv.carte[mouv.posT.x][mouv.posT.y] == CORPS || mouv.carte[mouv.posT.x][mouv.posT.y] == QUEUE)
       mouv.perdu = 1;
       if (mouv.carte[mouv.posT.x][mouv.posT.y] == POMME)
       {
       //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, mouv.croc, 0, NULL);
       mouv.pomme = 0;
       }

       for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
       {
           for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
           {
               if (mouv.carte[i][j] == SERPENT)
               mouv.carte[i][j] = CORPS;
               if (mouv.pomme)
               {
               if (mouv.carte[i][j] == QUEUE)
               {
                                     if (mouv.cmpt[0].valeur == 0)
                                     {
                                                              mouv.dirQ = mouv.cmpt[0].dir;
                                                              for (k=1;k<2500;k++)
                                                              {
                                                                  mouv.cmpt[k-1].dir = mouv.cmpt[k].dir;
                                                                  mouv.cmpt[k-1].valeur = mouv.cmpt[k].valeur;
                                                              }
                                     }
                                     switch(mouv.dirQ)
                                     {
                                                       case GAUCHE :
                                                            mouv.posQ.x--;
                                                            break;
                                                       case DROITE :
                                                            mouv.posQ.x++;
                                                            break;
                                                       case HAUT :
                                                            mouv.posQ.y--;
                                                            break;
                                                       case BAS :
                                                            mouv.posQ.y++;
                                                            break;
                                     }
                                     mouv.carte[i][j] = VIDE;
               }
               }

           }
       }
       mouv.carte[mouv.posT.x][mouv.posT.y] = SERPENT;
       mouv.carte[mouv.posQ.x][mouv.posQ.y] = QUEUE;

       if (mouv.pomme)
       {
       for (i=0;i<2500;i++)
       {
           if (mouv.cmpt[i].valeur != -1)
           {
           mouv.cmpt[i].valeur--;
           printf("%d%d    ",(int) i,mouv.cmpt[i].valeur);
           }
       }
       printf("\n");
       }
       mouv.fleche = 0;

       lastTick = SDL_GetTicks();
      }

           // -----------------------

           SDL_PollEvent(&event);
           switch(event.type)
           {
                             case SDL_KEYUP :
                                  keydown = 0;
                                  switch(event.key.keysym.sym)
                                  {
                                                              case SDLK_ESCAPE :
                                                                   cnt = 0;
                                                                   resultat = 0;
                                                                   break;
                                                              default:
                                                                break;
                                  }
                                  break;
                             case SDL_KEYDOWN :
                                  if (!keydown && !mouv.fleche)
                                  {
                                  switch(event.key.keysym.sym)
                                  {
                                      case SDLK_LEFT :
                                            mouv.dir = GAUCHE;
                                            /*
                                            * Merci moi du passé (bébé moi) de ne rien avoir commenté.
                                            * Si je comprends bien, le compteur sert à se souvenir de la direction
                                            * à chaque "boule" du corps du serpent pour que le mouvement soit suivi le long
                                            * du trajet parcouru.
                                            * (que la queue vienne effacer les boules dans l'ordre)
                                            */
                                            for (i=0;i<2500;i++) // taille maximale du serpent 2500 du coup...
                                            {
                                                if (mouv.cmpt[i].valeur == -1 && !modif) // on prend le premier compteur libre, le serpent ne fait que croître
                                                {
                                                      mouv.cmpt[i].valeur = mouv.tailleSerpent;
                                                      mouv.cmpt[i].dir = GAUCHE;
                                                      modif = 1;
                                                }
                                            }
                                            modif = 0;
                                            mouv.fleche = 1;
                                            break;
                                      case SDLK_RIGHT :
                                            mouv.dir = DROITE;
                                            for (i=0;i<2500;i++)
                                            {
                                                if (mouv.cmpt[i].valeur == -1 && !modif)
                                                {
                                                                        mouv.cmpt[i].valeur = mouv.tailleSerpent;
                                                                        mouv.cmpt[i].dir = DROITE;
                                                                        modif = 1;
                                                }
                                            }
                                            modif = 0;
                                            mouv.fleche = 1;
                                            break;
                                      case SDLK_UP :
                                            mouv.dir = HAUT ;
                                            for (i=0;i<2500;i++)
                                            {
                                                if (mouv.cmpt[i].valeur == -1 && !modif)
                                                {
                                                                        mouv.cmpt[i].valeur = mouv.tailleSerpent;
                                                                        mouv.cmpt[i].dir = HAUT;
                                                                        modif = 1;
                                                }
                                            }
                                            modif = 0;
                                            mouv.fleche = 1;
                                            break;
                                      case SDLK_DOWN :
                                            mouv.dir = BAS;
                                            for (i=0;i<2500;i++)
                                            {
                                                if (mouv.cmpt[i].valeur == -1 && !modif)
                                                {
                                                                        mouv.cmpt[i].valeur = mouv.tailleSerpent;
                                                                        mouv.cmpt[i].dir = BAS;
                                                                        modif = 1;
                                                }
                                            }
                                            modif = 0;
                                            mouv.fleche = 1;
                                            break;
                                      case SDLK_p :
                                            stop = 1;
                                            break;
                                      default:
                                        break;
                                  }
                                  keydown = 1;
                                  }
                                  break;
                            default:
                                break;
           }

          
           //SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
           SDL_RenderClear(renderer);
           //position.x = 0;
           //position.y = 0;
           //SDL_BlitSurface(fond_chateau,NULL,ecran,&position);
           SDL_RenderCopy(renderer, textureChateau, NULL, NULL);

           SDL_Texture *blitSurface = NULL;

           for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
           {
               for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
               {
                   position.x = i*TAILLE_BLOC;
                   position.y = j*TAILLE_BLOC;
                   position.w = position.h = TAILLE_BLOC;
                   blitSurface = NULL;

                   switch(carte[i][j])
                   {
                                      case CORPS :
                                           //SDL_BlitSurface(corps,NULL,ecran,&position);
                                           blitSurface = corps;
                                           break;
                                      case SERPENT :
                                           //SDL_BlitSurface(teteActuel,NULL,ecran,&position);
                                           blitSurface = teteActuel;
                                           break;
                                      case QUEUE :
                                           //SDL_BlitSurface(queue,NULL,ecran,&position);
                                           blitSurface = queue;
                                           break;
                                      case CASEGRISE :
                                           //SDL_BlitSurface(casegrise,NULL,ecran,&position);
                                           blitSurface = casegrise;
                                           break;
                                      case CASEROSE :
                                           //SDL_BlitSurface(caserose,NULL,ecran,&position);
                                           blitSurface = caserose;
                                           break;
                                      case POMME :
                                           //SDL_BlitSurface(pomme,NULL,ecran,&position);
                                           blitSurface = pomme;
                                           break;
                   }
                   if (blitSurface)
                      SDL_RenderCopy(renderer, blitSurface, NULL, &position);
               }
           }

           // affichages

           position.x = 46*TAILLE_BLOC;
           position.y = 0;

           //SDL_BlitSurface(pomme,NULL,ecran,&position);
           SDL_RenderCopy(renderer, pomme, NULL, &position);

           position.x = 47*TAILLE_BLOC+5;
           sprintf(nbpomme,"x %ld",pommesRestantes);

           txtnbpomme = TTF_RenderText_Solid(actionj,nbpomme,gris);
           //SDL_BlitSurface(txtnbpomme,NULL,ecran,&position);
           if (textureTxtNbPomme) // réinitialisation si nécessaire
            SDL_DestroyTexture(textureTxtNbPomme);
           textureTxtNbPomme = SDL_CreateTextureFromSurface(renderer, txtnbpomme);
           SDL_RenderCopy(renderer, textureTxtNbPomme, NULL, &position);

           if (stop)
           {
                    position.x = LF/2-pause->w/2;
                    position.y = HF/2-pause->h/2;
                    position.w = pause->w;
                    position.h = pause->h;
                    //SDL_BlitSurface(pause,NULL,ecran,&position);
                    SDL_RenderCopy(renderer, texturePause, NULL, &position);
           }
           //SDL_Flip(ecran);
           SDL_RenderPresent(renderer);

           if (stop)
           {
                    SDL_RemoveTimer(timer);
                    SDL_RemoveTimer(timer2);
                    do
                    {
                           SDL_WaitEvent(&event);
                           if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_p) p_up = 1; // break ?
                    }
                    while (event.type != SDL_KEYDOWN || event.key.keysym.sym != SDLK_p || !p_up); // je connaissais pas break; a priori en 2007...
                    stop = 0;
                    p_up = 0;
                    timer = SDL_AddTimer(vitesse,bouger,&mouv);
                    timer2 = SDL_AddTimer(5000,posePomme,&pose);
           }

           if (pommesRestantes == 0)
           {
                               SDL_RemoveTimer(timer);
                               SDL_RemoveTimer(timer2);
//                               FSOUND_Stream_Stop(musique_chateau_01);
//                               FSOUND_Stream_Stop(musique_chateau_02);
                               //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, son_gagne, 0, NULL);
                               position.x = LF/2-gagne->w/2;
                               position.y = HF/2-gagne->h/2;
                               position.w = gagne->w;
                               position.h = gagne->h;
                               //SDL_BlitSurface(gagne,NULL,ecran,&position);
                               SDL_RenderCopy(renderer, textureGagne, NULL, &position);
                               //SDL_Flip(ecran);
                               SDL_RenderPresent(renderer);
                               SDL_Delay(3000);
                               cnt=0;
                               resultat = 1;
           }
     }

     SDL_DestroyTexture(corps);
     SDL_DestroyTexture(casegrise);
     SDL_DestroyTexture(queue);
     SDL_DestroyTexture(caserose);
     SDL_DestroyTexture(pomme);
     for (i=0;i<4;i++)
     {
         SDL_DestroyTexture(tete[i]);
     }

     SDL_FreeSurface(gagne);
     SDL_FreeSurface(perdu);
     SDL_FreeSurface(pause);
     SDL_FreeSurface(fond_chateau);
     SDL_FreeSurface(chargement);

     SDL_DestroyTexture(textureGagne);
     SDL_DestroyTexture(texturePerdu);
     SDL_DestroyTexture(texturePause);
     SDL_DestroyTexture(textureChateau);
     SDL_DestroyTexture(textureChargement);
     SDL_DestroyTexture(textureTxtNbPomme);
     /*//FMOD_Sound_Release(musique_chateau_01);
     //FMOD_Sound_Release(musique_chateau_02);
     //FMOD_Sound_Release(mouv.avance);
     //FMOD_Sound_Release(pose.son_pomme);
     //FMOD_Sound_Release(mouv.croc);
     //FMOD_Sound_Release(bomb);
     //FMOD_Sound_Release(son_gagne);
     //FMOD_Sound_Release(son_perdu);*/
     SDL_RemoveTimer(timer);
     SDL_RemoveTimer(timer2);
     TTF_CloseFont(actionj);
     TTF_Quit();

     //FMOD_System_Close(//FMODsystem);
     //FMOD_System_Release(//FMODsystem);

     return resultat;

}

Uint32 bouger(Uint32 intervalle, void *param)
{
/*
       Mouvement *mouv = param;

       //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, mouv->avance, 0, NULL);

       long i,j,k;

       switch(mouv->dir)
       {
                        case GAUCHE :
                             mouv->posT.x--;
                             break;
                        case DROITE :
                             mouv->posT.x++;
                             break;
                        case HAUT :
                             mouv->posT.y--;
                             break;
                        case BAS :
                             mouv->posT.y++;
                             break;
       }

       // test collision

       if (mouv->carte[mouv->posT.x][mouv->posT.y] == CASEGRISE || mouv->carte[mouv->posT.x][mouv->posT.y] == CASEROSE || mouv->carte[mouv->posT.x][mouv->posT.y] == CORPS || mouv->carte[mouv->posT.x][mouv->posT.y] == QUEUE || mouv->carte[mouv->posT.x][mouv->posT.y] == BOMBE)
       mouv->perdu = 1;
       if (mouv->carte[mouv->posT.x][mouv->posT.y] == POMME)
       {
       //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, mouv->croc, 0, NULL);
       mouv->pomme = 0;
       }

       for (i=0;i<NOMBRE_BLOCS_LARGEUR;i++)
       {
           for (j=0;j<NOMBRE_BLOCS_HAUTEUR;j++)
           {
               if (mouv->carte[i][j] == SERPENT)
               mouv->carte[i][j] = CORPS;
               if (mouv->pomme)
               {
               if (mouv->carte[i][j] == QUEUE)
               {
                                     if (mouv->cmpt[0].valeur == 0)
                                     {
                                                              mouv->dirQ = mouv->cmpt[0].dir;
                                                              for (k=1;k<2500;k++)
                                                              {
                                                                  mouv->cmpt[k-1].dir = mouv->cmpt[k].dir;
                                                                  mouv->cmpt[k-1].valeur = mouv->cmpt[k].valeur;
                                                              }
                                     }
                                     switch(mouv->dirQ)
                                     {
                                                       case GAUCHE :
                                                            mouv->posQ.x--;
                                                            break;
                                                       case DROITE :
                                                            mouv->posQ.x++;
                                                            break;
                                                       case HAUT :
                                                            mouv->posQ.y--;
                                                            break;
                                                       case BAS :
                                                            mouv->posQ.y++;
                                                            break;
                                     }
                                     mouv->carte[i][j] = VIDE;
               }
               }

           }
       }
       mouv->carte[mouv->posT.x][mouv->posT.y] = SERPENT;
       mouv->carte[mouv->posQ.x][mouv->posQ.y] = QUEUE;

       if (mouv->pomme)
       {
       for (i=0;i<2500;i++)
       {
           if (mouv->cmpt[i].valeur != -1)
           {
           mouv->cmpt[i].valeur--;
           printf("%d%d    ",(int) i,mouv->cmpt[i].valeur);
           }
       }
       printf("\n");
       }
       mouv->fleche = 0;
       */
       return intervalle;

}

Uint32 posePomme(Uint32 intervalle,void *param)
{
       Pose *pose = param;
       srand(time(NULL));
       pose->debut = 0;

       if (!pose->pomme)
       {
       do{
       pose->x = (rand() % ((NOMBRE_BLOCS_LARGEUR-2)-1+1))+1;
       pose->y = (rand() % ((NOMBRE_BLOCS_HAUTEUR-2)-1+1))+1;
       pose->pomme = 1;
       }
       while(pose->carte[pose->x][pose->y] == CASEGRISE || pose->carte[pose->x][pose->y] == SERPENT || pose->carte[pose->x][pose->y] == CORPS || pose->carte[pose->x][pose->y] == QUEUE);
       //FMOD_System_PlaySound(//FMODsystem, //FMOD_CHANNEL_FREE, pose->son_pomme, 0, NULL);
       }
       return intervalle;
}




