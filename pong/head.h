//raylib header
#include <raylib.h>

//player structure
typedef struct Player {
  Rectangle r;
  float s;
  int p;
} Player;

//window size, C* is the default program resolution
static int WID = 500;
static const int CWID = 500;
static int HEI = 500;
static const int CHEI = 500;

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
