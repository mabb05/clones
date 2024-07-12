#include "head.h"

//this code is shit too ;((

//total blocks quantity
#define MB 60

/* declarations */
Player pl = {0};
Blocks bl[MB] = {0};
Vector2 B = {0};

/* variables */
int life = 3;

float bs = 5.0f;
float bdx = 0.0f;
bool bdy = true;
bool bdc = true;

int bly = 24;
int blx = 24;

void initlvl(void)
{
  //init:

  //ball pos
  B = (Vector2){380,300};

  //player pos, speed and points
  pl.r = (Rectangle){400,410,60,8};
  pl.s = 5.0f;
  pl.p = 0;
  
  //player life
  life = 3;

  //set all blocks pos, score and if notdestroyed
  //each 8 pixels apart, if goes out the screen, Y increases
  for (int i = 0; i<MB; i++)
  {
    bl[i].r = (Rectangle){blx,bly,60,20};
    bl[i].s = 20;
    bl[i].a = true;
    blx += 68;
    
    if (bl[i].r.x+bl[i].r.width > 800) 
    {
      bly += 24;
      blx = 24;
    }
  }
}

void updatelvl(void)
{

  //player movement
  if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) pl.r.x -= pl.s;
  if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) pl.r.x += pl.s;
  //ball follow and start
  if (IsKeyPressed(KEY_SPACE) && bdc) {bdy = false; bdc = false;}

  //player boundaries
  if (pl.r.x < 10) pl.r.x = 10;
  else if (pl.r.x > (844 - pl.r.width)) pl.r.x = (844 - pl.r.width);

  //if bdc, follow player
  //else: start game, launches ball
  if (bdc)
  {
    B.x = pl.r.x + (pl.r.width/2);
    B.y = pl.r.y - pl.r.height*2;
  }
  else 
  {
    if (bdy) B.y += bs;
    else B.y -= bs;
  }

  //move ball X
  B.x += bdx;

  //revert direction if collide both sides
  if (B.x < 0 || B.x > 854) bdx = -bdx;

  //if touch top revert Y
  //else if bottom, reset game, -1 life
  if (B.y < 5) bdy = true;
  else if (B.y > 500)
  {
    life--;
    bdc = true;
    bdx = 0;
  }

  //player and ball collision (measuring where it collides)
  if (B.x >= pl.r.x-5 && B.x <= pl.r.x+65 && B.y > pl.r.y && B.y < pl.r.y+5) 
  {
    bdy = false;
    if (B.x >= pl.r.x-5 && B.x <= pl.r.x+15) bdx = -3.5f;
    if (B.x > pl.r.x+15 && B.x < pl.r.x+30) bdx = -2.0f;
    if (B.x > pl.r.x+30 && B.x < pl.r.x+45) bdx = 2.0f;
    if (B.x >= pl.r.x+45 && B.x <= pl.r.x+65) bdx = 3.5f;
  }

  //for all blocks, check collision, if it do: destroy, revert ball, add point
  for (int i = 0; i<MB; i++)
  {
    if (bl[i].a)
    {
      if (CheckCollisionPointRec(B,bl[i].r))
      {
        bl[i].a = false;
        bdy = true;
        pl.p++;
      }
    }
  }

  //when out of lifes, close game
  if (life <= 0) CloseWindow();
}

void drawlvl(void)
{
  //background
  ClearBackground((Color){2,2,22,255});

  //draw blocks
  for (int i = 0; i<MB; i++) if (bl[i].a) DrawRectangleRec(bl[i].r,WHITE);

  //draw player and ball
  DrawRectangleRec(pl.r,WHITE);
  DrawCircleV(B,5.0f,WHITE);
  
  //draw hud, score and life
  DrawText(TextFormat("%d",pl.p),20,430,40,YELLOW);
  DrawText(TextFormat("%d",life),820,430,40,RED);
}
