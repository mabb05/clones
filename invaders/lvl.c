#include "head.h"

//same code from space shooter game

//max enemy, blocks and ammo
#define ME 30
#define MB 50

/* declarations */
Player pl = {0};
Enemy ene[ME] = {0};
Bullet bul[MB] = {0};
Bullet enu[MB] = {0};
Camera2D cam = {0};

/* variables */
float ENES = 5.0f;
int fene = 0;
int fENES = 0;
int score = 0;
int epo = 40;
int epy = 80;
int enuf = 0;
int life = 3;
float speed = 2;
bool notover = true;

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
  
  for (int i=0; i<MB; i++)
  {
    enu[i].p = (Vector2){-20,-20};
    enu[i].a = false;
    enu[i].s = 20.0f;
  }

  //set enemy initial pos, speed and life
  //now separated each 40 pixel, goes Y down
  //if outside screen
  for (int i=0; i<ME; i++)
  {
    ene[i].r = (Rectangle){-(ME*40)+epo,epy,20,20};
    epo += 40;
    ene[i].s = 1;
    ene[i].l = 1;
  }
}

void updatelvl(void)
{
  //gameplay
  if (notover)
  {
    //shooting, now infinite and slow rate
    if (IsKeyPressed(KEY_SPACE))
    {
      for (int i=0; i<MB; i++)
      {
        if (!bul[i].a)
        {
          bul[i].p.y = pl.r.y;
          bul[i].p.x = pl.r.x+8;
          bul[i].a = true;
          break;
        }
      }
    }

    //im tired of commenting, but aint hard so u will be good
    enuf++;
    for (int i=0; i<MB; i++)
    {
      for (int a=0; a<ME; a++)
      {
        if (ene[a].l > 0)
        {
          if (CheckCollisionPointRec(bul[i].p,ene[a].r) && bul[i].a)
          {
            bul[i].a = false;
            score += 80;
            ene[a].l = 0;
            speed += 0.1f;
          }
          if (CheckCollisionRecs(pl.r,ene[a].r))
          {
            life--;
            ene[a].l = 0;
          }

        if (enuf == 10)
        {
          if (!enu[i].a)
          {
            enu[i].p.y = ene[i].r.y;
            enu[i].p.x = ene[i].r.x+8;
            enu[i].a = true;
            break;
          }
          enuf = 0;
        }
        }
      }
      
      if (bul[i].a)
        bul[i].p.y -= bul[i].s;
      
      if (bul[i].p.y < -10)
        bul[i].a = false;
      
    }

    //player movement
    if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) pl.r.x -= pl.s;
    if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) pl.r.x += pl.s;
    
    //player bounds
    if (pl.r.x > 825) pl.r.x = 825;
    else if (pl.r.x < 5) pl.r.x = 5;
    
    for (int i=0; i<ME; i++)
    {
      if (ene[i].l <= 0)
      {
        ene[i].r = (Rectangle){ene[i].r.x+epo,epy,20,20};
      }
      ene [i].r.x += speed;
      if (ene[i].r.x > 850) 
      {
        ene[i].r.x = -60;
        ene[i].r.y += epy;
      }
    }

    //enemy speed (unused, from earlier game)
    fENES++;
    if (fENES == 30) 
    {
      ENES += 0.05f;
      fENES = 0;
    }
    
    //end game when no lifes
    if (life <= 0) notover = false;

    //win game
    if (score == 2400) CloseWindow();
  }
  else
  {
    //reset game
    if (IsKeyPressed('R'))
    {
      initlvl(); 
      notover = true;
      score = 0;
      life = 3;
    }
  }
}

void drawlvl(void)
{
  //background
  ClearBackground((Color){2,2,22,255});

  BeginMode2D(cam);
    
    if (notover)
    {
      //draw it all
      DrawRectangleRec(pl.r,WHITE);
      for (int i=0; i<MB; i++) if (bul[i].a) DrawRectangle(bul[i].p.x-2,bul[i].p.y,4,15,ORANGE);
      for (int i=0; i<ME; i++) if (ene[i].l > 0) DrawRectangle(ene[i].r.x,ene[i].r.y,20,20,RED);
    }
    else 
    {
      //unused restart screen
      DrawText("DEAD",250,150,40,WHITE);
      DrawText("again?",250,200,40,WHITE);
      DrawText("r - restart",250,300,40,GREEN);
    }
  EndMode2D();
  
  if (notover)
  {
    //hud
    DrawText(TextFormat("%d",score),(WID/2)-(MeasureText(TextFormat("%d",score),40)/2),10,40,ORANGE);
    DrawText(TextFormat("%d",life),20,10,40,GREEN);
  }
}
