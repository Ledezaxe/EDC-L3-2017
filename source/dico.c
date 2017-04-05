//
// Created by nfoissac on 18/11/16.
//



#include "dico.h"

unsigned int dictionary_line_counter;
unsigned int dictionary_line_pointer;

unsigned int max_size_random_ln = 26;

FILE * open_dictionary( char * path );
FILE * ropen_dictionary( FILE * file , char * path );
void close_dictionary( FILE * file );
int count_dictionary( FILE * file );
char ** create_dictionary( char * path );

FILE * open_dictionary( char * path )
{
  errno = 0;
  FILE * this;
  this = fopen( path , "r" );
  if ( errno != 0 )
  {
    fprintf( stderr , "Impossible d'ouvrir le fichier '%s': %s.\n" , path , strerror(errno));
    exit( EXIT_FAILURE );
  }
  return this;
}

FILE * ropen_dictionary( FILE * file , char * path )
{
  close_dictionary( file );
  file = open_dictionary( path );
  return file;
}

void close_dictionary( FILE * file )
{
  fclose( file );
}

int count_dictionary( FILE * file )
{

  if ( file == NULL)
  {
    fprintf( stderr , "Impossible de compter les ligne du fichier : File is NULL." );
    exit( EXIT_FAILURE );
  }
  int buffChar;
  int lines = 0;
  int compChar = '\0';
  while (( buffChar = fgetc( file )) != EOF)
  {
    if ( buffChar == '\n' )
    {
      lines ++;
    }
    compChar = buffChar;
  }

  if ( compChar != '\n' )
  {
    lines ++;
  }

  return lines;
}

void destroy_dictionary( char ** dictionary )
{
  unsigned int pointer_dictionary = 0;
  while ( pointer_dictionary != dictionary_line_counter && dictionary[ pointer_dictionary ] != NULL)
  {
    free( dictionary[ pointer_dictionary ] );
    dictionary[ pointer_dictionary ] = NULL;
    pointer_dictionary ++;
  }
  free( dictionary );
}
char ** create_dictionary( char * path )
{
  errno = 0;
  FILE * dictionary_file = open_dictionary( path );
  dictionary_line_counter = count_dictionary( dictionary_file );
  dictionary_line_pointer = 0;
  dictionary_file = ropen_dictionary( dictionary_file , path );
  char ** this = malloc( sizeof( char * ) * dictionary_line_counter );
  if ( this == NULL)
  {
    fprintf( stderr , "Impossible de créer le dictionnaire : %s .\n" , strerror(errno));
    exit( EXIT_FAILURE );
  }
  char * bufferDictionary = calloc( 28 , sizeof( char ));
  if ( bufferDictionary == NULL)
  {
    fprintf( stderr , "Impossible de créer le buffer du dictionnaire : %s .\n" , strerror(errno));
    exit( EXIT_FAILURE );
  }
  while ( fgets( bufferDictionary , 28 , dictionary_file ) != NULL)
  {
    int sizeBuffer = strlen( bufferDictionary );
    char * word = malloc( sizeof( char ) * sizeBuffer );
    if ( word == NULL)
    {
      fprintf( stderr , "Impossible de créer un mot du dictionnaire : %s .\n" , strerror(errno));
      exit( EXIT_FAILURE );
    }
    memcpy( word , bufferDictionary , sizeBuffer );
    if ( dictionary_line_pointer != dictionary_line_counter - 1 )
    {
      word[ sizeBuffer - 1 ] = '\0';
    }
    this[ dictionary_line_pointer ] = word;
    dictionary_line_pointer ++;
  }
  free( bufferDictionary );
  close_dictionary( dictionary_file );
  return this;
}

char * random_word_dictionary( char ** dictionary )
{
  srand( time( 0 ) ^ rand());
  int random_pointer = rand() % ( dictionary_line_counter );
  int random_word_size = strlen( dictionary[ random_pointer ] );
  char * this = malloc( sizeof( char ) * random_word_size + 1 );
  if ( this == NULL)
  {
    fprintf( stderr , "Impossible de créer un mot aléatoire du dictionnaire : %s .\n" , strerror(errno));
    exit( EXIT_FAILURE );
  }
  memcpy( this , dictionary[ random_pointer ] , random_word_size );
  this[ random_word_size ] = '\0';
  return this;
}

char ** random_n_word_dictionary( char ** dictionary , unsigned int number )
{
  char ** this = calloc( number + 1 , sizeof( char * ));
  if ( this == NULL)
  {
    fprintf( stderr , "Impossible de créer une liste aléatoire de mot du dictionnaire : %s .\n" , strerror(errno));
    exit( EXIT_FAILURE );
  }
  for ( unsigned int i = 0; i < number; ++ i )
  {
    this[ i ] = random_word_dictionary( dictionary );
  }
  return this;
}

char ** random_ln_word_dictionary( char ** dictionary , unsigned int number , unsigned int min , unsigned int max )
{
  unsigned int i = 0;
  int counter = 0;
  unsigned int size_word = 0;
  while ( dictionary_line_counter - 1 != i && dictionary[ i ] != NULL)
  {
    size_word = strlen( dictionary[ i ] );
    if ( size_word >= min && size_word <= max )
    {
      counter ++;
    }
    i ++;
  }
  char ** buffer = calloc( sizeof( dictionary ) , sizeof( char * ) * counter + 1 );
  if ( buffer == NULL)
  {
    fprintf( stderr , "Impossible de trier le dictionnaire : %s .\n" , strerror(errno));
    exit( EXIT_FAILURE );
  }
  i = 0;
  counter = 0;
  while ( dictionary_line_counter - 1 != i && dictionary[ i ] != NULL)
  {
    size_word = strlen( dictionary[ i ] );
    if ( size_word >= min && size_word <= max )
    {
      buffer[ counter ] = dictionary[ i ];
      counter ++;
    }
    i ++;
  }

  char ** this = calloc( sizeof( dictionary ) , sizeof( char * ) * number );
  if ( this == NULL)
  {
    fprintf( stderr , "Impossible de trier le dictionnaire : %s .\n" , strerror(errno));
    exit( EXIT_FAILURE );
  }
  srand( time( 0 ) ^ rand());

  for ( unsigned int j = 0; j < number; ++ j )
  {
    int random_pointer = rand() % ( counter );
    int random_word_size = strlen( buffer[ random_pointer ] );
    char * this_word = malloc( sizeof( char ) * random_word_size + 1 );
    if ( this_word == NULL)
    {
      fprintf( stderr , "Impossible de créer un mot aléatoire du dictionnaire : %s .\n" , strerror(errno));
      exit( EXIT_FAILURE );
    }
    memcpy( this_word , buffer[ random_pointer ] , random_word_size );
    this_word[ random_word_size ] = '\0';
    this[ j ] = this_word;
  }
  free( buffer );

  return this;
}

void strrev( char * s )
{
  char * end = strchr( s , 0 );

  while ( s + 1 < end )
  {
    const char tmp = *s;
    -- end;
    *s = *end;
    *end = tmp;
    ++ s;
  }
}
