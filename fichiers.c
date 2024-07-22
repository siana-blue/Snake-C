
#include "fichiers.h"

void sauvegarder(int carte[][NOMBRE_BLOCS_HAUTEUR],const int sens,long niveau)
{
     FILE* fichier = NULL;
     char nom[20];
     sprintf(nom,"niveau_%ld.lvl",niveau);
     fichier = fopen(nom,"w");
     long i,j;
     
     rewind(fichier);
     
     for (i=0;i<NOMBRE_BLOCS_HAUTEUR;i++)
     {
         for (j=0;j<NOMBRE_BLOCS_LARGEUR;j++)
         {
             fprintf(fichier,"%d",carte[j][i]);
         }
     }
     fprintf(fichier,"%d",sens);
     
     fclose(fichier);
}

int charger(int carte[][NOMBRE_BLOCS_HAUTEUR],int *sens,long niveau)
{
     FILE* fichier = NULL;
     char nom[20];
     sprintf(nom,"niveau_%ld.lvl",niveau);
     fichier = fopen(nom,"r");
     char chiffre[NOMBRE_BLOCS_HAUTEUR*NOMBRE_BLOCS_LARGEUR+2];
     long i,j;
     
     if (fichier == NULL) return 0;
     
     fgets(chiffre,NOMBRE_BLOCS_HAUTEUR*NOMBRE_BLOCS_LARGEUR+2,fichier);
     
     for (i=0;i<NOMBRE_BLOCS_HAUTEUR;i++)
     {
         for (j=0;j<NOMBRE_BLOCS_LARGEUR;j++)
         {
             switch(chiffre[i*NOMBRE_BLOCS_HAUTEUR+j])
             {
                                                      case '0' :
                                                           carte[j][i] = VIDE;
                                                           break;
                                                      case '1' :
                                                           carte[j][i] = CASEGRISE;
                                                           break;
                                                      case '3' :
                                                           carte[j][i] = SERPENT;
                                                           break;
                                                      case '4' :
                                                           carte[j][i] = CASEROSE;
                                                           break;
             }
         }
     }
     
     switch(chiffre[NOMBRE_BLOCS_HAUTEUR*NOMBRE_BLOCS_LARGEUR])
     {
                                                                 case '0' :
                                                                      *sens = HAUT;
                                                                      break;
                                                                 case '1' :
                                                                      *sens = BAS;
                                                                      break;
                                                                 case '2' :
                                                                      *sens = GAUCHE;
                                                                      break;
                                                                 case '3' :
                                                                      *sens = DROITE;
                                                                      break;
     }
     
     
     fclose(fichier);
     return 1;
}

