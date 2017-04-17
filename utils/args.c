//
// Created by adrie on 17/04/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "args.h"

int get_array_size_from_args(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: %s array_size\n", argv[0]);
    exit(1);
  }

  int array_size = atoi(argv[1]);

  if (array_size <= 0 || array_size > 2000000000) {
    printf("array_size should be between 1 and 2000000000 included\n");
    exit(1);
  }

  return array_size;
}
