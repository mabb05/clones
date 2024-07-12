#include <raylib.h>

//player structure
typedef struct Player {
  Rectangle r;
  float s;
  int p;
} Player;

//blocks structure
typedef struct Blocks {
  Rectangle r;
  int s;
  bool a;
} Blocks;

//window size, C* is the default program resolution
static int WID = 854;
static const int CWID = 854;
static int HEI = 480;
static const int CHEI = 480;

//volume (unused)
static float vol = 0.5f;

//level system
typedef enum GS {LVL,ERROR} GS;
extern GS screen;

//font (unused)
extern Font fMain;

void exitgame(void);

//start update and draw level functions
void initlvl(void);

void updatelvl(void);

void drawlvl(void);
