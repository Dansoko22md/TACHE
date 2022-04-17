
#include"personnage.h"
#include <math.h>

void initperso(personne* p)
{
    //INITIALISATIONS DES POSITIONS  
    p->TEXTE[0].position.x=5;
    p->TEXTE[0].position.y=5;
    p->TEXTE[1].position.x=5;
    p->TEXTE[1].position.y=25;
    p->TEXTE[2].position.x=5;
    p->TEXTE[2].position.y=50;
//--------------------------------
p->x =50;          
    p->y = 350;
    p->etat = ETAT_SOL;
    p->vx = p->vy = 0;
p->vitesse=0.5;
p->acceleration=0;
p->num=1;
p->direction=-1;
p->vi=0;
p->position_vie.x=50;
p->position_vie.y=50;

char Fichier[20];
int i;
for(i=0;i<17;i++)
{
    sprintf(Fichier,"image/sprite%d.png",i);
    p->sprite[i]=IMG_Load(Fichier);
}
 //p->jeu.HUD_vie = IMG_Load("image/life.png");
 //p->jeu.HUD_etoiles = IMG_Load("image/stars.png");

p->vie = 3;p->level=1;
 p->score = 0;
}

void afficherperso(personne* p,SDL_Surface *screen)
{  
//SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
SDL_BlitSurface(p->sprite[p->num],NULL,screen,&(p->position_perso));
//SDL_BlitSurface(p->vie[0],NULL,ecran,&(p->position_vie));

char score[20],vie[20],level[20];

TTF_Font *police=NULL;
SDL_Color couleur  = {50, 0, 150};
police =TTF_OpenFont("GenBasB.ttf",30);

sprintf(score, "SCORE:%d",p->score);
sprintf(vie, "VIE:%d",p->vie);
sprintf(level,"LEVEL:%d",p->level);

p->TEXTE[0].texte=TTF_RenderText_Blended(police,score, couleur);
p->TEXTE[1].texte=TTF_RenderText_Blended(police,vie, couleur);
p->TEXTE[2].texte=TTF_RenderText_Blended(police,level, couleur);

SDL_BlitSurface(p->TEXTE[0].texte,NULL,screen,&p->TEXTE[0].position);
SDL_BlitSurface(p->TEXTE[1].texte,NULL,screen,&p->TEXTE[1].position);
SDL_BlitSurface(p->TEXTE[2].texte,NULL,screen,&p->TEXTE[2].position);
TTF_CloseFont(police);

FILE *f;
		f=fopen("Score.txt","w");

		
			fprintf(f," %d \n ",p->score);

			fclose(f);
//drawHud(p,screen);

}

 

void Saute(personne* p,float impulsion)
{
    
    p->vy = -impulsion; 
    p->etat = ETAT_AIR;            
}




void deplacerperso(personne *p,Uint32 dt)
{ 
    p->dx = (0.5*p->acceleration)*dt*dt+(p->vitesse)*dt;//CALCUL DE LA DISTANCE ENGENDRE
 if(p->deplacement==1 && p->x <400)
 {
  p->x+=(p->dx);
  (p->score)++;
 }
else if(p->deplacement==0 && p->x >50)
 {
    p->x-=(p->dx);
 }
  
}

void animerperso(personne* p)
 {  
     if(p->direction==0)
     {if(p->num>=5)
      p->num=1;
      else p->num++;
     }
     else if(p->direction==1)
     {
      if(p->num==10||p->num<6||p->num>11)
       p->num=6;
       else p->num++;
      }
 else if(p->direction==2)
     {
      if(p->num==13||p->num<11||p->num>14)
       p->num=11;
       else p->num++;
      }
 else if(p->direction==3)
     {
   
       p->num=16;
    
      }
else if(p->direction==4)
     {
     
       p->num=17;
     
      }
 else 
     {
      if(p->num==15||p->num<14||p->num>16)
       p->num=14;
       else p->num++;
      }
 
      }


void Updateperso(personne* p,Uint8* keys)
{ 
    float impulsion = 6;
    float factgravite = 0.5;
    float factsautmaintenu = 3;
 
    if (p->etat == ETAT_AIR &&( keys[SDLK_UP]||keys[SDLK_z]))
    {
        factgravite/=factsautmaintenu; }
        p->vy += factgravite;


    if (p->y>380)    
    {
        p->y = 380;
        if (p->vy>0)
            p->vy = 0.0f;
        p->etat = ETAT_SOL;
    }
      
    p->x +=p->vx;
    p->y +=p->vy;

      p->position_perso.x =p->x;          
      p->position_perso.y= p->y;
 
      
}
void drawImage(SDL_Surface *image,SDL_Surface *screen, int x, int y)
{
	SDL_Rect dest;

	/* Règle le rectangle à blitter selon la taille de l'image source */
	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;

	/* Blitte l'image entière sur l'écran aux coordonnées x et y */
	SDL_BlitSurface(image, NULL,screen, &dest);
}
void drawString(char *text,SDL_Surface *screen, int x, int y, TTF_Font *font)
{
	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Color foregroundColor;

	/* On choisit d'écrire le texte en noir */
	foregroundColor.r = 0;
	foregroundColor.g = 0;
	foregroundColor.b = 0;

	/* On utilise SDL_TTF pour générer une SDL_Surface à partir d'une chaîne de caractères (string) */

	surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);

	if (surface == NULL)
	{
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());
		return;
	}

	/* On blitte cette SDL_Surface à l'écran */
	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_BlitSurface(surface, NULL,screen, &dest);

	/* On libère la SDL_Surface temporaire (pour éviter les fuites de mémoire - cf. chapitre dédié) */
	SDL_FreeSurface(surface);
}
void drawHud(personne *p,SDL_Surface *screen)
{
    //On crée une varuiable qui contiendra notre texte (jusqu'à 200 caractères, y'a de la marge ;) ).
    char text[200];
     TTF_Font *font = TTF_OpenFont("GenBasB.ttf",30);
    /* Affiche le nombre de vies en bas à droite */
    drawImage(p->jeu.HUD_vie,screen,480, 410);
    //Pour afficher le nombre de vies, on formate notre string pour qu'il prenne la valeur de la variable
    sprintf(text, "%d", p->jeu.vies);
    //Puis on utilise notre fonction créée précédemment
    drawString(text,screen, 560, 420, font);

    /* Affiche le nombre d'étoiles en haut à gauche */
    drawImage(p->jeu.HUD_etoiles,screen, 60, 60);
    sprintf(text, "%d", p->jeu.etoiles);
    drawString(text,screen, 100, 57, font);
     
     /*sprintf(text, "Score: %d", p->score);
    drawString(text,screen, 300,70, font);
   
     FILE *f;
		f=fopen("Score.txt","w");

		
			fprintf(f," %d \n ",t.score);

			fclose(f);
SDL_FreeSurface(text)*/
}

/*
void sauter(Personne *p,SDL_Surface *screen)
{//ennemi e;
#define SCREEN_W 1300
#define SCREEN_H 550
#define POS_X 500
#define POS_Y 900


double v_x, v_y, v_grav, v_jump, v_air;
double b;
if(p->done==1)
{
b=p->postion.y;
}
  p->postion.y=(-0.004*p->postion.x*p->postion.x)+1; ///lequation de la parabolle;
    /* initialisation des vitesses 
    p->v_grav =0.08;//va représenter l'attraction terrestre.
    p->v_jump =-4;//vitesse du saut

    p->v_air = 1.5;//pas trop compris se que signifiait cette variable
    p->v_x =p->v_air;//vitesse de déplacement dans les airs.
    p->v_y =p->v_jump;

  
p->postion.y=b;
    
if(p->etat==0)
{
     p->v_x=p->v_air;
        /* evolution de la position
	
	
	
        p->postion.x +=p->v_x;
        p->postion.y +=p->v_y;
 
        /* evolution de la vitesse
        p->v_y +=p->v_grav;//vitesse à la quel le personnage va latéralement monter
 
        /* collisions 
        if (p->postion.y > POS_Y)//si le perso dépace une certaine hauteur alors on fait redescendre le perso
            p->v_y =-p->v_jump;
	
        if (p->postion.x < POS_X || p->postion.x > SCREEN_W - POS_X)
            p->v_x = -p->v_x;
 
 
        /* dessin*/
        /*SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
affBackground(p->B,screen);
afficherEnnemi(p->e,screen);
        afficherPerso(p,screen);
        SDL_Flip(screen);


if(p->postion.y==b)
{
p->sauter=0;
}
}
else if(p->etat==1)
{

v_x=-v_air;
        /* evolution de la position
	
	
	
        p->postion.x += v_x;
        p->postion.y += v_y;
 
        /* evolution de la vitesse
        v_y += v_grav;//vitesse à la quel le personnage va latéralement monter
 
        /* collisions 
        if (p->postion.y > POS_Y)//si le perso dépace une certaine hauteur alors on fait redescendre le perso
            v_y =-v_jump;
	
        if (p->postion.x < POS_X || p->postion.x > SCREEN_W - POS_X)
            v_x = -v_x;
 
 
        /* dessin*/
       /* SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
affBackground(p->B,screen);
afficherEnnemi(p->e,screen);
        afficherPerso(p,screen);
        SDL_Flip(screen);

   
if(p->postion.y==b)
{
p->sauter=0;
}
}
}*/



