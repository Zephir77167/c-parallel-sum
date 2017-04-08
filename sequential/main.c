#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>

#define ARRAY_SIZE 2000000000

static long long reduce(int* array) {
  long long result = 0;

  for (int i = 0; i < ARRAY_SIZE; i += 1) {
    result += array[i];
  }

  return result;
}

void clean_array(int* array) {
  free(array);
}

static int* generate_array() {
  int* array = malloc(sizeof(int) * ARRAY_SIZE);

  srand(20172017);
  for (int i = 0; i < ARRAY_SIZE; i += 1) {
    array[i] = rand();
  }

  return array;
}

int main() {
  struct timespec start, end;

  printf("Generating array of size %d... ", ARRAY_SIZE);
  fflush(stdout);
  int* array = generate_array();
  printf("Done!\n");

  printf("Reducing array... ");
  fflush(stdout);
  clock_gettime(CLOCK_MONOTONIC, &start);
  long long result = reduce(array);
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("Done!\n");
  time_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
  printf("Time took to reduce array: %lums\n", delta_us / 1000);
  printf("Result: %lld\n", result);

  clean_array(array);
  return 0;
}
