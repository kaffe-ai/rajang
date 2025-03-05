#include <stdio.h>
#include <stdlib.h>


typedef struct string String_t;
struct string {
  char *characters;
  size_t length;
};
