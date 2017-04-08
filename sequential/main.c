#include <stdio.h>
#include <stdlib.h>
#include "../utils/arrays.h"
#include "../utils/timers.h"

static long long reduce(int* array, int size) {
  long long result = 0;

  for (int i = 0; i < size; i += 1) {
    result += array[i];
  }

  return result;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: ./c_parallel_sum_sequential array_size\n");
    exit(1);
  }

  int array_size = atoi(argv[1]);

  if (array_size <= 0 || array_size > 2000000000) {
    printf("array_size should be between 1 and 2000000000 included\n");
    exit(1);
  }

  printf("Generating array of size %d... ", array_size);
  fflush(stdout);
  int* array = generate_array(array_size);
  printf("Done!\n");

  printf("Reducing array... ");
  fflush(stdout);
  start_timer();
  long long result = reduce(array, array_size);
  stop_timer();
  printf("Done!\n");
  printf("Time took to reduce array: %lums\n", get_ellapsed_time_ms());
  printf("Result: %lld\n", result);

  clean_array(array);
  return 0;
}
