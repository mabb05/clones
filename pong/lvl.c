#include "head.h"

/* declarations */
Player pl1 = {0};
Player pl2 = {0};

Vector2 B = {250,250};

/* variables */
bool dx = false;
float dy = 0.25f;
float offset = 0.01f;
float bs = 1.0f;

void initlvl(void)
{
 //players start position, speed and points
 pl1.r = (Rectangle){20,230,10,40};
 pl1.s = 15.0f;
 pl1.p = 0;
  
 pl2.r = (Rectangle){470,230,10,40};
 pl2.s = 15.0f;
 pl2.p = 0;
}

void updatelvl(void)
{
  //ball speed always moving
  bs += 0.01f;

  //moving players
  if (IsKeyDown('W')) pl1.r.y -= pl1.s;
  if (IsKeyDown('S')) pl1.r.y += pl1.s;
  
  if (IsKeyDown(KEY_UP)) pl2.r.y -= pl2.s;
  if (IsKeyDown(KEY_DOWN)) pl2.r.y += pl2.s;

  //cheated bot lol
  //pl2.r.y = B.y;

  //players boundaries
  if (pl1.r.y < 0.0f) pl1.r.y = 0.0f;
  else if (pl1.r.y > 460.0f) pl1.r.y = 460.0f;

  if (pl2.r.y < 0.0f) pl2.r.y = 0.0f;
  else if (pl2.r.y > 460.0f) pl2.r.y = 460.0f;

  //set X direction to ball, - = <-, + = ->
  if (!dx) B.x -= bs;
  else if (dx) B.x += bs;

  //the rest is just plain poop. proceed with caution
  B.y += bs*dy;
  if (B.y > 492) dy = -0.25f;
  else if (B.y < 8) dy = 0.25f;

  if (B.x < 35 && B.y > pl1.r.y - 8 && B.y < pl1.r.y + 40)
  {
    dx = true;
    if (B.y < pl1.r.y + 5) dy = -1.00f; 
    if (B.y > pl1.r.y + 5 && B.y < pl1.r.y + 15) dy = -0.40f; 
    if (B.y > pl1.r.y + 15 && B.y < pl1.r.y + 20) dy = -0.15f; 
    if (B.y > pl1.r.y + 20 && B.y < pl1.r.y + 25) dy = 0.15f; 
    if (B.y > pl1.r.y + 25 && B.y < pl1.r.y + 35) dy = 0.40f; 
    if (B.y > pl1.r.y + 35) dy = 1.00f; 
  }
  
  if (B.x > 455 && B.y > pl2.r.y - 8 && B.y < pl2.r.y + 40)
  {
    dx = false;
    if (B.y < pl2.r.y + 5) dy = -1.00f; 
    if (B.y > pl2.r.y + 5 && B.y < pl2.r.y + 15) dy = -0.40f; 
    if (B.y > pl2.r.y + 15 && B.y < pl2.r.y + 20) dy = -0.15f; 
    if (B.y > pl2.r.y + 20 && B.y < pl2.r.y + 25) dy = 0.15f; 
    if (B.y > pl2.r.y + 25 && B.y < pl2.r.y + 35) dy = 0.40f; 
    if (B.y > pl2.r.y + 35) dy = 1.00f; 
  }

  if (B.x < -15) 
  {
    B.x = 250;
    B.y = 250;
    bs = 5.0f;
    pl2.p++;
    dx = true;
    dy = 0.25f;
  }
  
  if (B.x > 515) 
  {
    B.x = 250;
    B.y = 250;
    bs = 5.0f;
    pl1.p++;
    dx = false;
    dy = 0.25f;
  }

}

void drawlvl(void)
{
  //background
  ClearBackground(BLACK);

  //draw players and ball
  DrawRectangleRec(pl1.r,WHITE);
  DrawRectangleRec(pl2.r,WHITE);
  DrawCircle(B.x,B.y,8.0f,WHITE);

  //points hud
  DrawText(TextFormat("%d",pl1.p),210,20,40,WHITE);
  DrawText(TextFormat("%d",pl2.p),270,20,40,WHITE);
}
