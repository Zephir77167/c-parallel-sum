#include <stdlib.h>
#include <stdio.h>

int* generate_array(int size) {
  printf("Generating array of size %d... ", size);
  fflush(stdout);

  int* array = malloc(sizeof(int) * size);

  srand(20172017);
  for (int i = 0; i < size; i += 1) {
    array[i] = rand();
  }

  printf("Done!\n");
  return array;
}

void clean_array(int** array) {
  if (*array != NULL) {
    free(*array);
    *array = NULL;
  }
}
