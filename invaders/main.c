#include "head.h"

//level switcher
GS screen = LVL;
//cursor (unused)
Texture2D cursor = {0};
//render texture for window maximize
RenderTexture2D RT = {0};
//window icon
Image icon = {0};

void exitgame(void)
{
    //unload and free ram
    UnloadRenderTexture(RT);
    UnloadImage(icon);
    CloseAudioDevice();
    CloseWindow();
}

int main (void)
{
  //set no logs
  SetTraceLogLevel(LOG_NONE);
  //start window
  InitWindow(WID,HEI,"invaders");
  //resize window
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  //framerate
  SetTargetFPS(60);
  //remove exit key
  SetExitKey(KEY_NULL);
  //start audio (unused_
  InitAudioDevice();

  //unused
  Image icon = LoadImage("icon.h");
  ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
  SetWindowIcon(icon);
  cursor = LoadTexture("data/cursor.png");

  //set rt
  RT = LoadRenderTexture(WID,HEI);

  //fullscreen state
  bool fullscreen = false;

  //init game
  initlvl();

  //fast fix for not extracting full game
  //int errortime = 0;
  //if (!FileExists("data/fmain.ttf")) screen = ERROR;
  
  while (!WindowShouldClose())
  {
    //update rt
    Rectangle rt1 = {0,0,RT.texture.width,-RT.texture.height}; 
    Rectangle rt2 = {0,0,GetScreenWidth(),GetScreenHeight()}; 
    Vector2 rtv = {0,0};

    //fullscreen stuff
    if (IsKeyPressed(KEY_F11) && !fullscreen) 
    {
      fullscreen = true;
      SetWindowSize(GetMonitorWidth(GetCurrentMonitor()),GetMonitorHeight(GetCurrentMonitor()));
      SetWindowPosition(0,0);
      SetWindowState(FLAG_WINDOW_UNDECORATED);
    }
    else if (IsKeyPressed(KEY_F11) && fullscreen) 
    {
      fullscreen = false;
      SetWindowSize(CWID,CHEI);
      SetWindowPosition(GetMonitorWidth(GetCurrentMonitor())/2-(WID/2),GetMonitorHeight(GetCurrentMonitor())/2-(HEI/2));
      ClearWindowState(FLAG_WINDOW_UNDECORATED);
    }
    
    //update lvls
    switch (screen)
      {
        case ERROR:
          //errortime++;
          //if (errortime == 280) CloseWindow();
          break;

        case LVL:
         updatelvl();
         break;
        
       default: break;
     }

    //draw everything inside rt
    BeginTextureMode(RT);

      //unused cursor
      //HideCursor();
      //DrawTexture(cursor,GetMouseX(),GetMouseY(),WHITE);

      switch (screen)
      {
        case ERROR:
          //error lvl for "fast fix"
          ClearBackground(RED);
          DrawText("please extract all files!",300,360,24,WHITE); 
          break;

        case LVL:
          drawlvl();
          break;
        
        default: break;
      }

    EndTextureMode();
    
    //draw it all (rt)
    BeginDrawing();
      
      DrawTexturePro(
          RT.texture,
          rt1, 
          rt2,
          rtv,
          0,
          WHITE);
      
    EndDrawing();
  }

  //exit and go away
  exitgame();

  return 0;
}
