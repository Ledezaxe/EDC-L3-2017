
#include "sdlTest.h"
#include "sys/param.h"


const unsigned int max_with_screen = 1920;
const unsigned int max_heigth_screen = 1440;
const unsigned int min_with_screen = 480;
const unsigned int min_heigth_screen = 360;
const unsigned int max_size_tiles = 60;
const unsigned int min_size_tiles = 15;
unsigned int game_quit = 0;

unsigned int config_screen_width = 480;
unsigned int config_screen_heigth = 360;
int pause = 0;
int tiles_size = 25;
int posX = 0 , posY = 0;
int posX_tiles = 0 , posY_tiles = 0;

void init_mouse_position(){
  mouse_pos.x=-1;
  mouse_pos.y=-1;
  mouse_pos.x1=-1;
  mouse_pos.y1=-1;
}

Tile *** init_Tiles( Tile *** test , SDL_Surface * screen , TTF_Font * police ,unsigned int grid_width,unsigned int grid_heigth )
{
  for ( int i = 0; i < grid_width; ++ i )
  {
    for ( int j = 0; j < grid_heigth; ++ j )
    {
      test[ i ][ j ] -> border -> h = tiles_size + 4;
      test[ i ][ j ] -> border -> w = tiles_size + 4;
      test[ i ][ j ] -> border -> x = i * tiles_size;
      test[ i ][ j ] -> border -> y = j * tiles_size;
      test[ i ][ j ] -> border_color = 0xFFFFFF;
      test[ i ][ j ] -> inner -> h = tiles_size;
      test[ i ][ j ] -> inner -> w = tiles_size;
      test[ i ][ j ] -> inner -> x = i * tiles_size + 2;
      test[ i ][ j ] -> inner -> y = j * tiles_size + 2;
      test[ i ][ j ] -> inner_color = 0x2ecc71;
      test[ i ][ j ] -> character_pos -> h = j * tiles_size;
      test[ i ][ j ] -> character_pos -> w = i * tiles_size;
      test[ i ][ j ] -> character_pos -> x = i * tiles_size + 5;
      test[ i ][ j ] -> character_pos -> y = j * tiles_size + 5;

    }
  }
  return test;
}

Tile * create_Tiles()
{
  Tile * tile = malloc( sizeof( Tile ));
  tile -> inner = malloc( sizeof( SDL_Rect ));
  tile -> inner_color = 0x000000;
  tile -> border = malloc( sizeof( SDL_Rect ));
  tile -> border_color = ( unsigned int ) 0x000000;
  tile -> character_pos = malloc( sizeof( SDL_Rect ));
  tile -> character_color = malloc( sizeof( SDL_Color ));
  tile -> character_color -> r = 0xe7;
  tile -> character_color -> g = 0x4c;
  tile -> character_color -> b = 0x3c;
  tile -> character = 'A';
  return tile;
}


Tile * changeColor( Tile * tile , Uint32 color )
{
  tile -> inner_color = color;
  return tile;
}

Tile *** create_nTiles( unsigned int i , unsigned int j )
{
  Tile *** this = calloc( i + 1 , sizeof( Tile ** ));
  for ( int k = 0; k < i; ++ k )
  {
    this[ k ] = calloc( j + 1 , sizeof( Tile * ));
    for ( int l = 0; l < j; ++ l )
    {
      this[ k ][ l ] = create_Tiles();
    }
  }
  return this;
}

int main( int argc , char * argv[] )
{
  FILE * fichier;

  grid_heigth=8;
  grid_width=8;

  Tile *** test = create_nTiles( grid_width , grid_heigth );


  SDL_Surface * screen , *  main_menu =SDL_CreateRGBSurface(SDL_SWSURFACE, config_screen_width, config_screen_width, 32,0,0,0,0);


  /* Initialize the SDL library */
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    fprintf( stderr , "Couldn'tile initialize SDL: %s\n" , SDL_GetError());
    exit( 1 );
  }
  if ( TTF_Init() == - 1 )
  {

    fprintf( stderr , "Erreur d'initialisation de TTF_Init : %s\n" , TTF_GetError());

    exit( EXIT_FAILURE );

  }

  SDL_WM_SetCaption( "test" , "test" );

  // screen = SDL_SetVideoMode( config_screen_width , config_screen_heigth , 32 , SDL_SWSURFACE | SDL_DOUBLEBUF |SDL_RESIZABLE);

  screen = SDL_SetVideoMode( config_screen_width , config_screen_heigth , 32 , SDL_SWSURFACE | SDL_DOUBLEBUF|SDL_RESIZABLE);


  if ( screen == NULL)
  {
    fprintf( stderr , "Couldn'tile set 640x480x32 video mode: %s\n" , SDL_GetError());
    exit( 1 );
  }

  //TTF_Font *police = NULL;
  SDL_Color * couleurNoire = malloc( sizeof( SDL_Color ));
  couleurNoire -> b = 255;
  couleurNoire -> g = 75;
  couleurNoire -> r = 0;


  TTF_Font * police = TTF_OpenFont( "arial.ttf" , tiles_size );

  TTF_SetFontStyle( police , TTF_STYLE_BOLD );
  if ( police == NULL)
  {
    printf( "TTF_Init: %s\n" , TTF_GetError());
    TTF_Quit();
    SDL_Quit();
    exit( 1 );
  }

  Tile * tile = create_Tiles();
  tile -> character = 'A';

  SDL_Event event;

  int x = - 1;
  int y = - 1;
  int x1 = - 1;
  int y1 = - 1;

  test = init_Tiles( test , screen , police , grid_width,grid_heigth );

  while ( ! game_quit )
  {
      for ( int i = 0; i < grid_width; ++ i )
      {
        for ( int j = 0; j < grid_heigth; ++ j )
        {
          if ( test[ i ][ j ] -> inner -> x > 0 && test[ i ][ j ] -> inner -> y > 0)
          {
            if(test[ i ][ j ] -> inner -> x > config_screen_width || test[ i ][ j ] -> inner -> y > config_screen_heigth){
              break;
            }
            test[ i ][ j ] -> border -> h = tiles_size + 4;
            test[ i ][ j ] -> border -> w = tiles_size + 4;
            test[ i ][ j ] -> inner -> h = tiles_size;
            test[ i ][ j ] -> inner -> w = tiles_size;
            test[ i ][ j ] -> character_pos -> h = j * tiles_size;
            test[ i ][ j ] -> character_pos -> w = i * tiles_size;
            test[ i ][ j ] -> inner -> h = tiles_size;
            test[ i ][ j ] -> inner -> w = tiles_size;
            test[ i ][ j ] -> character_surface = TTF_RenderGlyph_Solid( police , test[ i ][ j ] -> character , *tile -> character_color );
            if ( SDL_FillRect( screen , test[ i ][ j ] -> border , test[ i ][ j ] -> border_color ) != 0 )
            {
              printf( "Bug" );
            }
            if ( SDL_FillRect( screen , test[ i ][ j ] -> inner , test[ i ][ j ] -> inner_color ) != 0 )
            {
              printf( "Bug" );
            }
            SDL_BlitSurface( test[ i ][ j ] -> character_surface , NULL , screen , test[ i ][ j ] -> character_pos );
            SDL_FreeSurface( test[ i ][ j ] -> character_surface );

          }
        }
      }



    if ( SDL_PollEvent( &event ))
    {
      // Check for the quit message
      switch ( event . type )
      {

        case SDL_QUIT:
          game_quit = 1;
          break;
        case SDL_VIDEORESIZE:

          if(event.resize.h >max_heigth_screen)
            event.resize.h = max_heigth_screen;
          if(event.resize.h <min_heigth_screen)
            event.resize.h = min_heigth_screen;
          if(event.resize.w >max_with_screen)
            event.resize.h = max_with_screen;
          if(event.resize.h <min_with_screen)
            event.resize.h = min_with_screen;
          screen = SDL_SetVideoMode( event.resize.w , event.resize.h , 32 , SDL_SWSURFACE | SDL_DOUBLEBUF |SDL_RESIZABLE);

          break;
        case SDL_MOUSEBUTTONDOWN :
          if ( event . button . button == SDL_BUTTON_LEFT )
          {
            x = event . button . x / tiles_size;
            y = event . button . y / tiles_size;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          if ( event . button . button == SDL_BUTTON_LEFT )
          {

            x1 = event . button . x / tiles_size;
            y1 = event . button . y / tiles_size;
          }
          break;
        case SDL_KEYDOWN:
        {
          switch ( event . key . keysym . sym )
          {

            case SDLK_ESCAPE:
            {
              Uint8 * keystate = SDL_GetKeyState(NULL);
              if ( keystate[ SDLK_LALT ] )
              {
                game_quit = 1;
                break;
              }
              if ( pause )
              {
                pause = 0;
              }
              else
              {
                pause = 1;
              }
            }
              break;
            case SDLK_KP_PLUS:
            {
              if ( ! pause )
              {

                Uint8 * keystate = SDL_GetKeyState(NULL);
                TTF_CloseFont( police );
                SDL_FillRect( screen , &screen -> clip_rect , 0x00000 );
                if ( keystate[ SDLK_LCTRL ] )
                {
                  if ( tiles_size < max_size_tiles )
                  {
                    tiles_size += 10;

                  }
                  if ( tiles_size > max_size_tiles )
                  {
                    tiles_size = max_size_tiles;
                  }
                }
                else
                {
                  if ( tiles_size < max_size_tiles )
                  {
                    tiles_size += 1;
                  }
                }
                for ( int i = 0; i < grid_width; ++ i )
                {
                  for ( int j = 0; j < grid_heigth; ++ j )
                  {

                    test[ i ][ j ] -> border -> x = posX + ( i * tiles_size );
                    test[ i ][ j ] -> border -> y = posY + ( j * tiles_size );
                    test[ i ][ j ] -> inner -> x = posX + ( i * tiles_size ) + 2;
                    test[ i ][ j ] -> inner -> y = posY + ( j * tiles_size ) + 2;
                    test[ i ][ j ] -> character_pos -> x = posX + ( i * tiles_size ) + 5;
                    test[ i ][ j ] -> character_pos -> y = posY + ( j * tiles_size ) + 5;
                  }
                }
                TTF_OpenFont( "arial.ttf" , tiles_size );
                TTF_SetFontStyle( police , TTF_STYLE_BOLD );

              }
            }
              break;
            case SDLK_KP_MINUS:
            {
              if ( ! pause )
              {
                Uint8 * keystate = SDL_GetKeyState(NULL);
                TTF_CloseFont( police );
                SDL_FillRect( screen , &screen -> clip_rect , 0x00000 );
                if ( keystate[ SDLK_LCTRL ] )
                {
                  if ( tiles_size > min_size_tiles )
                  {
                    tiles_size -= 10;

                  }
                  if ( tiles_size < min_size_tiles )
                  {
                    tiles_size = min_size_tiles;
                  }
                }
                else
                {
                  if ( tiles_size > min_size_tiles )
                  {
                    tiles_size -= 1;
                  }

                }
                for ( int i = 0; i < grid_width; ++ i )
                {
                  for ( int j = 0; j < grid_heigth; ++ j )
                  {

                    test[ i ][ j ] -> border -> x = posX + ( i * tiles_size );
                    test[ i ][ j ] -> border -> y = posY + ( j * tiles_size );
                    test[ i ][ j ] -> inner -> x = posX + ( i * tiles_size ) + 2;
                    test[ i ][ j ] -> inner -> y = posY + ( j * tiles_size ) + 2;
                    test[ i ][ j ] -> character_pos -> x = posX + ( i * tiles_size ) + 5;
                    test[ i ][ j ] -> character_pos -> y = posY + ( j * tiles_size ) + 5;
                  }
                }
                TTF_OpenFont( "arial.ttf" , tiles_size );
                TTF_SetFontStyle( police , TTF_STYLE_BOLD );
              }
            }
              break;
            case SDLK_LEFT:
            {
              if ( ! pause )
              {
                posX -= 1 * tiles_size;
                for ( int i = 0; i < grid_width; ++ i )
                {
                  for ( int j = 0; j < grid_heigth; ++ j )
                  {


                    test[ i ][ j ] -> border -> x -= 1 * tiles_size;
                    test[ i ][ j ] -> inner -> x -= 1 * tiles_size;
                    test[ i ][ j ] -> character_pos -> x -= 1 * tiles_size;
                    SDL_FillRect( screen , &screen -> clip_rect , 0x00000 );
                  }
                }
              }
            }

              break;
            case SDLK_RIGHT:
            {
              if ( ! pause )
              {
                posX += 1 * tiles_size;
                for ( int i = 0; i < grid_width; ++ i )
                {
                  for ( int j = 0; j < grid_heigth; ++ j )
                  {


                    test[ i ][ j ] -> border -> x += 1 * tiles_size;
                    test[ i ][ j ] -> inner -> x += 1 * tiles_size;
                    test[ i ][ j ] -> character_pos -> x += 1 * tiles_size;
                    SDL_FillRect( screen , &screen -> clip_rect , 0x00000 );
                  }
                }

              }
            }
              break;
            case SDLK_UP:
            {
              if ( ! pause )
              {
                posY -= 1 * tiles_size;
                for ( int i = 0; i < grid_width; ++ i )
                {
                  for ( int j = 0; j < grid_heigth; ++ j )
                  {


                    test[ i ][ j ] -> border -> y -= 1 * tiles_size;
                    test[ i ][ j ] -> inner -> y -= 1 * tiles_size;
                    test[ i ][ j ] -> character_pos -> y -= 1 * tiles_size;
                    SDL_FillRect( screen , &screen -> clip_rect , 0x00000 );

                  }
                }
              }
            }
              break;
            case SDLK_DOWN:
            {
              if ( ! pause )
              {
                posY += 1 * tiles_size;
                for ( int i = 0; i < grid_width; ++ i )
                {
                  for ( int j = 0; j < grid_heigth; ++ j )
                  {


                    test[ i ][ j ] -> border -> y += 1 * tiles_size;
                    test[ i ][ j ] -> inner -> y += 1 * tiles_size;
                    test[ i ][ j ] -> character_pos -> y += 1 * tiles_size;
                    SDL_FillRect( screen , &screen -> clip_rect , 0x00000 );

                  }
                }
              }
            }
              break;
            default:
              break;
          }
        }

          break;

      }
    }


    if ( x != - 1 && y != - 1 && x1 != - 1 && y1 != - 1 )
    {

      if ( ! pause )
      {
        if ( x != x1 || y != y1 )
        {
          int posY_tile = posY / tiles_size;
          int posX_tile = posX / tiles_size;

          unsigned int size_word =MAX(MAX(x,x1)-MIN(x,x1),MAX(y,y1)-MIN(y,y1));
          char * word = calloc(size_word+1,sizeof(char));
          if ( x1 == x )
          {
            int cpt = 0;
            if ( y <= y1 )
            {

              for ( int i = - posY_tile + y; i <= - posY_tile + y1; ++ i )
              {
                if (i >= 0 && i < grid_heigth && - posX_tile + x >= 0 && - posX_tile + x < grid_width && cpt < grid_width )
                {
                  test[ - posX_tile + x ][ i ] = changeColor( test[ - posX_tile + x ][ i ] , 0xddbdcc );
                  word[ cpt ] = test[ - posX_tile + x ] [i]-> character;
                }
                cpt +=1;
              }
            }
            else
            {
              for ( int i = - posY_tile + y; i >= - posY_tile + y1; -- i )
              {
                if ( i >= 0 && i < grid_heigth && - posX_tile + x >= 0 && - posX_tile + x < grid_width && cpt<grid_width)
                {
                  test[ - posX_tile + x ][ i ] = changeColor( test[ - posX_tile + x ][ i ] , 0xddddcb );
                  word[cpt] =test[ - posX_tile + x ][ i ]->character;
                }
              }
            }
            x =-posX_tile + x;
            x1 =-posX_tile + x;
            y=- posY_tile + y;
            y1=- posY_tile + y1;
          }
          else if ( y1 == y )
          {
            if ( x <= x1 )
            {
              for ( int i = - posX_tile + x; i <= - posX_tile + x1; ++ i )
              {
                if ( i >= 0 && i < grid_width && - posX_tile + y >= 0 && - posX_tile + y < grid_heigth )
                {
                  test[ i ][ - posY_tile + y ] -> inner_color = 0xdddd00;
                  word[ i ] =test[ i ][ - posY_tile + y ]->character;
                }
              }

            }
            else
            {
              for ( int i = - posX_tile + x; i >= - posX_tile + x1; -- i )
              {
                if ( i >= 0 && i < grid_width && - posX_tile + y >= 0 && - posX_tile + y < grid_heigth )
                {
                  test[ i ][ - posY_tile + y ] -> inner_color = 0xdddd00;
                  word[ i ] = test[ i ][ - posY_tile + y ]->character;
                }

              }

            }
          }
          else
          {
            if ((( y - y1 ) / ( x - x1 )) == 1 || (( y - y1 ) / ( x - x1 )) == - 1 )
            {
              if (( x - x1 ) < 0 )
              {
                if (( y - y1 ) < 0 )
                {

                  for ( int i = 0; i <= ( x1 - posX_tile ) - ( x - posX_tile ); ++ i )
                  {
                    if ( x - posX_tile + i >= 0 && x - posX_tile + i < grid_width && y - posY_tile + i >= 0 && y - posY_tile + i < grid_heigth )
                    {
                      test[ x - posX_tile + i ][ y - posY_tile + i ] -> inner_color = 0xdddd00;
                      word[ i ] =test[ x - posX_tile + i ][ y - posY_tile + i ]->character;
                    }
                  }

                }
                else
                {
                  for ( int i = 0; i <= ( x1 - posX_tile ) - ( x - posX_tile ); ++ i )
                  {
                    if ( x - posX_tile + i >= 0 && x - posX_tile + i < grid_width && y - posY_tile - i >= 0 && y - posY_tile - i < grid_heigth )
                    {
                      test[ x - posX_tile + i ][ y - posY_tile - i ] -> inner_color = 0xdddd00;
                      word[ i ] =test[ x - posX_tile + i ][ y - posY_tile - i ]->character;
                    }
                  }
                }
              }
              else
              {
                if (( y - y1 ) < 0 )
                {
                  for ( int i = 0; i <= ( x - posX_tile ) - ( x1 - posX_tile ); ++ i )
                  {
                    if ( x - posX_tile - i >= 0 && x - posX_tile - i < grid_width && y - posY_tile + i >= 0 && y - posY_tile + i < grid_heigth )
                    {
                      test[ x - posX_tile - i ][ y - posY_tile + i ] -> inner_color = 0xdddd00;
                      word[ i ] =test[ x - posX_tile - i ][ y - posY_tile + i ]->character;
                    }
                  }
                }
                else
                {
                  for ( int i = 0; i <= ( x - posX_tile ) - ( x1 - posX_tile ); ++ i )
                  {
                    if ( x - posX_tile - i >= 0 && x - posX_tile - i < grid_width && y - posY_tile - i >= 0 && y - posY_tile - i < grid_heigth )
                    {
                      test[ x - posX_tile - i ][ y - posY_tile - i ] -> inner_color = 0xdddd00;
                      word[ i ] =test[ x - posX_tile - i ][ y - posY_tile - i ]->character;
                    }

                  }

                }
              }
            }
          }

          x=-posX_tile + x;
          x1=-posX_tile + x1;
          y=-posY_tile + y;
          y1=-posY_tile + y1;
          fprintf(stdout,"FOUND %s %d %d %d %d\n", word,x,y,x1,y1);
        }
      }
         x = - 1;
         y = - 1;
         y1 = - 1;
         x1 = - 1;

    }
    SDL_Flip( screen );

  }
  SDL_FreeSurface( screen );
  SDL_Quit();

}