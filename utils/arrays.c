#include <stdlib.h>

int* generate_array(int size) {
  int* array = malloc(sizeof(int) * size);

  srand(20172017);
  for (int i = 0; i < size; i += 1) {
    array[i] = rand();
  }

  return array;
}

void clean_array(int* array) {
  if (array != NULL) {
    free(array);
  }
}
