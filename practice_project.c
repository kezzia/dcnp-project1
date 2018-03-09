#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int main () {
   FILE *fp;
   char str[60];
   char super_string[60];
   int super_string_index = 0;

   /* opening file for reading */
   fp = fopen("test_file.txt" , "r");
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
        char string_to_convert[6] = {'\0','\0','\0','\0','\0','\0'};
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
             char padded_binary[8];
             // convert ascii codes into decimals
             char_as_int = atoi(string_to_convert);
             //printf("%s as an int is %i\n", string_to_convert, char_as_int);
             long binary = convert_to_binary(char_as_int);
             //printf("The binary equivalent is %ld\n", binary);

             // find the length of the binary number
             padding_required = 8 - intlen(binary);
             if (padding_required == 0) {
               //printf("The number is two bytes long. No padding required\n");
               char eight_bit_string[9];
               sprintf(eight_bit_string, "%ld", binary);
               //printf("Adding %s to super_string\n", eight_bit_string);
               if (super_string_index < 59) {
                   strcat(super_string, eight_bit_string);
                   strcat(super_string, " ");
                   //printf("Adding %c to superstring\n", padded_binary[i]);
                   //printf("%c was added to the superstring\n", super_string[super_string_index]);
                 super_string_index += strlen(eight_bit_string) - 2;
               } else {
                 //printf("Super string full. Discarding\n");
               }

               //printf("super_string: %s\n", super_string);
               //printf("\n");

             } else if (padding_required > 0) {
               /* if the binary number has too few bits, add leading zeroes equal to
               * (8 - len of number) or (3 - len of_number)
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
               for (int j = padding_required; j < 9; j++) {
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
      char final_string[6] = {'\0','\0','\0','\0','\0','\0'};
      memcpy(final_string, str, 6);
      //printf("Converting: %s to binary\n", final_string);
      //printf("The final string is %i characters long\n", strlen(final_string));
      int char_as_int;
      int padding_required;
      char padded_binary[8];
      // convert ascii codes into decimals
      char_as_int = atoi(final_string);
      //printf("%s as an int is %i\n", string_to_convert, char_as_int);
      long binary = convert_to_binary(char_as_int);
      //printf("The binary equivalent is %ld\n", binary);

      // find the length of the binary number
      padding_required = 8 - intlen(binary);
      if (padding_required == 0) {
        //printf("The number is two bytes long. No padding required\n");
        char eight_bit_string[9];
        sprintf(eight_bit_string, "%ld", binary);

        //printf("Adding %s to super_string\n", eight_bit_string);
        if (super_string_index < 59) {
            strncpy(super_string, eight_bit_string, 9);
            //printf("Adding %c to superstring\n", padded_binary[i]);
            //printf("%c was added to the superstring\n", super_string[super_string_index]);
            super_string_index += strlen(eight_bit_string) - 2;
          }
        else {
          //printf("Super string full. Discarding\n");
        }

      } else if (padding_required > 0) {
        /* if the binary number has too few bits, add leading zeroes equal to
        * (8 - len of number)
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
        for (int j = padding_required; j < 9; j++) {
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
      printf("super_string: %s\n", super_string);
      printf("\n");

      //clear superstring and reset the index for the next entry
      for (int i = 0; i < 59; i++) {
        super_string[i] = '\0';
      }
      super_string_index = 0;
   }

   fclose(fp);

   return(0);
}
