#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Type Amount Number1 Number2 … NumberN --> Type Amount Number1, Number2, … , NumberN
//0000 0010 1000111 11111111 --> 0001 002 71,255

void print_char_array(char array[], int length) {
  /* Print non-null values */
  for (int i = 0; i <= length; i++) {
    if (array[i] != '\0') {
      printf("%c", array[i]);
    }
  }
}

void print_int_array(int array[], int length) {
  for (int i = 0; i < length; i++) {
    printf("%u ", array[i]);
  }
  printf("\n");
}

int convert_to_binary(int decimal) {

  return 0;
}

/* function to generate and return random numbers */
int get_number_of_strings(char array[]) {
  int length = 3;
  int num = 0;
  // reserve space for the 3 contiguous integers
  int number_of_numbers[length];
  char number_of_numbers_char[length];

  //convert chars into ints
  for (int i = 0; i < length; i++) {
    int x = -1;
    if (isdigit(array[i])) {
      x = array[i] - 48;
    }
    number_of_numbers[i] = x;
    number_of_numbers_char[i] = array[i];
   }

   int len_copy = length;
   for (int i = 0; i < length; i++) {
     num = num + pow(number_of_numbers[i], len_copy);
     len_copy = len_copy - 1;
   }
   printf("The number of entries in this line is: %i\n", num);
   printf("The string that will be returned is: %s\n", number_of_numbers_char);

   return num;
}


int int_array_to_int (int array[], int length) {
  int num = 0;
  int len_copy = length;
  for (int i = 0; i < length; i++) {
    num = num + pow(array[i], len_copy);
    len_copy = len_copy - 1;
  }
  return num;
}

int main () {
   FILE *fp;
   char str[60];

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

      //int x = get_number_of_strings(str);

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
        printf("Space index at: %i\n", index);
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
        for (int i=0; i<60; i++) {
          str[i] = '\0';
        }
        strcpy(str, remaining_string);

        printf("Converting: %s to binary\n", string_to_convert);
        printf("Remaining string is:%s\n", str);
        ptr = strstr(str, " ");
      }
      // convert the last number with no space after it
      char final_string[6];
      memcpy(final_string, str, 6);
      printf("Converting: %s to binary\n", final_string);

   }
   fclose(fp);

   return(0);
}
