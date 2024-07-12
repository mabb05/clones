#include "head.h"

//max enemy, blocks and ammo
#define ME 100
#define MB 50
#define MAXAMMO 50

/* declarations */
Player pl = {0};
Enemy ene[ME] = {0};
Bullet bul[MB] = {0};

Camera2D cam = {0};

/* variables */
float ENES = 5.0f;
int fene = 0;
int fENES = 0;
int shootrate = 0;
int life = 10;
int bullets = MAXAMMO;
int score = 0;
bool notover = true;
bool canshoot = true;

void initlvl(void)
{
  //init player pos, size, speed and points
  pl.r = (Rectangle){427,400,20,20};
  pl.s = 4.0f;
  pl.p = 0;

  //camera settings (doesnt really make a diff)
  cam.target = (Vector2){pl.r.x,pl.r.y-150};
  cam.offset = (Vector2){WID/2.0f,HEI/2.0f};
  cam.rotation = 0.0f;
  cam.zoom = 1.0f;

  //init bullets (pos out of the map, inactive and its speed)
  for (int i=0; i<MB; i++)
  {
    bul[i].p = (Vector2){-20,-20};
    bul[i].a = false;
    bul[i].s = 20.0f;
  }

  //set enemy initial pos, speed and life
  for (int i=0; i<ME; i++)
  {
    ene[i].r = (Rectangle){GetRandomValue(0,WID),GetRandomValue(-550,-50),20,20};
    ene[i].s = 1;
    ene[i].l = 1;
  }
}

void updatelvl(void)
{
  //while game is not over
  if (notover)
  {
    //shoot bullets, holding space, at a rate
    if (IsKeyDown(KEY_SPACE))
    {
      shootrate += 5;
      for (int i=0; i<MB; i++)
      {
        if (!bul[i].a && shootrate % 40 == 0 && canshoot)
        {
          bul[i].p.y = pl.r.y;
          bul[i].p.x = pl.r.x+8;
          bul[i].a = true;
          bullets -= 1;
          break;
        }
      }
    }
    
    //reach 0, refill ammo, cant shoot until refilled
    if (bullets <= 0) canshoot = false;
    if (!canshoot)
    {
      if (bullets < MAXAMMO) bullets++;
      else if (bullets == MAXAMMO) canshoot = true;
    }

    //collision enemy with player = -1 health
    //collision enemy with bullet = kills both
    for (int i=0; i<MB; i++)
    {
      for (int a=0; a<ME; a++)
      {
        if (ene[a].l > 0)
        {
          if (CheckCollisionPointRec(bul[i].p,ene[a].r))
          {
            bul[i].a = false;
            ene[a].l--;
            score += 80;
          }
          if (CheckCollisionRecs(pl.r,ene[a].r))
          {
            life -= 1;
            ene[a].l = 0;
          }
        }
      }

      //ball direction
      if (bul[i].a) bul[i].p.y -= bul[i].s;

      //destroy bullet outside
      if (bul[i].p.y > 490 || bul[i].p.y < -10) bul[i].a = false;
    }

    //player movement 
    if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) pl.r.x -= pl.s;
    if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) pl.r.x += pl.s;
    
    //player boundaries
    if (pl.r.x > 825) pl.r.x = 825;
    else if (pl.r.x < 5) pl.r.x = 5;
    
    //set enemy speed, wins point when enemy goes bottom and reset it
    for (int i=0; i<ME; i++)
    {
      ene[i].r.y += ENES;
      if (ene[i].r.y > 500)
      {
        score += 1;
        ene[i].r = (Rectangle){GetRandomValue(0,WID),GetRandomValue(-550,-50),GetRandomValue(15,30),GetRandomValue(15,30)};
        ene[i].l = 1;
      }
    }

    //increase enemy speed with time
    fENES++;
    if (fENES == 30) 
    {
      ENES += 0.05f;
      fENES = 0;
    }

    //end game if no lives
    if (life <= 0) notover = false;
  }
  //dead menu, reset
  else
  {
    if (IsKeyPressed('R'))
    {
      initlvl(); 
      notover = true;
      life = 10;
      score = 0;
      ENES = 5.0f;
    }
  }
}

void drawlvl(void)
{
  //background
  ClearBackground((Color){2,2,22,255});

  //draw all in camera
  BeginMode2D(cam);
    
    //draw it all in gameplay
    if (notover)
    {
      DrawRectangleRec(pl.r,WHITE);
      for (int i=0; i<MB; i++) if (bul[i].a) DrawRectangle(bul[i].p.x-2,bul[i].p.y,4,15,ORANGE);
      for (int i=0; i<ME; i++) if (ene[i].l > 0) DrawRectangle(ene[i].r.x,ene[i].r.y,20,20,RED);
    }

    //draw game over menu
    else 
    {
      DrawText("DEAD",250,150,40,WHITE);
      DrawText("go again?",250,200,40,WHITE);
      DrawText("r - restart",250,300,40,GREEN);
      DrawText("hold space, A & D",250,400,20,WHITE);
    }
    
  EndMode2D();
  
  //draw hud
  if (notover)
  {
    DrawText(TextFormat("%d",life),20,20,40,GREEN);
    DrawText(TextFormat("%d",bullets),790,20,40,YELLOW);
    DrawText(TextFormat("%d",score),(WID/2)-(MeasureText(TextFormat("%d",score),40)/2),20,40,ORANGE);
  }
}
