#include <sys/time.h>

struct timespec start, end;

void start_timer() {
  clock_gettime(CLOCK_MONOTONIC, &start);
}

void stop_timer() {
  clock_gettime(CLOCK_MONOTONIC, &end);
}

time_t get_ellapsed_time_ms() {
  return ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000) / 1000;
}
