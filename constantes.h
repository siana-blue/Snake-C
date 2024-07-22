/*
  Name: constantes.h
  Copyright: 2007
  Author: Disclosis
  Date: 24/03/07 18:20
  Description: constantes pour Snake
               HF : hauteur fenêtre
               LF : largeur fenêtre
               MARGE : espace entre bord fenêtre et texte
               LIGNE : espace entre deux lignes
*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define NOMBRE_BLOCS_LARGEUR 50
#define NOMBRE_BLOCS_HAUTEUR 50
#define TAILLE_BLOC 18
#define LF NOMBRE_BLOCS_LARGEUR*TAILLE_BLOC
#define HF NOMBRE_BLOCS_HAUTEUR*TAILLE_BLOC
#define MARGE 10
#define LIGNE 20
#define SOUND_VOLUME 0.8

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <//FMOD.h>

//FMOD_SYSTEM *//FMODsystem;

enum {HAUT,BAS,GAUCHE,DROITE};
enum {VIDE=0,CASEGRISE,POMME,SERPENT,CASEROSE,CORPS,QUEUE,BOMBE};

typedef struct Compteur Compteur;
struct Compteur
{
       int dir;
       int valeur;
};

typedef struct Mouvement Mouvement;
struct Mouvement
{
       int dir;
       int dirQ;
       SDL_Rect posT;
       SDL_Rect posQ;
       Compteur cmpt[2500];
       int carte[NOMBRE_BLOCS_LARGEUR][NOMBRE_BLOCS_HAUTEUR];
       int perdu;
       int pomme;
       long tailleSerpent;
       int fleche;
       //FMOD_SOUND *avance;
       //FMOD_SOUND *croc;
};

typedef struct Pose Pose;
struct Pose
{
       int pomme;
       int carte[NOMBRE_BLOCS_LARGEUR][NOMBRE_BLOCS_HAUTEUR];
       long x;
       long y;
       int debut;
       //FMOD_SOUND *son_pomme;
};

SDL_Texture* createTextureFromFile(SDL_Renderer* renderer, const char* fileName);

#endif
