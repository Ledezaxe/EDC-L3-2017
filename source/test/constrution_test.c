#include "construction.h"

int main()
{
  srand(time(NULL));

  char** words = malloc(13 * sizeof(char *));

  words[0] = strdup("GOURDE");
  words[1] = strdup("ETE");
  words[2] = strdup("SKATER");
  words[3] = strdup("KIWI");
  words[4] = strdup("GITE");
  words[5] = strdup("SCIER");
  words[6] = strdup("FOULE");
  words[7] = strdup("FUME");
  words[8] = strdup("EFFIGIE");
  words[9] = strdup("KAYAK");
  words[10] = strdup("PARTIE");
  words[11] = strdup("ATTENTION");
  words[12] = NULL;

  Grid* test = filling(words, 15, 15, 10);

  display_grid(test);

  grid_destroy(test);

  return EXIT_SUCCESS;
}
