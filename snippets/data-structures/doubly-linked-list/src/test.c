#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "list.h"
#include "printing.h"
#include "defs.h"

static int intcmp(const int *a, const int *b)
{
  return *a - *b;
}


static void freeint(void *item) { free((int*)item); }

void test_intcmp()
{
  int a = 1;
  int b = 2;
  int c = 1;

  assert(intcmp(&a, &b) < 0);
  assert(intcmp(&b, &a) > 0);
  assert(intcmp(&a, &c) == 0);
  pr_info("test_intcmp: PASSED\n");
}


void test_create_destroy()
{
  list_t *list = list_create((cmp_fn)intcmp);
  assert(list != NULL);
  assert(list_length(list) == 0);
  list_destroy(list, (free_fn)freeint);
  pr_info("test_create_destroy: PASSED\n");
}

void test_addfirst()
{
  list_t *list = list_create((cmp_fn)intcmp);

  int a = 10;
  int b = 20;
  char c = 'c';
  assert(list_addfirst(list, &a) == 0);
  assert(list_length(list) == 1);
  assert(list_addfirst(list, &b) == 0);
  assert(list_length(list) == 2);
  assert(list_addfirst(list, &c) == 0);
  pr_info("test_addfirst: PASSED\n");
}

void test_addlast()
{
  
}


void test_popfirst()
{
  
}

void test_poplast();

void test_remove();

void test_contains();

void test_sort();

void test_create_destroy_iter();

void test_has_next();

void test_next();

void test_resetiter();

