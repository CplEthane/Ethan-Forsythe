#include "huc.h"


#define PACSTARTRIGHT 0x6000
#define PACRANIM1     0x6100
#define PACRANIM2     0x6200
#define PACRANIM3     0x6300

#define PACSTARTLEFT  0X6400
#define PACLANIM1     0x6500
#define PACLANIM2     0x6600
#define PACLANIM3     0x6700

#define PACSTARTUP    0X6800
#define PACUANIM1     0x6900
#define PACUANIM2     0x7000
#define PACUANIM3     0x7100

#define PACSTARTDOWN  0x7200
#define PACDANIM1     0x7300
#define PACDANIM2     0x7400
#define PACDANIM3     0x7500

#define _o_   0  // dot-populated corridor
#define ___   1  
#define _B_   2 // corridor that is always blank from dots
#define _Bp   3 // Pac-starting tile left
#define pB_   4 // Pac-starting tile right
#define RXD   5 // Red (red) scatter target, blank
#define PNK   6 // Pink (Pinky) scatter target, blank
#define BLU   7 // Blue (Inky)  scatter target, blank
#define ORA   8 // Orange (Clyde) scatter target, blank
#define RUL   9  // rectangle, upper left
#define HLN   10 // regular single horizontal line border
#define BLK   11 // black, blank
#define RUR   12 // rectangle, upper right
#define BLL   13 // border, lower left
#define BLR   14 // border, lower right
#define RLL   15 // rectangle, lower left
#define RLR   16 // rectangle, lower right
#define ULM   17  // upper left middle border
#define _P_   18 // power pellet space (designated)
#define BUN   19 // lower outside border
#define BLN   20 // lower leftturn border
#define BRN   21 // lower rightturn border ****
#define RVBOR 22
#define GUR   23 // Ghost house upper right
#define GUL   24 // Ghost house upper left
#define GLR   25 // Ghost house lower right
#define GLL   26 // Ghost house lower left
#define GDL   27 // Ghost house door left jamb
#define GDR   28 // Ghost house door right jamb
#define LOR   29 // Lower border
#define DRN   30 // Border turn, from down to right
#define DRL   31 // Border turn, from down to left
#define BUL   32 // border, upper left
#define DVBOR 33  // double vert border
#define BOR   34 // border
#define VLN   35 // regular single vertical line border
#define RoD   36 // Red populated
#define PoK   37 // Pink populated
#define BoU   38 // Blue populated
#define OoA   39 // Orange populated
//40, 41
#define URM   40  // upper right middle border
#define BUR   41  // border, upper right
#define BL2   44 // Left Border turn for lower PP salient
#define BR2   45 // '' but right
#define BL3   46 //
#define BR3   47 //
#define DOR   48 // Ghost house door
#define _C_      49 // Red scatter target, occupied
#define PnK   50 // ''
#define BlU   51 // ''
#define OrA   52 // ''
#define B_R   53 // bottom border
#define GHL   57
#define eLR   58
#define eLL   59
#define eUL   60
#define eUR   61
#define YLN   62
#define ZLN   63

#define FALSE 0
#define TRUE  1

#define GHOST_ANIM_COUNTER 16

#define MAP_WIDTH     28
#define MAP_HEIGHT    31
#define NB_TILE_BG    64
#define NB_DOT_TILES 868
#define NB_DOTS      240
#define NB_PPs         4
#define NB_TOTAL     244

#define pac_start_right_X  100
#define pac_start_right_Y  132    ///133
#define MAZE_START_X 104   /////112 ////////////
#define MAZE_START_Y 144    //140 /////////////

#define RED_START_X 104
#define RED_START_Y 84

#define TILE_PAL     0
#define SPRITE_PAL   1
#define GHOST_PAL    2
#define BLACKPAL     6

#define PAC_MAN_SPRITE        0


#define MOVEMENT_RATE 1

#define TILE_VRAM    0x1000
//#define PANEL_VRAM   0x2000
#define SPRITE_VRAM  0x6000

//#inctile(tile_gfx, "tiles.pcx", 8, 8)

#incpal(tile_pal,  "tiles.pcx", 0)
#incchr_ex(tile_gfx, "tiles.pcx", 0, 0, 8, 8, 0)

#define SQUARE_SPRITE 0x3700
#incspr(black_square, "redswap.png",  0, 0, 1, 1)
#incpal(blackpal, "redswap.png")

#incspr(pac_start_right, "sprites2.png", 0, 0, 1, 1)
#incspr(pac_faceright_1, "sprites2.png", 16, 0, 1, 1)
#incspr(pac_faceright_2, "sprites2.png", 32, 0, 1, 1)
#incspr(pac_faceright_3, "sprites2.png", 48, 0, 1, 1)

#incspr(pac_start_left, "sprites2.png", 0, 16, 1, 1)
#incspr(pac_faceleft_1, "sprites2.png", 16, 16, 1, 1)
#incspr(pac_faceleft_2, "sprites2.png", 32, 16, 1, 1)
#incspr(pac_faceleft_3, "sprites2.png", 48, 16, 1, 1)

#incspr(pac_start_up, "sprites2.png", 0, 32, 1, 1)
#incspr(pac_faceup_1, "sprites2.png", 16, 32, 1, 1)
#incspr(pac_faceup_2, "sprites2.png", 32, 32, 1, 1)
#incspr(pac_faceup_3, "sprites2.png", 48, 32, 1, 1)

#incspr(pac_start_down, "sprites2.png", 0, 48, 1, 1)
#incspr(pac_facedown_1, "sprites2.png", 16, 48, 1, 1)
#incspr(pac_facedown_2, "sprites2.png", 32, 48, 1, 1)
#incspr(pac_facedown_3, "sprites2.png", 48, 48, 1, 1)

#define REDRIGHT1  0x3000
#define REDRIGHT2  0x3100
#define REDUP1     0x3200
#define REDUP2     0x3300
#define REDDOWN1   0x3400
#define REDDOWN2   0x3500

#incspr(red_right_1, "redghosts.png",  0, 0, 1, 1)
#incspr(red_right_2, "redghosts.png", 16, 0, 1, 1) 
#incspr(red_up_1,    "redghosts.png", 64, 0, 1, 1)
#incspr(red_up_2,    "redghosts.png", 80, 0, 1, 1)
#incspr(red_down_1,  "redghosts.png", 96, 0, 1, 1)
#incspr(red_down_2,  "redghosts.png", 112, 0, 1, 1)

#incpal(sprite_pal, "sprites2.png")
#incpal(red_pal, "redghosts.png")




typedef enum {LEFT, RIGHT, UP, DOWN, HALT} DIRECTION;
typedef enum {NULLG, RED, PINK, ORANGE, BLUE} GCOLOR;
typedef enum {CHASE, SCATTER, CRUISE_ELROY} MODE;

const char tile_pal_ref[NB_TILE_BG] = {
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4,
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4,
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4,
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4,
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4,
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4,
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4,
	TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4, TILE_PAL<<4	
};

#define XXX 0
// All directions start from leftmost
#define L_R 2   // LR Corridor
#define U_D 3   // UD Corridor
#define LcR 4 // corridor

#define D_R 5   //Down Right
#define L_D 6   //Left Down
#define U_R 7   //Up Right
#define U_L 8   //Up Left
//three-way
#define LDR 9  // Left Down Right
#define LUR 10  // Left Up Right
#define UDR 11 // Up Down Right
#define LUD 12 // Left Up Down

#define FFF 13



const char intersections[868]={
   XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,  // 1
   XXX, D_R, L_R, L_R, L_R, L_R, LDR, L_R, L_R, L_R, L_R, L_R, L_D, XXX, XXX, D_R, L_R, L_R, L_R, L_R, L_R, LDR, L_R, L_R, L_R, L_R, L_D, XXX,  // 2
   XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX,  // 3
   XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX,  // 4 powerpellet row
   XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, // 5
   XXX, UDR, L_R, L_R, L_R, L_R, FFF, L_R, L_R, LDR, L_R, L_R, LUR, L_R, L_R, LUR, L_R, L_R, LDR, L_R, L_R, FFF, L_R, L_R, L_R, L_R, LUD, XXX,  // 6
   XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, // 7
   XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, // 8
   XXX, U_R, L_R, L_R, L_R, L_R, LUD, XXX, XXX, U_R, L_R, L_R, L_D, XXX, XXX, D_R, L_R, L_R, U_L, XXX, XXX, UDR, L_R, L_R, L_R, L_R, U_L, XXX, // 9
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, // 10
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, //11
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, D_R, L_R, L_R, LUR, L_R, L_R, LUR, L_R, L_R, L_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX,  // 12
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX,  // 13 top of ghost house
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, // 14
   L_R, L_R, L_R, L_R, L_R, L_R, FFF, L_R, L_R, LUD, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, UDR, L_R, L_R, FFF, L_R, L_R, L_R, L_R, L_R, L_R, // 15
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, // 16
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX,  // 17 bottom of house
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, UDR, L_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, LUD, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX,  // 18 starting corridor
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX,  // 19
   XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX,  // 20
   XXX, D_R, L_R, L_R, L_R, L_R, FFF, L_R, L_R, LUR, L_R, L_R, L_D, XXX, XXX, D_R, L_R, L_R, LUR, L_R, L_R, FFF, L_R, L_R, L_R, L_R, L_D, XXX,   // 21 long corridor
   XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX,  //22
   XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, XXX, XXX, U_D, XXX,  //23
   XXX, U_R, L_R, L_D, XXX, XXX, UDR, L_R, L_R, LDR, L_R, L_R, LUR, L_R, L_R, LUR, L_R, L_R, LDR, L_R, L_R, LUD, XXX, XXX, D_R, L_R, U_L, XXX,   //24 Powerpellet row 
   XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX,  //25
   XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX,  //26
   XXX, D_R, L_R, LUR, L_R, L_R, U_L, XXX, XXX, U_R, L_R, L_R, L_D, XXX, XXX, D_R, L_R, L_R, U_L, XXX, XXX, U_R, L_R, L_R, LUR, L_R, L_D, XXX, 
   XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, 
   XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, XXX, U_D, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, U_D, XXX, 
   XXX, U_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, LUR, L_R, L_R, LUR, L_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, L_R, U_L, XXX, 
   XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX  
};

const char pacField[NB_DOT_TILES]={ 
   BUL,   BOR, BOR, BOR, BOR, BOR,   BOR, BOR, BOR, BOR, BOR,   BOR, BOR, ULM, URM, BOR, BOR,   BOR,   BOR, BOR, BOR, BOR,   BOR, BOR, BOR, BOR, BOR, BUR,   
   DVBOR, PNK, ___, ___, ___, ___,   ___, ___, ___, ___, ___,   ___, ___, VLN, ZLN, ___, ___,   ___,   ___, ___, ___, ___,   ___, ___, ___, ___, RXD, RVBOR,  
   DVBOR, ___, RUL, HLN, HLN, RUR,   ___, RUL, HLN, HLN, HLN,   RUR, ___, VLN, ZLN, ___, RUL,   HLN,   HLN, HLN, RUR, ___,   RUL, HLN, HLN, RUR, ___, RVBOR, 
   DVBOR, ___, VLN, _B_, _B_, ZLN,   ___, VLN, _B_, _B_, _B_,   ZLN, ___, VLN, ZLN, ___, VLN,   _B_,   _B_, _B_, ZLN, ___,   VLN, _B_, _B_, ZLN, ___, RVBOR, 
   DVBOR, ___, RLL, YLN, YLN, RLR,   ___, RLL, YLN, YLN, YLN,   RLR, ___, RLL, RLR, ___, RLL,   YLN,   YLN, YLN, RLR, ___,   RLL, YLN, YLN, RLR, ___, RVBOR, 
   DVBOR, ___, ___, ___, ___, ___,   ___, ___, ___, ___, ___,   ___, ___, ___, ___, ___, ___,   ___,   ___, ___, ___, ___,   ___, ___, ___, ___, ___, RVBOR, 
   DVBOR, ___, RUL, HLN, HLN, RUR,   ___, RUL, RUR, ___, RUL,   HLN, HLN, HLN, HLN, HLN, HLN,   RUR,   ___, RUL, RUR, ___,   RUL, HLN, HLN, RUR, ___, RVBOR, 
   DVBOR, ___, RLL, YLN, YLN, RLR,   ___, VLN, ZLN, ___, RLL,   YLN, YLN, eUR, eUL, YLN, YLN,   RLR,   ___, VLN, ZLN, ___,   RLL, YLN, YLN, RLR, ___, RVBOR, 
   DVBOR, ___, ___, ___, ___, ___,   ___, VLN, ZLN, ___, ___,   ___, ___, VLN, ZLN, ___, ___,   ___,   ___, VLN, ZLN, ___,   ___, ___, ___, ___, ___, RVBOR, 
   BLL,   BUN, BUN, BUN, BUN, BLN,   ___, VLN, eLL, HLN, HLN,   RUR, _B_, VLN, ZLN, _B_, RUL,   HLN,   HLN, eLR, ZLN, ___,   RUL, BUN, BUN, BUN, BUN, BLR,   
   _B_,   _B_, _B_, _B_, _B_, DVBOR, ___, VLN, eUL, YLN, YLN,   RLR, _B_, RLL, RLR, _B_, RLL,   YLN,   YLN, eUR, ZLN, ___, RVBOR, _B_, _B_, _B_, _B_, _B_,   
   _B_,   _B_, _B_, _B_, _B_, DVBOR, ___, VLN, ZLN, _B_, _B_,   _B_, _B_, _B_, _B_, _B_, _B_,   _B_,   _B_, VLN, ZLN, ___, RVBOR, _B_, _B_, _B_, _B_, _B_,   
   _B_,   _B_, _B_, _B_, _B_, DVBOR, ___, VLN, ZLN, _B_, GUR,   LOR, GDL, DOR, DOR, GDR, LOR,   GUL,   _B_, VLN, ZLN, ___, RVBOR, _B_, _B_, _B_, _B_, _B_,    // top of ghost house
   BOR,   BOR, BOR, BOR, BOR, DRL,   ___, RLL, RLR, _B_, GHL,  _B_, _B_, _B_, _B_, _B_, _B_,   DVBOR, _B_, RLL, RLR, ___,   DRN, BOR, BOR, BOR, BOR, BOR,   
   _B_,   _B_, _B_, _B_, _B_, _B_,   ___, _B_, _B_, _B_, GHL,  _B_, _B_, _B_, _B_, _B_, _B_,   DVBOR, _B_, _B_, _B_, ___,   _B_, _B_, _B_, _B_, _B_, _B_,   
   LOR,   LOR, LOR, LOR, LOR, BLN,   ___, RUL, RUR, _B_, GHL,  _B_, _B_, _B_, _B_, _B_, _B_,   DVBOR, _B_, RUL, RUR, ___,   RUL, LOR, LOR, LOR, LOR, LOR ,   
   _B_,   _B_, _B_, _B_, _B_, DVBOR, ___, VLN, ZLN, _B_, GLL,   BOR, BOR, BOR, BOR, BOR, BOR,   GLR,   _B_, VLN, ZLN, ___, RVBOR, _B_, _B_, _B_, _B_, _B_,    // bottom of house
   _B_,   _B_, _B_, _B_, _B_, DVBOR, ___, VLN, ZLN, _B_, _B_,   _B_, _B_, _Bp, pB_, _B_, _B_,   _B_,   _B_, VLN, ZLN, ___, RVBOR, _B_, _B_, _B_, _B_, _B_,    // starting corridor
   _B_,   _B_, _B_, _B_, _B_, DVBOR, ___, VLN, ZLN, _B_, RUL,   HLN, HLN, HLN, HLN, HLN, HLN,   RUR,   _B_, VLN, ZLN, ___, RVBOR, _B_, _B_, _B_, _B_, _B_,   
   BUL,   BOR, BOR, BOR, BOR, DRL,   ___, RLL, RLR, _B_, RLL,   YLN, YLN, eUR, eUL, YLN, YLN,   RLR,   _B_, RLL, RLR, ___,   DRN, BOR, BOR, BOR, BOR, BUR,    
   DVBOR, ___, ___, ___, ___, ___,   ___, ___, ___, ___, ___,   ___, ___, VLN, ZLN, ___, ___,   ___,   ___, ___, ___, ___,   ___, ___, ___, ___, ___, RVBOR,   // long corridor
   DVBOR, ___, RUL, HLN, HLN, RUR,   ___, RUL, HLN, HLN, HLN,   RUR, ___, VLN, ZLN, ___, RUL,   HLN,   HLN, HLN, RUR, ___,   RUL, HLN, HLN, RUR, ___, RVBOR, 
   DVBOR, ___, RLL, YLN, eUR, ZLN,   ___, RLL, YLN, YLN, YLN,   RLR, ___, RLL, RLR, ___, RLL,   YLN,   YLN, YLN, RLR, ___,   VLN, eUL, YLN, RLR, ___, RVBOR, 
   DVBOR, ___, ___, ___, VLN, ZLN,   ___, ___, ___, ___, ___,   ___, ___, _B_, _B_, ___, ___,   ___,   ___, ___, ___, ___,   VLN, ZLN, ___, ___, ___, RVBOR,   // Powerpellet row 
   45 ,   HLN, RUR, ___, VLN, ZLN,   ___, RUL, RUR, ___, RUL,   HLN, HLN, HLN, HLN, HLN, HLN,   RUR,   ___, RUL, RUR, ___,   VLN, ZLN, ___, RUL, HLN, 42,   
   44 ,   YLN, RLR, ___, RLL, RLR,   ___, VLN, ZLN, ___, RLL,   YLN, YLN, eUR, eUL, YLN, YLN,   RLR,   ___, VLN, ZLN, ___,   RLL, RLR, ___, RLL, YLN, 43,   
   DVBOR, ___, ___, ___, ___, ___,   ___, VLN, ZLN, ___, ___,   ___, ___, VLN, ZLN, ___, ___,   ___,   ___, VLN, ZLN, ___,   ___, ___, ___, ___, ___, RVBOR, 
   DVBOR, ___, RUL, HLN, HLN, HLN,   HLN, eLR, eLL, HLN, HLN,   RUR, ___, VLN, ZLN, ___, RUL,   HLN,   HLN, eLR, eLL, HLN,   HLN, HLN, HLN, RUR, ___, RVBOR, 
   DVBOR, ___, RLL, YLN, YLN, YLN,   YLN, YLN, YLN, YLN, YLN,   RLR, ___, RLL, RLR, ___, RLL,   YLN,   YLN, YLN, YLN, YLN,   YLN, YLN, YLN, RLR, ___, RVBOR, 
   DVBOR, BLU, ___, ___, ___, ___,   ___, ___, ___, ___, ___,   ___, ___, ___, ___, ___, ___,   ___,   ___, ___, ___, ___,   ___, ___, ___, ___, ORA, RVBOR, 
   BLL,   LOR, LOR, LOR, LOR, LOR,   LOR, LOR, LOR, LOR, LOR,   LOR, LOR, LOR, LOR, LOR, LOR,   LOR,   LOR, LOR, LOR, LOR,   LOR, LOR, LOR, LOR, LOR, BLR   
};

// the dot layout

const char populatedDotField[868]={
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,  
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, // powerpellet row
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
   0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  // top of ghost house
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  // bottom of house
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  // starting corridor
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,   // long corridor
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 0,   // Powerpellet row 
   0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
   0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
   0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  
};

char workingField[868]={
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,  
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, // powerpellet row
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
   0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  // top of ghost house
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  // bottom of house
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  // starting corridor
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,   // long corridor
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
   0, 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 0,   // Powerpellet row 
   0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
   0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
   0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  
};



struct pacMan
{
	//#define pac_start_right_X  104
    //#define pac_start_right_Y  133
	int x;
	int y;
	int maze_x;
	int maze_y;
	int box_x;     // bounding box
	int box_y;   
	unsigned char iter; // for vsync.  Pac-man's animation is every other frame 
	//unsigned char UPflag;
	unsigned char cruiseLR;
	unsigned char cruiseUD;
	unsigned char start_status;
	DIRECTION direction;
	DIRECTION previous_direction;
	unsigned int score;
	
};

struct pacMan Pac_Man;


struct ghostMonster
{
	int x;
	int y;
	int maze_x;
	int maze_y;
	unsigned char iter;
	unsigned char cruiseLR;
	unsigned char cruiseUD;
	MODE mode;
	DIRECTION primary_direction;
	DIRECTION secondary_direction;
	DIRECTION previous_direction;
	GCOLOR color;
};

struct ghostMonster Red_Ghost;
struct ghostMonster Pink_Ghost;
struct ghostMonster Orange_Ghost;
struct ghostMonster Blue_Ghost;

unsigned int d_Iter;

void repopulateField(char *a)
{
	
	int i=0;
	int x=0;
	unsigned char j=0;
	
	while(i < 868)
	{
		if(j == 28)
		{
			x+=4;
			j = 0;
		}
		
		if(populatedDotField[i] == 1)
		{
			put_tile(0, x);
			++*a;
		}
		
		j++;
		x++;
		i++;
	}
	return;
}


void pac_Init();
void pac_Move(DIRECTION direction);
void pac_Anim(unsigned char counter, unsigned int *iter);
void dot_removal();
void set_score(unsigned char num);
void ghost_Init();
void red_Anim(unsigned char counter, unsigned int scroll_y);
DIRECTION vector_Target(GCOLOR color);
DIRECTION determine_Direction(unsigned int tile, DIRECTION incoming_Direction, GCOLOR color);


main()
{
	char dotCount = 0;   // max 244 (240 regular dots, 4 power pellets.)
	int i;
	unsigned int j;
	unsigned int map_x;
	unsigned int map_y;
	unsigned int iter;
	unsigned char flagCounter;
	unsigned int scroll_y;
	unsigned char counter;
	
	
	struct pacMan *Pac_Ptr; 
	Pac_Ptr = &Pac_Man;
	
	Pac_Man.x = pac_start_right_X;
	Pac_Man.y = pac_start_right_Y;
	Pac_Man.maze_x = MAZE_START_X;
	Pac_Man.maze_y = MAZE_START_Y;
	Pac_Man.box_x = Pac_Man.x + 6;
	Pac_Man.box_y = Pac_Man.y + 6;
	Pac_Man.direction = 1;
	Pac_Man.iter = 0;
	Pac_Man.start_status = TRUE;
	Pac_Man.score = 0;
	
	Red_Ghost.x = RED_START_X;
	Red_Ghost.y = RED_START_Y;
	
	scroll_y = 0;
	d_Iter = 33;
	
	disp_off();
	cls();
	set_screen_size(SCR_SIZE_32x32);
	set_map_data(pacField, MAP_WIDTH, MAP_HEIGHT);

	set_tile_data(tile_gfx);
	load_tile(TILE_VRAM);
	load_palette(TILE_PAL, tile_pal, 1);
	load_map(0, 0, 0, 0, MAP_WIDTH, MAP_HEIGHT);

	for(i=0; i<248; i+=8)
	{
		for(j=224; j<256; j+=8)
		{
			put_tile(1, j/8, i/8);
		}
	}
	put_tile(0, 1, 1);

	set_font_color(1, 4);
	load_default_font();
	put_string(" 1UP", 23, 10);
	put_string("000000", 23, 11);
	//put_char(5, 23, 12);
	
	repopulateField(&dotCount);
	
	init_satb();
	pac_Init();
	disp_on();
	
	counter = 0;
	iter = PACSTARTRIGHT;
	Pac_Man.direction = HALT;  // HALT used only for beginning a level
	
	ghost_Init();
	
	spr_set(0);
	spr_pal(BLACKPAL);
	spr_pattern(SQUARE_SPRITE);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
	spr_pri(1);
	spr_x(0);
	spr_y(108 - scroll_y);
	
	spr_set(1);
	spr_pal(BLACKPAL);
	spr_pattern(SQUARE_SPRITE);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
	spr_pri(1);
	spr_x(208);
	spr_y(108 - scroll_y);
	
	load_sprites(SQUARE_SPRITE, black_square, 1);
	satb_update();
	
	for (;;)
	{
		if(Pac_Man.maze_y/8 >= 15 && scroll_y < 24)   // if Pac-Man is in Y-Corridor XX and the maze hasn't fully shifted up yet
		{
			scroll_y++;
		}
		else if(Pac_Man.maze_y/8 < 15 && scroll_y != 0)
		{
			scroll_y--;
		}
		i=0;
		Pac_Man.box_x = Pac_Man.x + 6;
		Pac_Man.box_y = Pac_Man.y + 6;
		
		map_y = ((Pac_Man.y+4) / 8);   
		map_x = ((Pac_Man.x+4) / 8);		
		
		i = ((28 * map_y) + (map_x));
		
		if ((joy(0) & JOY_LEFT) && Pac_Man.maze_y % 8 == 0)
		{
			if(intersections[i] == U_D)
			{
				Pac_Man.cruiseUD = TRUE;
			}
			else if(intersections[i] == L_R || intersections[i] == LcR)
			{
				Pac_Man.previous_direction = Pac_Man.direction;
				Pac_Man.direction = LEFT;
				Pac_Man.cruiseUD = FALSE;
				Pac_Man.cruiseLR = TRUE;
			}
			else if(Pac_Man.maze_y % 8 == 0)
			{
				if(intersections[i-1] > XXX)	
				{
					Pac_Man.previous_direction = Pac_Man.direction;
					Pac_Man.direction = LEFT;
				}
			}
		}
		else if((joy(0) & JOY_RGHT) && Pac_Man.maze_y % 8 == 0)
		{
			if(intersections[i] == U_D)
			{
				Pac_Man.cruiseUD = TRUE;
			}
			else if(intersections[i] == L_R || intersections[i] == LcR)
			{
				Pac_Man.previous_direction = Pac_Man.direction;
				Pac_Man.direction = RIGHT;
				Pac_Man.cruiseUD = FALSE;
				Pac_Man.cruiseLR = TRUE;
			}
			else if(Pac_Man.maze_y % 8 == 0)
			{
				if(intersections[i+1] > XXX)	
				{
					Pac_Man.previous_direction = Pac_Man.direction;
					Pac_Man.direction = RIGHT;
					// added during search for the turnbug
					Pac_Man.cruiseUD = FALSE;
					// ''
					Pac_Man.cruiseLR = TRUE;
				}
			}
		}
		else if((joy(0) & JOY_UP) && Pac_Man.maze_x % 8 == 0)
		{
			if(intersections[i] == L_R || intersections[i] == LcR)
			{
				Pac_Man.cruiseLR = TRUE;
			}
			else if(intersections[i] == U_D)
			{
				Pac_Man.previous_direction = Pac_Man.direction;
				Pac_Man.direction = UP;
				Pac_Man.cruiseUD = TRUE;
				Pac_Man.cruiseLR = FALSE;
			}
			else if(intersections[i] > L_D && intersections[i] < LDR)
			{
				Pac_Man.direction = UP;
				Pac_Man.cruiseUD = TRUE;
				Pac_Man.cruiseLR = FALSE;
			}
			else if((intersections[i] > U_L) && (intersections[i] != LDR ))
			{
				Pac_Man.direction = UP;
				Pac_Man.cruiseUD = TRUE;
				Pac_Man.cruiseLR = FALSE;
			}
		}
		else if((joy(0) & JOY_DOWN) && Pac_Man.maze_x % 8 == 0)
		{	
			if(intersections[i] == L_R || intersections[i] == LcR)
			{
				Pac_Man.cruiseLR = TRUE;
			}
			else if(intersections[i] == U_D)
			{
				Pac_Man.previous_direction = Pac_Man.direction;
				Pac_Man.direction = DOWN;
				Pac_Man.cruiseUD = TRUE;
				Pac_Man.cruiseLR = FALSE;
			}
			else if(intersections[i] > U_D && intersections[i] < U_R)
			{
				Pac_Man.direction = DOWN;
				Pac_Man.cruiseUD = TRUE;
				Pac_Man.cruiseLR = FALSE;
			}
			else if((intersections[i] > U_L) && (intersections[i] != LUR ))
			{
				Pac_Man.direction = DOWN;
				Pac_Man.cruiseUD = TRUE;
				Pac_Man.cruiseLR = FALSE;
			}
		}
		else
			Pac_Man.previous_direction = Pac_Man.direction;

		pac_Move(Pac_Man.direction);
		//ghost_Move(GCOLOR color, int curr_x, int curr_y)
		ghost_Move(RED, Red_Ghost.x, Red_Ghost.y);
		if((Pac_Man.maze_x % 8 == 0) && (Pac_Man.maze_y % 8 == 0))
			dot_removal();

		spr_set(4);    // The sprite number itself. 
		spr_pattern(iter);
		
		if(Pac_Man.direction == LEFT)
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		else if (Pac_Man.direction == RIGHT)
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|FLIP_X);
		else if (Pac_Man.direction == UP)
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|FLIP_Y);
		else
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		
		spr_pri(1);  
		spr_x(Pac_Man.x);
		spr_y(Pac_Man.y - scroll_y);
		
		spr_set(0);
		spr_pal(BLACKPAL);
		spr_pattern(SQUARE_SPRITE);
		spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		spr_pri(1);
		spr_x(0);
		spr_y(108 - scroll_y);
		
		spr_set(1);
		spr_pal(BLACKPAL);
		spr_pattern(SQUARE_SPRITE);
		spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		spr_pri(1);
		spr_x(208);
		spr_y(108 - scroll_y);
		
		
		
		set_sprpal(BLACKPAL, blackpal);
		
		//scroll(0, 0, ADJUST THIS NUMBER, 0, 223, 0xC0);
		scroll(0, 0, scroll_y, 0, 223, 0xC0);
	
		satb_update();
		vsync();
		counter++;
		
		//pac_Anim(counter, &iter);
		red_Anim(counter, scroll_y);
		if(Pac_Man.direction == LEFT || Pac_Man.direction == RIGHT)
		{
			if(iter < 0x6000 || iter > 0x6300)
				iter = 0x6000;
		
			if((counter % 4)==0)
			{
				iter += 0x0100;
				if(iter >= 0x6400)
					iter = 0x6000;
			}
		}
		else if(Pac_Man.direction == UP)
		{
			if(iter < 0x7200 || iter > 0x7500)
				iter = 0x7200;
			
			if((counter % 4)==0)
			{
				iter += 0x0100;
				
				if(iter == 0x7600)
					iter = 0x7200;
			}
			
		}
		else if (Pac_Man.direction == DOWN)
		{
			if(iter < 0x7200 || iter > 0x7500)
				iter = 0x7200;
			
			if((counter % 4)==0)
			{
				iter += 0x0100;
				
				if(iter == 0x7600)
					iter = 0x7200; 
			}
		}
		
		if (counter % 16 == 0)
			counter = 0;
	}
}


/*
#define XXX 0
// All directions start from leftmost
#define L_R 2   // LR Corridor
#define U_D 3   // UD Corridor
#define LcR 4 // corridor

#define D_R 5   //Down Right
#define L_D 6   //Left Down
#define U_R 7   //Up Right
#define U_L 8   //Up Left
//three-way
#define LDR 9  // Left Down Right
#define LUR 10  // Left Up Right
#define UDR 11 // Up Down Right
#define LUD 12 // Left Up Down

#define FFF 13
*/

DIRECTION determine_Direction(unsigned int tile, DIRECTION incoming_Direction, GCOLOR color)
{
	DIRECTION new_direction;
	DIRECTION XDirection;
	DIRECTION YDirection;
	int x1;
	int y1;
	
	
	unsigned int x;
	unsigned int y;
	char r;
	new_direction = vector_Target(color);
	
	put_number(tile, 3, 0, 20);
	
	switch(color){
		case RED:
		{
			x = Red_Ghost.x;
			y = Red_Ghost.y;
			break;
		}
		
	}
	
	switch(intersections[tile])
	{
		// 2-Way Intersection Notes
		// It's irrelevant what mode a ghost is in when they encounter a two-way intersection. 
		// They simply have to keep moving as per their behavior. 
		// Ghost AI (vectoring) only kicks in at a 3 or 4-way intersection. 
		case D_R:
		{
			put_string("D_R", 0, 9);
			if(incoming_Direction == UP)
			{
				return RIGHT;
			}
			else 
				return DOWN;
			// do not vector
			break;
		}
		
		case L_D:
		{
			put_string("L_D", 0, 9);
			if(incoming_Direction == UP)
			{
				
				return LEFT;
			}
			else
				return DOWN;
			// do not vector
			break;
		}
		
		case U_R:
		{
			put_string("U_R", 0, 9);
			if(incoming_Direction == DOWN)
				return RIGHT;
			else
				return UP;
			// do not vector
			break;
		}
		
		case U_L:
		{
			put_string("U_L", 0, 9);
			if(incoming_Direction == DOWN)
				return LEFT;
			else
				return UP;
			// do not vector
			break;
		}
		// Three-way intersection notes
		// When a ghost arrives at a three-way, only two of the directions are available.
		// A ghost cannot turn back from whence it came. It must take a single turn or continue
		// straight ahead. 
		case LDR:
		{
			put_string("LDR", 0, 9);
			if(incoming_Direction == UP)
			{
				if(new_direction == UP)
				{
					if(Pac_Man.x > x) 
					    return RIGHT;
					else if(Pac_Man.x < x)
						return LEFT; 	
				}
			}
			else if(incoming_Direction == LEFT || incoming_Direction == RIGHT)
			{
				if(new_direction == UP || Pac_Man.y == y)
					return incoming_Direction;
				else
					return DOWN;
			}
			else
				return incoming_Direction;
			break;
		}
		case LUR:
		{
			//return UP;
			put_string("LUR", 0, 9);
			if(incoming_Direction == DOWN)
			{
				if(new_direction == UP)
					new_direction = DOWN;
				
				if(new_direction == DOWN)
				{
					if(Pac_Man.x > x ) // probably should set up a function for this
						return RIGHT;
					else
						return LEFT;
				}
				else
					return new_direction;
			}
			else if(incoming_Direction == LEFT || incoming_Direction == RIGHT)
			{
				if(tile >= 320 && tile <= 324)
					return incoming_Direction;
			    else if(new_direction == DOWN || Pac_Man.y == y)
					return incoming_Direction;
				else
					return UP;
			}
			else
				return incoming_Direction;
			break;
		}
		case UDR:
		{
			put_string("UDR", 0, 9);
			
			if(incoming_Direction == UP || incoming_Direction == DOWN)
			{
				if( Pac_Man.x > x)
					return RIGHT;
				else if( (Pac_Man.y > y) && (incoming_Direction == UP) ) 
					return RIGHT;
				else if (incoming_Direction == UP && (Pac_Man.y < y) )
					return UP;
				else
					return DOWN;
			}
			else if(incoming_Direction == LEFT)
			{
				
				if( Pac_Man.y >  y) // probably should set up a function for this
					return DOWN;
				else
					return UP;
				
				
			} 
			else
				return incoming_Direction;
			break;
		}
		case LUD:
		{
			put_string("LUD", 0, 9);
			
			//if( Pac_Man.y > y && incoming_Direction == DOWN)
				//return DOWN;
			//else if(Pac_Man.y < y && incoming_Direction == DOWN)
				//return LEFT;
			if(Pac_Man.x == x)
			{
				if(Pac_Man.y > y)
					return DOWN;
				else
					return UP;
			}
			
			if(incoming_Direction == UP || incoming_Direction == DOWN)
			{
				if( Pac_Man.x < x )
					return LEFT;
				else if(incoming_Direction == DOWN && Pac_Man.y < y)
					return LEFT;
				else
				{
					//return UP;
					return incoming_Direction;	
				}
			}
			
			if(incoming_Direction == RIGHT)
			{
				
				if(new_direction == RIGHT)
				{
					if( Pac_Man.y > y  ) // probably should set up a function for this
					{
						return DOWN;
					}
					else
						return UP;
				}
				
				return UP;
			}
			else
				return incoming_Direction;
			
			//return UP;
			break;
		}
		case FFF:
		{
			
			put_string("FFF", 0, 9);
			
			//if(tile == 566)
				//return UP;
			
			if(incoming_Direction == RIGHT)
			{
				if(Pac_Man.y > y)
					return DOWN;
				else if(Pac_Man.x > x)
					return RIGHT;
				else
					return UP;
				break;			
			}
			else if(incoming_Direction == LEFT)
			{
				if(Pac_Man.y > y)
					return DOWN;
				else if (Pac_Man.x < x)
					return LEFT;
				else
					return UP;
				break;
			}
			
			
			if(incoming_Direction == UP && new_direction == DOWN)
			{
				if(Pac_Man.x > x)
					return RIGHT;
				else
					return LEFT;
				break;
			}
			else if(incoming_Direction == DOWN && new_direction == UP)
			{
				
				if(Pac_Man.x > x)
					return RIGHT;
				else if(Pac_Man.x == x)
					return DOWN;
				else
					return LEFT;
				break;
			}
			else if(incoming_Direction == UP)
			{
				if(Pac_Man.x == x && Pac_Man.y < y)
					return UP;
				if(Pac_Man.x > x)
					return RIGHT;
				else
					return LEFT;
				break;
			}
			else if(incoming_Direction == DOWN)
			{
				if(Pac_Man.x == x && Pac_Man.y > y)
					return DOWN;
				if(Pac_Man.x > x)
					return RIGHT;
				else
					return LEFT;
				break;
			}
			
			
			if(Pac_Man.y == y)
			{
				if(Pac_Man.x < x)
				{
					if(incoming_Direction != RIGHT)
						return LEFT;
					else
					{
						r = random();
						if(r % 2 == 0)
							return UP;
						else
							return DOWN;
					}
				}
				else if(Pac_Man.x > x)
				{
					if(incoming_Direction != LEFT)
						return RIGHT;
					else
					{
						r = random();
						if(r % 2 == 0)
							return UP;
						else
							return DOWN;
					}
				}
			}
			else if(Pac_Man.x == x)
			{
				if(Pac_Man.y < y)
				{
					if(incoming_Direction != DOWN)
						return UP;
					else
					{
						r=random();
						if(r % 2 == 0)
							return LEFT;
						else
							return RIGHT;
					}
				}
				else
					return incoming_Direction;
			}
			else if(Pac_Man.y<y && incoming_Direction != UP)
				return UP;
			
			
			
			
			
			if(new_direction == LEFT || new_direction == RIGHT )
			{
				
				if(incoming_Direction == LEFT && new_direction == RIGHT)
				{
					if(Pac_Man.y > y)
						return DOWN;
					else
						return UP;
				}
				else if(incoming_Direction == RIGHT && new_direction == LEFT)
				{
					if(Pac_Man.y > y)
						return DOWN;
					else
						return UP;
				}
				
				break;
			}	
			else
				return new_direction;
			
			break;
		}
	}
}

void ghost_Move(GCOLOR color, int curr_x, int curr_y)
{
	unsigned int i;
	
	DIRECTION direction;
	char map_x;
	char map_y;
	
	i = ((28 * (((curr_y+4) / 8))) + (((curr_x+4) / 8)));
	
	switch(color)
	{
		case RED:
		{
			if( ( (Red_Ghost.y+4) % 8 == 0)  &&  ( (Red_Ghost.x+4) % 8 == 0) ) // check for intersection
			{
				//direction = HALT;
				if(intersections[i] > LcR)
				{
					direction = determine_Direction(i, Red_Ghost.primary_direction, RED);
					Red_Ghost.primary_direction = direction;
				}
			}
			
			switch(Red_Ghost.primary_direction)
			{
				case RIGHT:
				{
					if(((Red_Ghost.y+4) % 8 == 0)) // movement along X-axis should occur only when on correct Y-value
					{
						//if(pacField[i+1] <= ORA)
						if(intersections[i] > XXX)							
						{
							Red_Ghost.primary_direction = RIGHT;
							Red_Ghost.x+=MOVEMENT_RATE;
							Red_Ghost.cruiseLR = TRUE;	
						}
						else
						{
							Red_Ghost.primary_direction = Red_Ghost.previous_direction;
							Red_Ghost.cruiseLR = FALSE;
						}
					}
					else if(((Red_Ghost.y+4) % 8 == 0) && Red_Ghost.cruiseLR == TRUE)
					{
						Red_Ghost.x+=MOVEMENT_RATE;
					}
					break;
				}
				case LEFT:
				{
					if(((Red_Ghost.y+4) % 8 == 0))
					{						
						//if(pacField[i-1] <= ORA)
					    if(intersections[i] > XXX)
						{
							Red_Ghost.primary_direction = LEFT;
							Red_Ghost.x-=MOVEMENT_RATE;
							Red_Ghost.cruiseLR = TRUE;	
						}
						else
						{
							Red_Ghost.primary_direction = Red_Ghost.previous_direction;
							Red_Ghost.cruiseLR = FALSE;
						}
					}
					else if(((Red_Ghost.y+4) % 8 == 0) && Red_Ghost.cruiseLR == TRUE)
					{
						Red_Ghost.x-=MOVEMENT_RATE;
					}
					break;
				}
				case UP:
				{
					if(((Red_Ghost.x+4) % 8 == 0) && ((Red_Ghost.y+4) % 8 == 0) )
					{
						//i=0;
						map_y = ((Red_Ghost.y+11) / 8);
						map_x = ((Red_Ghost.x+4) / 8);				
							
						i = ((28 * map_y) + (map_x));
						
						if(pacField[i-28] <= ORA )	
						{
							map_y = ((Red_Ghost.y+12) / 8);
							i = ((28 * map_y) + (map_x));
							if(pacField[i-28] > ORA && (Red_Ghost.y % 8 == 0 ))
							{
								Red_Ghost.cruiseUD = FALSE;
								// code to move left or right goes here
							}
							else
							{
								Red_Ghost.primary_direction = UP;
								Red_Ghost.y-=MOVEMENT_RATE;
								//Pac_Man.maze_y-=MOVEMENT_RATE;
								Red_Ghost.cruiseUD = TRUE;
							}
						}
					}
					else if(((Red_Ghost.x+4) % 8 == 0) && Red_Ghost.cruiseUD == TRUE)
					{
						Red_Ghost.y-=MOVEMENT_RATE;
						//Pac_Man.maze_y-=MOVEMENT_RATE;
					}
					break;				
				}
				case DOWN:
				{
					if((Red_Ghost.x+4) % 8 == 0 && Red_Ghost.cruiseUD == FALSE)
					{
						Red_Ghost.primary_direction = DOWN;
						i=0;
						map_y = ((Red_Ghost.y+4) / 8);
						map_x = ((Red_Ghost.x+4) / 8);	
						
						i = ((28 * map_y) + (map_x));
						
						if(pacField[i+28] <= ORA)	
						{
							
							Red_Ghost.y+=MOVEMENT_RATE;
							//Pac_Man.maze_y+=MOVEMENT_RATE;
							Red_Ghost.cruiseUD = TRUE;
							Red_Ghost.cruiseLR = FALSE;
							break;
						}
						else
						{
							
							Red_Ghost.primary_direction = Pac_Man.previous_direction;
							Red_Ghost.cruiseLR = TRUE;
							Red_Ghost.cruiseUD = FALSE;
							break;
						}
					}
					else if(((Red_Ghost.x+4) % 8 == 0) && Red_Ghost.cruiseUD == TRUE)
					{
						
						Red_Ghost.y+=MOVEMENT_RATE;
						//Pac_Man.maze_y+=MOVEMENT_RATE;
						break;
					}
					break;
				}
				default:
				{
					break;
				}
			}
			break;
			//Red_Ghost.primary_direction = direction;
		}
	}
}

DIRECTION vector_Target(GCOLOR color)
{
	// This is rudimentary vectoring that occurs at the intersection. 
	
	// There needs to be a look-ahead feature implemented, but this will do for now.
	
	int x1;
	int y1;
	

	
	switch(color)
	{
		case RED:
		{
			//Notes: Red will only vector on Pac-Man during chase and Cruise Elroy modes
			//First, check for y axis then x axis to determine chase direction
			if(Red_Ghost.mode == SCATTER)
			{
				// get RED coords
			}
			
			if(Red_Ghost.x >= Pac_Man.x)
			{
				x1 = Red_Ghost.x - Pac_Man.x;
				//Red_Ghost.primary_direction == LEFT;
			}
			else
			{
				x1 = Pac_Man.x - Red_Ghost.x;
				//Red_Ghost.primary_direction == RIGHT;
			}
			
			if(Red_Ghost.y >= Pac_Man.y)
			{
				y1 = Red_Ghost.y - Pac_Man.y;
			}
			else
			{
				y1 = Pac_Man.y - Red_Ghost.y;
			}
			
			if(x1 == 0)
			{
				if(Red_Ghost.y > Pac_Man.y)
				{
					return UP;
					break;
				}
				else
				{
					return DOWN;
					break;
				}
			}
			else if(y1 == 0)
			{
				if(Red_Ghost.x > Pac_Man.x)
				{
					return LEFT;
					break;
				}
				else
				{
					return RIGHT;
					break;
				}
			}
			else
			{
				if(y1 > x1) // prioritise U/D
				{
					if(Red_Ghost.y > Pac_Man.y)
					{
						return UP;
						break;
					}
					else
					{
						return DOWN;
						break;
					}
				}
				else
				{
					if(Red_Ghost.x > Pac_Man.x)
					{
						return LEFT;
						break;
					}
					else
					{
						return RIGHT;
						break;
					}
				}
			}
			
			
			/*
			if(Pac_Man.y == Red_Ghost.y) // If Pac-Man is on the same LR path
			{
				// if x == x then game over man
				if(Pac_Man.x >= Red_Ghost.x)
				{
					Red_Ghost.primary_direction = RIGHT;
					//Red_Ghost.x++;
					break;
				}
				else if(Pac_Man.x <= Red_Ghost.x)
				{
					Red_Ghost.primary_direction = LEFT;
					//Red_Ghost--;
					break;
				}
			}
			else if(Pac_Man.x == Red_Ghost.x) // if Pac-Man is on the same UD path
			{
				// if y == y then game over
				if(Pac_Man.y >= Red_Ghost.y)
				{
					Red_Ghost.primary_direction = DOWN;
					//Red_Ghost.y++;
					break;
				}
				else if(Pac_Man.y <= Red_Ghost.y)
				{
					Red_Ghost.primary_direction = UP;
					//Red_Ghost.y--;
					break;
				}
			}
			else if(Pac_Man.y > Red_Ghost.y)  // might need to add onto this algorithm
			{
				Red_Ghost.primary_direction = DOWN;
				break;
			}
			return Red_Ghost.primary_direction;
			break;
			*/
		}
		case PINK:
		{
			
			break;
		}
		case ORANGE:
		{
			
			break;
		}
		case BLUE:
		{
			
			break;
		}	
	}
	return LEFT;
}

void red_Anim(unsigned char counter, unsigned int scroll_y)
{
	int map_y;
	int map_x;
	
	spr_set(2);
	spr_pal(2);
	
	map_y = ((Red_Ghost.y+4) / 8);   
	map_x = ((Red_Ghost.x+4) / 8);
	
	switch(Red_Ghost.mode)
	{
		case SCATTER:
		{
			//vector to RXD
			break;
		}
		default:
		{
			break;
		}
	}
	
	if(Red_Ghost.primary_direction == LEFT || Red_Ghost.primary_direction == RIGHT)
	{	
		if(counter % GHOST_ANIM_COUNTER >= 8 && Red_Ghost.primary_direction == RIGHT)
		{
			spr_pattern(REDRIGHT1);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		}
		else if(counter % GHOST_ANIM_COUNTER >= 0 && Red_Ghost.primary_direction == RIGHT)
		{
			spr_pattern(REDRIGHT2);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		}
		else if(counter % GHOST_ANIM_COUNTER >= 8 && Red_Ghost.primary_direction == LEFT)
		{
			spr_pattern(REDRIGHT1);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|FLIP_X);
		}
		else if(counter % GHOST_ANIM_COUNTER >= 0 && Red_Ghost.primary_direction == LEFT)
		{
			spr_pattern(REDRIGHT2);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|FLIP_X);
		}
	}
	else if(Red_Ghost.primary_direction == UP)
	{
		if(counter % GHOST_ANIM_COUNTER >= 8)
		{
			spr_pattern(REDUP1);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		}
		else
		{
			spr_pattern(REDUP2);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		}
	}
	else if(Red_Ghost.primary_direction == DOWN)
	{
		if(counter % GHOST_ANIM_COUNTER >= 8)
		{
			spr_pattern(REDDOWN1);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		}
		else
		{
			spr_pattern(REDDOWN2);
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		}
	}
	
	spr_pri(1);
	spr_x(Red_Ghost.x);
	spr_y(Red_Ghost.y-scroll_y);
	//put_string("berday", 0, 6);
	//put_number(counter, 4, 0, 6);
	return;
}

void pac_Anim(unsigned char counter, unsigned int *iter)
{
	return;
}

void set_score(unsigned char num)
{
	int score;
	unsigned char value;
	unsigned char iter;
	iter = 6;
	Pac_Man.score += (int)num;
	score = Pac_Man.score;
	while(iter != 0)
	{
		value = (char)(score % 10);
		put_number((int)value, 1, 22+iter, 11);
		score = score/10;
		iter--;
	}
	return;
}

void dot_removal(void)
{
	int i;
	unsigned char map_y;
	unsigned char map_x;
	int x;
	
	i=0;
	map_y = ((Pac_Man.y+4) / 8);   
	map_x = ((Pac_Man.x+4) / 8);		
	
	i = ((28 * map_y) + (map_x));
	
	if(workingField[i] > 0)
	{
		put_tile(1, map_x, map_y);
		workingField[i] = 0;
		set_score(10);
	}
	return;
}

void ghost_Init()
{
		
		Red_Ghost.x = RED_START_X;   
		Red_Ghost.y = RED_START_Y;    
		Red_Ghost.primary_direction = LEFT;
		Red_Ghost.mode = SCATTER;
		
		load_sprites(REDRIGHT1, red_right_1, 1);
		load_sprites(REDRIGHT2, red_right_2, 1);
		load_sprites(REDUP1, red_up_1, 1);
		load_sprites(REDUP2, red_up_2, 1);
		load_sprites(REDDOWN1, red_down_1, 1);
		load_sprites(REDDOWN2, red_down_2, 1);
		
		spr_set(2);
		spr_pal(GHOST_PAL);
		spr_pattern(REDRIGHT1);
		spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|FLIP_X);
		spr_pri(1); 
		spr_x(RED_START_X);  //112
		spr_y(RED_START_Y);   //88
		
		set_sprpal(GHOST_PAL, red_pal);
		satb_update();
		return;
}

void pac_Init()
{
	spr_set(4);    // The sprite number itself. 
	spr_pal(SPRITE_PAL);
	spr_pattern(PACSTARTRIGHT);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
	spr_pri(1);  
	spr_x(Pac_Man.x);
	spr_y(Pac_Man.y);
	satb_update();
	
	
	load_sprites(PACSTARTRIGHT, pac_start_right, 1);
	load_sprites(PACRANIM1, pac_faceright_1, 1);
	load_sprites(PACRANIM2, pac_faceright_2, 1);
	load_sprites(PACRANIM3, pac_faceright_3, 1);
	
	load_sprites(PACSTARTLEFT, pac_start_left, 1);
	load_sprites(PACRANIM1, pac_faceleft_1, 1);
	load_sprites(PACRANIM2, pac_faceleft_2, 1);
	load_sprites(PACRANIM3, pac_faceleft_3, 1);
	
	load_sprites(PACSTARTUP, pac_start_up, 1);
	load_sprites(PACUANIM1, pac_faceup_1, 1);
	load_sprites(PACUANIM2, pac_faceup_2, 1);
	load_sprites(PACUANIM3, pac_faceup_3, 1);
	
	load_sprites(PACSTARTDOWN, pac_start_down, 1);
	load_sprites(PACDANIM1, pac_facedown_1, 1);
	load_sprites(PACDANIM2, pac_facedown_2, 1);
	load_sprites(PACDANIM3, pac_facedown_3, 1);
	
	set_sprpal(SPRITE_PAL, sprite_pal);
	return;
}


void pac_Move(DIRECTION direction)
{
	char map_x;
	char map_y;
	int i;
	
	switch(direction)
	{
		case RIGHT:
		{
			if(((Pac_Man.maze_y) % 8 == 0)) // movement along X-axis should occur only when on correct Y-value
			{
				i=0;
				map_y = ((Pac_Man.y+4) / 8);
				map_x = ((Pac_Man.x+4) / 8);		
				
				i = ((28 * map_y) + (map_x));
				
				if(pacField[i+1] <= ORA)	
				{
					Pac_Man.direction = RIGHT;
					Pac_Man.x+=MOVEMENT_RATE;
					Pac_Man.maze_x+=MOVEMENT_RATE;
					Pac_Man.cruiseLR = TRUE;	
				}
				else
				{
					Pac_Man.direction = Pac_Man.previous_direction;
					Pac_Man.cruiseLR = FALSE;
				}
			}
			else if(((Pac_Man.maze_y) % 8 == 0) && Pac_Man.cruiseLR == TRUE)
			{
				Pac_Man.x+=MOVEMENT_RATE;
				Pac_Man.maze_x+=MOVEMENT_RATE;
			}
			break;
		}
		case LEFT:
		{
			if(((Pac_Man.maze_y) % 8 == 0)) // movement along X-axis should occur only when on correct Y-value
			{
				
				i=0;
				map_y = ((Pac_Man.y+4) / 8);
				map_x = ((Pac_Man.x+4) / 8);
				
				i = ((28 * map_y) + (map_x));
				
				if(pacField[i] <= ORA)
				{
					if(pacField[i-1] > ORA && (Pac_Man.maze_x % 8 == 0 ))
					{
						Pac_Man.cruiseLR = FALSE;
					}
					else
					{
						Pac_Man.direction = LEFT;
						Pac_Man.x-=MOVEMENT_RATE;
						Pac_Man.maze_x-=MOVEMENT_RATE;
						Pac_Man.cruiseLR = TRUE;
					}
				}
				else
				{
					Pac_Man.direction = Pac_Man.previous_direction;
				}
			}
			else if(((Pac_Man.maze_y) % 8 == 0) && Pac_Man.cruiseLR == TRUE)
			{
				Pac_Man.x-=MOVEMENT_RATE;
				Pac_Man.maze_x-=MOVEMENT_RATE;
			}
			break;
		}
		case UP:
		{
			if(((Pac_Man.maze_x) % 8 == 0) && ((Pac_Man.maze_y) % 8 == 0) )
			{
				i=0;
				map_y = ((Pac_Man.y+11) / 8);
				map_x = ((Pac_Man.x+4) / 8);				
					
				i = ((28 * map_y) + (map_x));
				
				if(pacField[i-28] <= ORA )	
				{
					map_y = ((Pac_Man.y+12) / 8);
					i = ((28 * map_y) + (map_x));
					if(pacField[i-28] > ORA && (Pac_Man.maze_y % 8 == 0 ))
					{
						Pac_Man.cruiseUD = FALSE;
					}
					else
					{
						Pac_Man.direction = UP;
						Pac_Man.y-=MOVEMENT_RATE;
						Pac_Man.maze_y-=MOVEMENT_RATE;
						Pac_Man.cruiseUD = TRUE;
					}
				}
			}
			else if(((Pac_Man.maze_x) % 8 == 0) && Pac_Man.cruiseUD == TRUE)
			{
				Pac_Man.y-=MOVEMENT_RATE;
				Pac_Man.maze_y-=MOVEMENT_RATE;
			}
			break;				
		}
		case DOWN:
		{
			if((Pac_Man.maze_x) % 8 == 0)
			{
				Pac_Man.direction = DOWN;
				i=0;
				
				map_y = ((Pac_Man.y+4) / 8);
				map_x = ((Pac_Man.x+4) / 8);	
				
				i = ((28 * map_y) + (map_x));
				
				if(pacField[i+28] <= ORA)	
				{
					Pac_Man.y+=MOVEMENT_RATE;
					Pac_Man.maze_y+=MOVEMENT_RATE;
					Pac_Man.cruiseUD = TRUE;
					Pac_Man.cruiseLR = FALSE;
				}
				else
				{
					Pac_Man.direction = Pac_Man.previous_direction;
					Pac_Man.cruiseLR = TRUE;
					Pac_Man.cruiseUD = FALSE;
				}
			}
			else if(((Pac_Man.maze_x) % 8 == 0) && Pac_Man.cruiseUD == TRUE)
			{
				Pac_Man.y+=MOVEMENT_RATE;
				Pac_Man.maze_y+=MOVEMENT_RATE;
			}
			break;
		}
		case HALT:
		{
			break;
		}
	}
	
}



//760 4893