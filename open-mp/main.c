#include <stdio.h>
#include "../utils/args.h"
#include "../utils/arrays.h"
#include "../utils/timers.h"

static long long reduce(int* array, int size) {
  long long result = array[0];

  #pragma omp parallel for reduction (+: result)
  for (int i = 1; i < size; i += 1) {
    result += array[i];
  }

  return result;
}

int main(int argc, char** argv) {
  int array_size = get_array_size_from_args(argc, argv);
  int* array = generate_array(array_size);

  printf("Reducing array... ");
  fflush(stdout);
  start_timer();
  long long result = reduce(array, array_size);
  stop_timer();
  printf("Done!\n");
  printf("Time took to reduce array: %lums\n", get_ellapsed_time_ms());
  printf("Result: %lld\n", result);

  clean_array(&array);
  return 0;
}
