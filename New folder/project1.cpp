#include <iostream>
#include <cstdlib>
#include "SDL/SDL.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "SDL/SDL_image.h"
#include <vector>
#include <math.h>
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
SDL_Event event;
Mix_Music* music;
Mix_Chunk* cash = NULL;
Mix_Chunk* death1 = NULL;
Mix_Chunk* los = NULL;
Mix_Chunk* victory = NULL;
int squars[50][30]={0};
SDL_Surface* screen=SDL_SetVideoMode(1000,600,32,0);
SDL_Surface* picwin=IMG_Load("win.jpg");
SDL_Surface* piclose=IMG_Load("lose.jpg");
SDL_Rect pic={0,0,0,0};
SDL_Surface* start=IMG_Load("back.jpg");
SDL_Surface* image1=IMG_Load("1.jpg");
SDL_Surface* image2=IMG_Load("2.jpg");
SDL_Surface* image7=IMG_Load("bonus.jpg");
SDL_Surface* image3=IMG_Load("3.jpg");
SDL_Surface* image4=IMG_Load("4.jpg");
SDL_Surface* image5=IMG_Load("5.jpg");
SDL_Surface* image6=IMG_Load("tower.jpg");
using namespace std;
bool win;
class Map
{
   public:     
      int draw()
      {
	 SDL_WM_SetCaption( "Tower Defense", NULL );
	 SDL_BlitSurface(start,NULL,screen,&pic);
	 SDL_Flip(screen);
	 boxRGBA(screen,0,0,1001,601,0,0,0,255);    	 
	 while(1)
	 if(SDL_PollEvent(&event))
	      {
		  if(event.type==SDL_QUIT){
  		     SDL_Quit();
		     break;}
		  if(event.type==SDL_MOUSEBUTTONDOWN)
  		    {
			if(event.button.button==SDL_BUTTON_LEFT)
			  {boxRGBA(screen,0,0,250,249,0,150,0,255);
	 		  boxRGBA(screen,250,0,449,449,0,150,0,255);
	                  boxRGBA(screen,450,0,900,49,0,150,0,255);
	                  boxRGBA(screen,900,0,1000,349,0,150,0,255);
	                  boxRGBA(screen,850,250,900,349,0,150,0,255);
	                  boxRGBA(screen,700,250,850,350,0,150,0,255);
	                  boxRGBA(screen,700,350,849,499,0,150,0,255);
	                  boxRGBA(screen,0,300,199,600,0,150,0,255);
	                  boxRGBA(screen,200,500,649,600,0,150,0,255);
         		  boxRGBA(screen,649,550,1000,600,0,150,0,255);
	 		  boxRGBA(screen,900,400,1000,550,0,150,0,255);
	 		  boxRGBA(screen,500,100,649,500,0,150,0,255);
	 		  boxRGBA(screen,650,100,849,199,0,150,0,255);
			  SDL_Rect load7={35,3,0,0};
			  SDL_BlitSurface(image7,NULL,screen,&load7);
	 		  return 1;}
		    }   
	        }
	}
};
class Enemy
{
   public:
      int ex;
      int ey;
      int di;
      int dj;
      int health;
      void draw(int x,int y,int z)
      {
	   if(z==0)
     	     boxRGBA(screen,x,y,x+49,y+49,0,0,0,255);
	   else if(z==1)
           {
             SDL_Rect load1={x,y,0,0};
	     SDL_BlitSurface(image1,NULL,screen,&load1);
	   }
	   else if(z==2)
           {
             SDL_Rect load2={x,y,0,0};
	     SDL_BlitSurface(image2,NULL,screen,&load2);
	   }
	   else if(z==3)
           {
             SDL_Rect load3={x,y,0,0};
	     SDL_BlitSurface(image3,NULL,screen,&load3);
	   }
	   else if(z==4)
           {
             SDL_Rect load4={x,y,0,0};
	     SDL_BlitSurface(image4,NULL,screen,&load4);
	   }
	   else if(z==5)
           {
             SDL_Rect load5={x,y,0,0};
	     SDL_BlitSurface(image5,NULL,screen,&load5);
	   }
      }	
};
class Tower
{
   public:
      int x;
      int y;
      void settower(int posx,int posy)
      {
      	   SDL_Rect load={x,y,0,0};
	   SDL_BlitSurface(image6,NULL,screen,&load);
      }
};
class Game
{
    public:
      vector <Enemy> enemy;
      int number;
      int money;
      int level;
      vector <Tower> gametower;
      void first()
         {
            for(int i=0;i<enemy.size();i++)
	       {
                   enemy[i].health=599;
		   enemy[i].di=-1;
		   enemy[i].dj=0;
	       }
	    
	    
         }
	void play()
	{
	    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,0);
	    death1 = Mix_LoadWAV( "death.wav" );
            victory = Mix_LoadWAV( "victory.wav" );
    	    los = Mix_LoadWAV( "lose.wav" );
	    cash = Mix_LoadWAV( "cash.wav" );
	    music=Mix_LoadMUS("music.wav");    
	    Mix_PlayMusic(music,-1);}      
	void click()
         {
	    int mousex,mousey;
	    if(SDL_PollEvent(&event))
	      {
		  if(event.type==SDL_QUIT)
  		     SDL_Quit();
		  if(event.type==SDL_MOUSEBUTTONDOWN)
  		    {
			if((event.button.button==SDL_BUTTON_LEFT)&&(money>=5))
			  {
			      mousex=event.button.x;
			      mousey=event.button.y;
	 		      mousex=(mousex/50)*50;
	 		      mousey=(mousey/50)*50;
			      Tower b;
			      b.x=mousex;
			      b.y=mousey; 
			      b.settower(b.x,b.y);
			      gametower.push_back(b);
			      printbonus(0,150,0);
			      money-=5;
			      printbonus(0,0,150);
			      Mix_PlayChannel( -1, cash, 0 );
			      
			  }
		    }   
	        
	      }
         }
      void attack()
         {
	    for(int i=0;i<gametower.size();i++)
		{
		    for(int j=0;j<enemy.size();j++)
			if(sqrt((enemy[j].ex-gametower[i].x)*(enemy[j].ex-gametower[i].x)+(enemy[j].ey-gametower[i].y)*(enemy[j].ey-gametower[i].y))<150 && enemy[j].health>95)
{
   enemy[j].health--;
   break;
}
	    	}
	 }
     void move()
         {
	     for(int i=0;i<enemy.size();i++)
		{
		    enemy[i].draw(enemy[i].ex,enemy[i].ey,0);
		    enemy[i].ex+=enemy[i].di;
		    enemy[i].ey+=enemy[i].dj;
		    enemy[i].draw(enemy[i].ex,enemy[i].ey,(enemy[i].health)/100);
		    
		if(enemy[i].ex==850 && enemy[i].ey==350){
		enemy[i].di=0;
		enemy[i].dj=1;}
		else if(enemy[i].ey==500 && enemy[i].ex==850){
		enemy[i].di=-1;
		enemy[i].dj=0;}
		else if(enemy[i].ex==650 && enemy[i].ey==500){
		enemy[i].di=0;
		enemy[i].dj=-1;}
		else if(enemy[i].ey==200 && enemy[i].ex==650){
		enemy[i].di=1;
		enemy[i].dj=0;}
		else if(enemy[i].ex==850 && enemy[i].ey==200){
		enemy[i].di=0;
		enemy[i].dj=-1;}
		else if(enemy[i].ex==850 && enemy[i].ey==50){
		enemy[i].di=-1;
		enemy[i].dj=0;}
		else if(enemy[i].ex==450 && enemy[i].ey==50){
		enemy[i].di=0;
		enemy[i].dj=1;}
		else if(enemy[i].ex==450 && enemy[i].ey==450){
		enemy[i].di=-1;
		enemy[i].dj=0;}
		else if(enemy[i].ex==200 && enemy[i].ey==450){
		enemy[i].di=0;
		enemy[i].dj=-1;}
		else if(enemy[i].ex==200 && enemy[i].ey==250){
		enemy[i].di=-1;
		enemy[i].dj=0;}				
		}
	 }
     void setenemy(int t)
    	 {
	    int r=1000;
	    for(int i=0;i<t;i++)
		{
		   Enemy c;
		   enemy.push_back(c);
		}
	    for(int i=0;i<enemy.size();i++)
		{
		    enemy[i].ex=r;
		    enemy[i].ey=350;
		    r+=120;
		}
	 }
     void check()
	 {
	     int d=1;
	     for(int i=0;i<enemy.size();i++)
		if(enemy[i].health>95)
		   d=0;
			
	     if(enemy[enemy.size()-1].ex<-50)
		d=1;
	     if(d==1 && level>0)
	       {
		  level--;
		  setenemy(5);
		  first();
	       }
	 }
     bool finish()
 	{
	    if(level==0)
	      {
		  win=1;
		  return 0;
	      }
	    for(int i=0;i<enemy.size();i++)
		if((enemy[i].ex==1)&&(enemy[i].health>=100))
                  {
		     number--;
                     if(number==0){
		        win=0; 
			return 0;}
		  }
            return 1;       
        } 
    void bonus()
	{                  
	      
	    for(int i=0;i<enemy.size();i++)
		if(enemy[i].health==95){
		  Mix_PlayChannel( -1, death1, 0 );
		  printbonus(0,150,0);
		  money++;
		  printbonus(0,0,150);
		  enemy[i].health=-1;}
	}
    void result()
	{
		if(win==1){
		SDL_BlitSurface(picwin,NULL,screen,&pic);
		SDL_Flip(screen);
		Mix_PauseMusic();
		Mix_PlayChannel( -1, victory, 0 );
        	SDL_Delay(5000);}
    if(win==0){
		SDL_BlitSurface(piclose,NULL,screen,&pic);
		Mix_PauseMusic();		
		Mix_PlayChannel( -1, los, 0 );
		SDL_Flip(screen);
        	SDL_Delay(5000);}}
    void printbonus(int a,int b,int c)
	{
	    if(money<10)
	       characterRGBA(screen,60,10,money+48,a,b,c,255);
	    if(money>=10)
	     {
		 characterRGBA(screen,60,10,money/10+48,a,b,c,255);
		 characterRGBA(screen,70,10,money%10+48,a,b,c,255);
	     }
	}
    
    
};
int main()
{  
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Map map;
    Game game;
    map.draw();
    game.play();
    game.setenemy(5);
    game.first();
    game.level=4;
    game.number=5;
    game.money=15;
    game.printbonus(0,0,150);
    while(game.finish())
    {   
        game.move();
	game.click();
	game.attack();
	game.bonus();
        game.check();       
        SDL_Flip(screen);
        SDL_Delay(2);

	
    }
	game.result();
	return 0;
        
}
