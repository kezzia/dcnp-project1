#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Type Amount Number1 Number2 … NumberN --> Type Amount Number1, Number2, … , NumberN
//0000 0010 1000111 11111111 --> 0001 002 71,255

// converts ascii codes into binary numbers (unpadded)
long convert_to_binary(long decimal_num) {
    long num, remainder, base = 1, binary = 0, no_of_1s = 0;
    num = decimal_num;
    while (num > 0)
    {
        remainder = num % 2;
        /*  To count no.of 1s */
        if (remainder == 1)
        {
            no_of_1s++;
        }
        binary = binary + remainder * base;
        num = num / 2;
        base = base * 10;
    }
    return binary;
}

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


/*quick and dirty function that returns the degree of an integer */
int intlen(long x) {
    if(x>=10000000000000000) return 17;
    if(x>=1000000000000000) return 16; //65535 converts to 1111 1111 1111 1111, which has 16 bits
    if(x>=100000000000000) return 15;
    if(x>=10000000000000) return 14;
    if(x>=1000000000000) return 13;
    if(x>=100000000000) return 12;
    if(x>=10000000000) return 11;
    if(x>=1000000000) return 10;
    if(x>=100000000) return 9;
    if(x>=10000000) return 8;
    if(x>=1000000) return 7;
    if(x>=100000) return 6;
    if(x>=10000) return 5;
    if(x>=1000) return 4;
    if(x>=100) return 3;
    if(x>=10) return 2;
    return 1;
}


int convert_type_0(char input_file_path[], char output_file_target[]) {

}


int convert_type_1(char input_file_path[], char output_file_target[]) {

}


int type_0_translation(char input_file_path[], char output_file_target[]) {
  printf("RUNNING TYPE 0 TRANSLATION\n");
  FILE * fp;
  FILE * fn;
  char str[60];
  fp = fopen(input_file_path , "r");
  fn = fopen(output_file_target,"w");

  if(fp == NULL) {
     perror("Error opening file");
     return(-1);
  }
  while( fgets (str, 60, fp)!=NULL ) {
     /* Print each line */
     printf("\n%s\n", "ORIGINAL STRING:");
     printf("%s", str);

     fprintf(fn, str);
  }
  fclose(fp);
  fclose(fn);
  return 0;
}


int type_1_translation(char input_file_path[], char output_file_target[]) {
   printf("RUNNING TYPE 1 TRANSLATION\n");
   FILE *fp;
   FILE * fn;
   char str[60];
   char super_string[60];
   int super_string_index = 0;

   /* opening file for reading */
   fp = fopen(input_file_path , "r");
   fn = fopen(output_file_target,"w");

   if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   }
   while( fgets (str, 60, fp)!=NULL ) {
      /* Print each line */
      printf("\n%s\n", "ORIGINAL STRING:");
      printf("%s", str);

      // Removing all commas from the string

      //check for the presence of a comma to start
      char *ptr = strchr(str, ',');
      //while there is a Comma
      while(ptr) {
        //printf("\n%s\n", "There are still commas in the string");
        // find its index
        int index = ptr - str;
        //printf("Comma at index %i\n", index);
        // replace the comma with a space
        str[index] = ' ';
        //printf("New string: %s", str);

        //check for commas again
        ptr = strchr(str, ',');
      }
      //printf("There are no more commas in this string\n");

      ptr = strstr(str, " ");
      while (ptr) {
        //setting this to 6 because the longest possible decimal is 6 digits long.
        char string_to_convert[7];
        char remaining_string[60]; // set to 60 just cuz

        //printf("\nptr is:%s\n", ptr);
        // find the index of the nearest space
        int index = ptr - str;
        //printf("Space index at: %i\n", index);
        //copy everything before the space we find into a new string
        for (int i = 0; i < index; i++) {
          string_to_convert[i] = str[i];
        }
        //copy everything after the space we find into a new string
        int a = 0;
        for (int i = (index + 1); i < 60; i++) {
          remaining_string[a] = str[i];
          a++;
        }

        //clear str and copy remaining_string into it
        for (int i=0; i < 60; i++) {
          str[i] = '\0';
        }
        strcpy(str, remaining_string);
        //printf("str is %i characters long\n", strlen(str));
        //printf("Converting: %s to binary\n", string_to_convert);
            // split strings into binary
             int char_as_int;
             int padding_required;
             char padded_binary[17];
             // convert ascii codes into decimals
             char_as_int = atoi(string_to_convert);
             //printf("%s as an int is %i\n", string_to_convert, char_as_int);
             long binary = convert_to_binary(char_as_int);
             //printf("The binary equivalent is %ld\n", binary);

             // find the length of the binary number
             padding_required = 16 - intlen(binary);
             if (padding_required == 0) {
               //printf("The number is two bytes long. No padding required\n");
               char sixteen_bit_string[17];
               sprintf(sixteen_bit_string, "%ld", binary);
               //printf("Adding %s to super_string\n", sixteen_bit_string);
               if (super_string_index < 59) {
                   strcat(super_string, sixteen_bit_string);
                   strcat(super_string, " ");
                   //printf("Adding %c to superstring\n", padded_binary[i]);
                   //printf("%c was added to the superstring\n", super_string[super_string_index]);
                 super_string_index += strlen(sixteen_bit_string) - 2;
               } else {
                 //printf("Super string full. Discarding\n");
               }

               //printf("super_string: %s\n", super_string);
               //printf("\n");

             } else if (padding_required > 0) {
               /* if the binary number has too few bits, add leading zeroes equal to
               * (16 - len of number) or (3 - len of_number)
               */
              // printf("The number is too short. Padding.\n");
               //printf("%i 0's are required\n", padding_required);
               for (int j = 0; j < padding_required; j++) {
                 // insert the correct # of leading zeros into a string
                 padded_binary[j] = '0';
               }
               // converts integer into a string
               char placeholder_str[9];
               sprintf(placeholder_str, "%ld", binary);
               int k = 0;
               // copy the binary number into that same string
               for (int j = padding_required; j < 17; j++) {
                 padded_binary[j] = placeholder_str[k];
                 k =  k + 1;
               }
               //printf("The padded binary_num is: %s\n", padded_binary);
               //printf("Adding %s to super_string\n", padded_binary);
               if (super_string_index < 59) {
                   strcat(super_string, padded_binary);
                   strcat(super_string, " ");
                   //printf("Adding %c to superstring\n", padded_binary[i]);
                   //printf("%c was added to the superstring\n", super_string[super_string_index]);
                 super_string_index += strlen(padded_binary) - 2;
               } else {
                 //printf("Super string full. Discarding\n");
               }

               //printf("super_string: %s\n", super_string);
               //printf("\n");
             } else {
               //printf("ERROR: This digit is longer than 2 bytes. Discarding\n");
             }
        //printf("Remaining string is:%s\n", str);
        ptr = strstr(str, " ");
        super_string_index++;

      }
      // convert the last number with no space after it
      char final_string[7];
      memcpy(final_string, str, 7);
      //printf("Converting: %s to binary\n", final_string);
      //printf("The final string is %i characters long\n", strlen(final_string));
      int char_as_int;
      int padding_required;
      char padded_binary[17];
      // convert ascii codes into decimals
      char_as_int = atoi(final_string);
      //printf("%s as an int is %i\n", string_to_convert, char_as_int);
      long binary = convert_to_binary(char_as_int);
      //printf("The binary equivalent is %ld\n", binary);

      // find the length of the binary number
      padding_required = 16 - intlen(binary);
      if (padding_required == 0) {
        //printf("The number is two bytes long. No padding required\n");
        char sixteen_bit_string[17];
        sprintf(sixteen_bit_string, "%ld", binary);

        //printf("Adding %s to super_string\n", sixteen_bit_string);
        if (super_string_index < 59) {
            strncpy(super_string, sixteen_bit_string, 17);
            //printf("Adding %c to superstring\n", padded_binary[i]);
            //printf("%c was added to the superstring\n", super_string[super_string_index]);
            super_string_index += strlen(sixteen_bit_string) - 2;
          }
        else {
          //printf("Super string full. Discarding\n");
        }

      } else if (padding_required > 0) {
        /* if the binary number has too few bits, add leading zeroes equal to
        * (16 - len of number)
        */
       // printf("The number is too short. Padding.\n");
        //printf("%i 0's are required\n", padding_required);
        for (int j = 0; j < padding_required; j++) {
          // insert the correct # of leading zeros into a string
          padded_binary[j] = '0';
        }
        // converts integer into a string
        char placeholder_str[17];
        sprintf(placeholder_str, "%ld", binary);
        int k = 0;
        // copy the binary number into that same string
        for (int j = padding_required; j < 17; j++) {
          padded_binary[j] = placeholder_str[k];
          k =  k + 1;
        }
        //printf("The padded binary_num is: %s\n", padded_binary);
        //printf("Adding %s to super_string\n", padded_binary);
        if (super_string_index < 59) {
            strcat(super_string, padded_binary);
            strcat(super_string, " ");
            //printf("Adding %c to superstring\n", padded_binary[i]);
            //printf("%c was added to the superstring\n", super_string[super_string_index]);
          super_string_index += strlen(padded_binary) - 2;
        } else {
          //printf("Super string full. Discarding\n");
        }
      } else {
        //printf("ERROR: This digit is longer than 2 bytes. Discarding\n");
      }

      //reset this so we know the first one is the number
      super_string_index = 0;
      printf("CONVERTED STRING:\n %s\n", super_string);
      printf("\n");
      strcat(super_string, "\n");
      fprintf(fn, super_string);

      //clear superstring and reset the index for the next entry
      for (int i = 0; i < 59; i++) {
        super_string[i] = '\0';
      }
      super_string_index = 0;
   }

   fclose(fp);
   fclose(fn);
   return(0);
}

int type_2_translation(char input_file_path[], char output_file_target[]) {
  printf("RUNNING TYPE 2 TRANSLATION\n");
  FILE * fp;
  FILE * fn;
  char str[60];
  char splitStrings[10][17]; // we can store 10 words of 17 chars
  char super_string[60];
  char dec_as_string[10];
  fp = fopen(input_file_path , "r");
  fn = fopen(output_file_target,"w");
  int i, j, count;

  if(fp == NULL) {
     perror("Error opening file");
     return(-1);
  }

  char temp_dec_as_string[4];
  int space_number = 1;
  while( fgets (str, 60, fp)!=NULL ) {
  int numbers_in_string;
  j = 0; count = 0;
    for (i = 0; i <= strlen(str); i++) {
      //if space or null found, assign null to splitStrings[count]
      if ((str[i] == ' ') || (str[i] == '\0')) {
        splitStrings[count][j] ='\0';
        count++;
        j = 0;
      } else {
        splitStrings[count][j] = str[i];
        j++;
      }/*endif*/
    } /* endfor */

    //convert only if it's type 0
    if (strcmp(splitStrings[0],"0") == 0) {
        printf("\nORIGINAL STRING: %s",str);
        strcat(super_string, "1 ");
        //the number of numbers in the string will be equal to this first one
        numbers_in_string = convert_from_binary(splitStrings[1]);
        //printf("There are %i numbers in the string and %i commas to place\n", numbers_in_string, (numbers_in_string-1));
        int number_of_commas_placed = 0;
        for(i=1; i < count; i++) {
          int dec = convert_from_binary(splitStrings[i]);

          if (i == 1) {
            int padding_required = 3 - intlen(dec);
            if (padding_required == 1) {
              sprintf(dec_as_string, "0%i", dec);
              strcat(super_string, dec_as_string);
            } else if (padding_required == 2) {
              sprintf(dec_as_string, "00%i", dec);
              strcat(super_string, dec_as_string);
            }
          } else {
            sprintf(dec_as_string, "%i", dec);
            strcat(super_string, dec_as_string);
          }
          if (space_number == 1) {
            strcat(super_string, " ");
          } else if ((space_number > 1)
            && (number_of_commas_placed < (numbers_in_string-1))) {
            strcat(super_string, ",");
            number_of_commas_placed++;
          }
          space_number++;
        }/* endfor*/
        fprintf(fn, "%s\n", super_string);
        printf("CONVERTED STRING: %s\n", super_string);
        // clear super_string for the next numbers
        memset(super_string,0,strlen(super_string));
        space_number = 1;
      } /*endif*/
      else { //if type = 1 just copy it in
        fprintf(fn, "%s\n", str);
      }
    } /*endwhile*/
  fclose(fp);
  fclose(fn);
  return 0;
}


int type_3_translation(char input_file_path[], char output_file_target[]) {
  printf("This transformation type is not yet supported\n");
  return 0;
}
