
#include"personnage.h"


void initperso2(personne* p)
{
    p->x =50;          // type de mesure
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
p->fig=0;
char nomFich[20];
int i;
for(i=0;i<20;i++)
{
    sprintf(nomFich,"image/sprite%d.png",i);
    p->sprite[i]=IMG_Load(nomFich);
}
 p->jeu.HUD_vie = IMG_Load("image/life.png");
 p->jeu.HUD_etoiles = IMG_Load("image/stars.png");

 p->jeu.vies = 3;
 p->jeu.etoiles = 0;
 p->score = 0;
}

void afficherperso2(personne* p,SDL_Surface *ecran)
{  
//SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
SDL_BlitSurface(p->sprite[p->num],NULL,ecran,&(p->position_perso));
//SDL_BlitSurface(p->vie[0],NULL,ecran,&(p->position_vie));
drawHud(p,ecran);

}

 

void Saute2(personne* p,float impulsion)
{
    p->vy = -impulsion;        
    p->etat = ETAT_AIR;            
}




void deplacerperso2(personne *p,Uint32 dt)
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

void animerperso2(personne* p)
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


void Updateperso2(personne* p,Uint8* keys)
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
void drawHud2(personne *p,SDL_Surface *screen)
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
     
     sprintf(text, "Score: %d", p->score);
    drawString(text,screen, 300,70, font);
   
     FILE *f;
		f=fopen("Score.txt","w");

		
			fprintf(f," %d \n ",p->score);

			fclose(f);
}





