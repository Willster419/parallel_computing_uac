/*
  Block (multi line comments are inside the "/ *" and "* /" characters

*/

// Single line comments are with two slashes

// Compiler directives are listed as with the pound (#) symbol for the pre-processor
// https://en.wikipedia.org/wiki/Directive_(programming)
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>

#define SIZE 1000

// In C, you need to define method signatures before you can use them
// https://en.wikipedia.org/wiki/Type_signature#Method_signature
static void test_fail();
/*
  In c, the main program starts with "int main"
  The "int", is the return code, the 
*/
int main(int argc, char **argv) {

  // In this specification of C, you must define your variables before you ocan use them
  int test1;

  // A variable with an astrick is called a pointer
  // A pointer is an address to a value in memory
  // https://en.wikipedia.org/wiki/Pointer_(computer_programming)
  // https://tekslate.com/explain-different-types-pointers-c-language
  // https://www.tutorialspoint.com/cprogramming/c_pointers.htm
  int *test2;

  // Init the value of test1
  // The variable test1 contains the value 4
  test1 = 4;

  // Print it to the console
  // Use the "&" symbol to get the address of a variable
  // You can directly print variables by specifying additional parameters after your string
  // https://www.codingunit.com/printf-format-specifiers-format-conversions-and-formatted-output
  printf("The value of test1 is %d\n", test1);
  printf("The address of test1 is %x\n", &test1);

  // Values take up application space in memory
  // Use the sizeof() function, with a data type, to know how much bits it will take
  printf("The int type takes up %d bytes (%d bits)\n", sizeof(int), sizeof(int)*8);

  // Set the address of the test2 variable to 1 above test1
  // Using sizeof will return how much space the intiger type takes up
  // https://www.tutorialspoint.com/cprogramming/c_data_types.htm
  // To write the *address* of test2, type 'test2'
  // To write the *value* of test2, type '*test2'
  test2 = &test1 + sizeof(int);

  // To access the *address* of test2, type 'test2'
  // To access the *value* of test 2, type '*test2'
  printf("The address of test2 is %x\n", test2);

  // Set the value of the pointer
  *test2 = 8;
  // This would be wrong because you setting the address of the pointer, not the value inside the address
  // test2 = 8;

  printf("The value of test2 is %d\n", *test2);

  exit(0);
}

static void test_fail()
{
  printf("\n");
  exit(1);
}
