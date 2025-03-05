#include <stdio.h>
#include <stdlib.h>

#include "test.h"


int main()
{
  test_intcmp();
  test_create_destroy();
  test_addfirst();
  test_addlast();
  test_popfirst();
  return EXIT_SUCCESS;
} 
