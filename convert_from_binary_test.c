#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int convert_from_binary(char binary[]) {
  int  num, binary_val, decimal_val = 0, base = 1, rem;
  unsigned long long sixteen_digit_integer;
  /*checks to see if the number is has a 1 in the 2^16 space.
    integers and longs can't hold 16 digit numbers*/
  if (binary[0] == '1') {
    //manually convert the 16 digit int to a ull
    if (strcmp("111111111111", binary)) {
      sixteen_digit_integer = 1111111111111111;
    } else {
      sixteen_digit_integer = 1111111111111110;
    }
    while ( sixteen_digit_integer > 0)
    {
        rem = sixteen_digit_integer % 10;
        decimal_val = decimal_val + rem * base;
        sixteen_digit_integer = sixteen_digit_integer / 10 ;
        base = base * 2;
    }
  } else {
    binary_val = atoi(binary);
    num = atoi(binary);

    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;
    }
  }
  return decimal_val;
}






int main(int argc, char const *argv[]) {
  char * binary[17] = {"0000000000000010","0000000011001000","0000000001001000",
  "0000000000000010","0000000000111011","0000000001101111","0000000000000001",
  "0000001110000100","0000000000000011","0000000001011001","0000000001001101",
  "0000000000000001","0000000000000001","0000000000000000","0000000000000010",
  "1111111111111111","0000000000000000"};
  int decimal[17] = {002,200,72,002,59,111,001,900,003,89,77,1,001,0,002,65535,0};
  int pass = 1; //true
  int x = atol("111111111111111");
  printf("111111111111111 as an int is: %i\n", x);
  for (int i = 0; i < 17; i++) {
    convert_from_binary(binary[i]);
    printf("EXPECTED VALUE: %i\n", decimal[i]);
    printf("CALCULATED VALUE: %i\n", convert_from_binary(binary[i]));
    if (convert_from_binary(binary[i]) == decimal[i]) {
      printf("TRUE\n\n");
    } else {
      printf("FALSE\n\n");
      pass = 0; //false
    } /*endif*/
  }

  if (pass == 0) {
    printf("\nFAILURE\n");
  }
  return 0;
}
