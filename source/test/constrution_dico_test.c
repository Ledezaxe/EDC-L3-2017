#include "construction.h"

int main()
{
  srand(time(NULL));

  char** dico = create_dictionary("../dico/dictionary.dic");

  Grid* test = filling(dico, 50, 25, 1500);

  display_grid(test);

  grid_destroy(test);
  destroy_dictionary(dico);

  return EXIT_SUCCESS;
}
