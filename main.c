
#include"personnage.h"

int main(int argc,char** argv)
{   
int continuer=1;
SDL_Event event; 
Uint8 *keys;
Uint32 dt=1,t_prev=1;
 int impulsion=6;
SDL_Surface* screen;
personne S ;
int i;

SDL_Init(SDL_INIT_VIDEO);



TTF_Init();
SDL_Rect position_fond;
    SDL_Init(SDL_INIT_VIDEO);
    
screen = SDL_SetVideoMode (640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
 
SDL_Surface *fond=IMG_Load("map.png"); 
 
initperso(&S);

while(continuer)
{
position_fond.x = 0;
position_fond.y =-510;
 t_prev = SDL_GetTicks();
 SDL_BlitSurface(fond,NULL,screen,&position_fond);
//SDL_Flip(screen);
 afficherperso(&S,screen);
  SDL_Flip(screen);
  
    SDL_PollEvent(&event);
        switch(event.type)
        { 
         case SDL_QUIT:
                     continuer = 0;
                     break;
         case SDL_KEYDOWN:
         switch(event.key.keysym.sym)
            {
            
             case SDLK_ESCAPE:
                        continuer = 0;
                        break;
            }
            break;
        }
    keys = SDL_GetKeyState(NULL);
if(keys[SDLK_RIGHT]==0&&keys[SDLK_LEFT]==0&&keys[SDLK_j]==0&&keys[SDLK_UP]==0&&keys[SDLK_w]==0)
{ 
  S.direction=-1;
  S.deplacement = -1;
}
if(keys[SDLK_RIGHT]==1)
 { 
    S.deplacement=1;
    S.direction=0;
}
if(keys[SDLK_j])
{ 
    S.direction=2;
}
if(keys[SDLK_w])
{
 S.direction=4;
}
if(keys[SDLK_a])
{
    S.acceleration=0;
}
if(keys[SDLK_f])
{ 
    S.vi=1;
}
if(keys[SDLK_LEFT])
{ 
 S.deplacement=0;
 S.direction=1;
}
if(keys[SDLK_UP] && S.etat == ETAT_SOL)
{  
    Saute(&S,impulsion);
    S.direction=3;
}
    animerperso(&S);
    deplacerperso(&S,dt);
    Updateperso(&S,keys);
    
    dt = SDL_GetTicks()-t_prev;     
 }


 SDL_FreeSurface(screen);
 SDL_FreeSurface(fond);
 for(i=0;i<20;i++)
 {
   SDL_FreeSurface(S.sprite[i]);
 }
for(i=0;i<4;i++)
 {
   SDL_FreeSurface(S.TEXTE[i].texte);
 }
 SDL_FreeSurface(S.jeu.HUD_etoiles);
 SDL_FreeSurface(S.jeu.HUD_vie);
    SDL_Quit();
    return 0;
}
