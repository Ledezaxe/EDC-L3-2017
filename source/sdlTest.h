//
// Created by nfoissac on 22/11/16.
//

#ifndef MOT_MELE_SDLTEST_H
#define MOT_MELE_SDLTEST_H

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL_ttf.h>


typedef struct Tuile Tuile;
typedef struct Mouse_Pos Mouse_Pos;


struct Mouse_Pos
{
  unsigned int x;
  unsigned int y;
  unsigned int x1;
  unsigned int y1;
};

struct Tuile
{

  SDL_Rect * interne;
  SDL_Rect * externe;
  Uint32 couleur;
  Uint32 c2;
  char c;

};

typedef struct Tile Tile;

struct Tile
{
  SDL_Rect * inner;
  Uint32 inner_color;
  SDL_Rect * border;
  Uint32 border_color;
  char character;
  SDL_Rect * character_pos;
  SDL_Surface * character_surface;
  SDL_Color * character_color;
};

Tile * create_Tiles();
Tile * changeColor( Tile * tile , Uint32 color );

void zoom_up1();
void zoom_up10();
void zoom_down1();
void zoom_down10();

void init_mouse_position();
Mouse_Pos mouse_pos;

const unsigned int width_screen;

const unsigned int color_screen;

const unsigned int max_with_screen;
const unsigned int max_heigth_screen;
const unsigned int min_with_screen;
const unsigned int min_heigth_screen;
const unsigned int max_size_tiles;
const unsigned int min_size_tiles;

unsigned int config_screen_width;
unsigned int config_screen_heigth;

unsigned int grid_width;
unsigned int grid_heigth;

unsigned int game_quit;
unsigned int game_pause_menu;
unsigned int game_option_menu;
unsigned int game_start_menu;
#endif //MOT_MELE_SDLTEST_H
