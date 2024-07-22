
#include "fonctions.h"

long chargerEdit(SDL_Renderer *renderer)
{
     TTF_Init();
     long niveau = 1;
     int cnt = 1;
     char niv[10];
     SDL_Surface *cadre = NULL, *titre_fenetre = NULL,*txt_1=NULL,*txt_2=NULL,*txt_nb=NULL,*flechehaut=NULL,*flechebas=NULL;

     SDL_Event event;
     SDL_Rect positionF,position;
     SDL_Color noir = {0,0,0};
     TTF_Font *basic1 = NULL, *basic2 = NULL;

     cadre = SDL_LoadBMP("cadre.bmp");
     flechehaut = IMG_Load("fleche.gif");
     flechebas = IMG_Load("fleche2.gif");
     basic1 = TTF_OpenFont("basic.ttf",75);
     basic2 = TTF_OpenFont("basic.ttf",50);

     titre_fenetre = TTF_RenderText_Solid(basic1,"Chargement",noir);
     txt_1 = TTF_RenderText_Solid(basic2,"Niveau :  ",noir);

     SDL_Texture* textureCadre = SDL_CreateTextureFromSurface(renderer, cadre);
     SDL_Texture* textureTitre = SDL_CreateTextureFromSurface(renderer, titre_fenetre);
     SDL_Texture* textureTxt1 = SDL_CreateTextureFromSurface(renderer, txt_1);
     SDL_Texture* textureTxt2 = SDL_CreateTextureFromSurface(renderer, txt_2);
     SDL_Texture* textureTxtNb = SDL_CreateTextureFromSurface(renderer, txt_nb);
     SDL_Texture* textureFlecheHaut = SDL_CreateTextureFromSurface(renderer, flechehaut);
     SDL_Texture* textureFlecheBas = SDL_CreateTextureFromSurface(renderer, flechebas);


     while(cnt)
     {
               sprintf(niv,"%ld",niveau);
               txt_nb = TTF_RenderText_Solid(basic2,niv,noir);
               SDL_DestroyTexture(textureTxtNb);
               textureTxtNb = SDL_CreateTextureFromSurface(renderer, txt_nb);

               positionF.x = LF/2-cadre->w/2;
               positionF.y = HF/2-cadre->h/2;
               positionF.w = cadre->w;
               positionF.h = cadre->h;
               //SDL_BlitSurface(cadre,NULL,ecran,&positionF);
               SDL_RenderCopy(renderer, textureCadre, NULL, &positionF);

               position.x = positionF.x+cadre->w/2-titre_fenetre->w/2;
               position.y = positionF.y+20;
               position.w = titre_fenetre->w;
               position.h = titre_fenetre->h;
               //SDL_BlitSurface(titre_fenetre,NULL,ecran,&position);
               SDL_RenderCopy(renderer, textureTitre, NULL, &position);

               position.x = positionF.x+MARGE;
               position.y += titre_fenetre->h+LIGNE;
               position.w = txt_1->w;
               position.h = txt_1->h;
               //SDL_BlitSurface(txt_1,NULL,ecran,&position);
               SDL_RenderCopy(renderer, textureTxt1, NULL, &position);
               position.x += txt_1->w;
               position.w = txt_nb->w;
               position.h = txt_nb->h;
               //SDL_BlitSurface(txt_nb,NULL,ecran,&position);
               SDL_RenderCopy(renderer, textureTxtNb, NULL, &position);
               position.x += txt_nb->w/2-flechehaut->w/2;
               position.y -= 10;
               position.w = flechehaut->w;
               position.h = flechehaut->h;
               //SDL_BlitSurface(flechehaut,NULL,ecran,&position);
               SDL_RenderCopy(renderer, textureFlecheHaut, NULL, &position);
               position.y += txt_nb->h;
               position.w = flechebas->w;
               position.h = flechebas->h;
               //SDL_BlitSurface(flechebas,NULL,ecran,&position);
               SDL_RenderCopy(renderer, textureFlecheBas, NULL, &position);

               //SDL_Flip(ecran);
               SDL_RenderPresent(renderer);

               SDL_WaitEvent(&event);
               switch(event.type)
               {
                                 case SDL_KEYUP :
                                      switch (event.key.keysym.sym)
                                      {
                                             case SDLK_ESCAPE :
                                                  cnt = 0;
                                                  niveau = -1;
                                                  break;
                                                default:
                                                    break;
                                      }
                                      break;
                                 case SDL_KEYDOWN :
                                      switch (event.key.keysym.sym)
                                      {
                                             case SDLK_RETURN :
                                                  cnt = 0;
                                                  break;
                                             case SDLK_UP :
                                                  niveau++;
                                                  break;
                                             case SDLK_DOWN :
                                                  niveau--;
                                                  if (niveau<1) niveau = 1;
                                                  break;
                                                default:
                                                    break;
                                      }
                                      break;
                                default:
                                    break;
               }
     }

     SDL_FreeSurface(cadre);
     SDL_FreeSurface(flechehaut);
     SDL_FreeSurface(flechebas);
     SDL_FreeSurface(titre_fenetre);
     SDL_FreeSurface(txt_1);
     SDL_FreeSurface(txt_2);
     SDL_FreeSurface(txt_nb);
     SDL_DestroyTexture(textureCadre);
     SDL_DestroyTexture(textureTitre);
     SDL_DestroyTexture(textureTxt1);
     SDL_DestroyTexture(textureTxt2);
     SDL_DestroyTexture(textureTxtNb);
     SDL_DestroyTexture(textureFlecheHaut);
     SDL_DestroyTexture(textureFlecheBas);
     TTF_CloseFont(basic1);
     TTF_CloseFont(basic2);
     TTF_Quit();

     return niveau;
}

void attention(SDL_Renderer *renderer,int parametre)
{
     SDL_Surface *cadre,*attention;
     SDL_Event event;
     SDL_Rect position,positionF;
     int cnt=1;

     cadre = SDL_LoadBMP("cadre.bmp");
     attention = IMG_Load("attention.gif");
     SDL_Texture *textureCadre = SDL_CreateTextureFromSurface(renderer, cadre);
     SDL_Texture *textureAttention = SDL_CreateTextureFromSurface(renderer, attention);

     while(cnt)
     {
               positionF.x = LF/2-cadre->w/2;
               positionF.y = HF/2-cadre->h/2;
               positionF.w = cadre->w;
               positionF.h = cadre->h;
               //SDL_BlitSurface(cadre,NULL,ecran,&positionF);
               SDL_RenderCopy(renderer, textureCadre, NULL, &position);

               position.x = positionF.x+2*MARGE;
               position.y = positionF.y+cadre->h/2-attention->h/2;
               position.w = attention->w;
               position.h = attention->h;
               //SDL_BlitSurface(attention,NULL,ecran,&position);
               SDL_RenderCopy(renderer, textureAttention, NULL, &position);

               //SDL_Flip(ecran);
               SDL_RenderPresent(renderer);

               SDL_WaitEvent(&event);
               switch (event.type)
               {
                      case SDL_KEYUP :
                           switch (event.key.keysym.sym)
                           {
                                  case SDLK_ESCAPE :
                                       cnt = 0;
                                       break;
                                    default:
                                        break;
                           }
                           break;
                        default:
                            break;
               }
     }

     SDL_FreeSurface(cadre);
     SDL_FreeSurface(attention);
     SDL_DestroyTexture(textureCadre);
     SDL_DestroyTexture(textureAttention);

}

