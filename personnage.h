#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


#define DROITE 1
#define GAUCHE 0

#define ETAT_SOL 0
#define ETAT_AIR 1
struct texte
{
SDL_Surface *texte;
SDL_Rect position;
char score[20];
char vie[20];
char temps[20];
};
typedef struct texte texte; //STRUCTURE PERMETTANT DE GERER LES TEXTES QUI DOIVENT ETRE AFFCIHÉS COMME "SCORE,VIE,OU TEMPS.....);

typedef struct Gestion
{

    SDL_Surface *screen;
    //HUD
    SDL_Surface *HUD_vie, *HUD_etoiles;
    int vies, etoiles;
} Gestion;
typedef struct
{   
    Gestion jeu;
    texte TEXTE[3];
    float dx;
    int num,vi;
    float x,y;
    float vx,vy;
    SDL_Rect position_perso,position_vie;
    SDL_Surface *sprite[20];
    int etat;
    float acceleration,vitesse;
    int deplacement;
    int direction;
    int score,vie,level;
} personne;

//LES FONCTIONS DEVELOPPEES
void initperso(personne* p);
void afficherperso(personne* p,SDL_Surface *screen);
void deplacerperso(personne *p,Uint32 dt);
void Saute(personne* p,float impulsion);
void animerperso(personne* p);
void Updateperso(personne* p,Uint8* keys);

//---------------------------------------------
void initPerso2(personne * p);
void afficherPerso2(personne *p, SDL_Surface * screen);
void deplacerPerso2(personne *p,Uint32 dt);
void animerPerso2(personne* p);
void updatePerso2(personne *p);
void liberer2(personne *p);
void sauter2(personne *p,SDL_Surface *screen);

void multi_joeur(SDL_Surface *screen);
//---------------------------------------------
void drawImage(SDL_Surface *image,SDL_Surface *screen, int x, int y);
void drawString(char *text,SDL_Surface *screen, int x, int y, TTF_Font *font);
void drawHud(personne *p,SDL_Surface *screen);

#endif
