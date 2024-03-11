
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include <iostream>
#include < windows.h>
#include < string >
#include < SDL.h >
#include < SDL_image.h >
#include < SDL_mixer.h >
#include < SDL_ttf.h >

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
//The music that will be played
static Mix_Music* gMusic = NULL;


// screen
const int FRAME_PER_SECOND = 60; // fps

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_bpp = 32;

const int color_key_r = 128;
const int color_key_g = 128;
const int color_key_b = 128;
const int max_coins = 50;

// Varaible
const int RENDER_DRAW_COLOR = 255;


#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define BLANK_TILE 0

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;

};

typedef struct Map
{
	int start_x_ = 0;
	int start_y_ = 0;

	int max_x_ ;
	int max_y_ ;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name_;

};

#endif