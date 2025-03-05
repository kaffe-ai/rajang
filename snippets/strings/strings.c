#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct string String_t;
struct string {
  size_t length;
  size_t capacity;
  char data[];
};


String_t *string_create(char *cstr, size_t initial_capacity) {
  size_t len = strlen(cstr);
  if (initial_capacity < len) initial_capacity = len; // Ensure minimal capacity
  
  String_t *s;
  s = malloc(sizeof(String_t) + initial_capacity + 1); // +1 for null terminator
  if (!s) return NULL;
  
  s->length = len;
  s->capacity = initial_capacity;
  memcpy(s->data, cstr, len + 1); // Copy data and null terminator
  return s;
}

void string_free(String_t *s) { free(s); }
