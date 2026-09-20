/*Exercise 4_1 : Safe String Operations
  CYBR470 Fall 2026
  Student: Christopher Stahl
  
  This program demonstrates some common string 
  functions and how they operate.*/


#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 


void truncation_detection(int string_length, int buffer_length)     //function to determine if string was truncated
{
    if (string_length >= buffer_length)
        printf("Truncated: yes\n");
    else
    {
        printf("Truncated: no\n"); 
    }
}


int main() 
{
    char first_array[16];       //declares a char array of 16 bytes to store a string
    int first_array_buffer = sizeof(first_array);   //sets a variable to store the buffer size of the first array 
    int number_chars_first_array = snprintf(first_array, first_array_buffer, "Read more books");   /*reads the string "Read more books" into first_array,
                                                                                                    sets variable to store number of chars given to 
                                                                                                    snprintf() to write*/ 

    printf("=== snprintf ===\n");       //display header for output 
    printf("Buffer size: %d\n", first_array_buffer);     //display the number of bytes (buffer) of the first array 
    printf("Result: ");     //display the 'Result' designator for the second line of text 
    puts(first_array);     //display the string copied into first_array
    printf("Return value: %d\n", number_chars_first_array);       //display the number of chars the snprintf() function was given to copy  
    truncation_detection(number_chars_first_array, first_array_buffer);     //display whether the string was truncated 

    char second_array[7];   // declares a char array of 7 bytes to store a string
    int second_array_buffer = sizeof(second_array);     //sets a variable to store the buffer size of the second array 
    int number_chars_second_array = snprintf(second_array, second_array_buffer, "Read more books");  /*reads the string "Read more books" into second_array,
                                                                                                      sets variable to store number of chars given to 
                                                                                                      snprintf() to write*/ 

    printf("Buffer size: %d\n", second_array_buffer);   //display the number of bytes (buffer) of the second array
    printf("Result: ");     //display the 'Result' designator for the second line of text
    puts(second_array);     //display the string copied into second_array 
    printf("Return value: %d\n", number_chars_second_array);    //display the number of chars the snprintf() function was given to copy 
    truncation_detection(number_chars_second_array, second_array_buffer);   //display whether the string was truncated 
    

    char third_array[7];    //declares a char array of 7 bytes to store a string
    strncpy(third_array, "Read more books", sizeof(third_array));   //copies the given string into the array 
    printf("=== strncpy ===\n");    //displays the haeader for the second portion of output
    printf("Bytes: ");      //displays the 'bytes' designator for the hex values of the string
    for (unsigned int i = 0; i < sizeof(third_array); i++)      //displays each char in the string as a hex value
    {
        printf("%02x ", third_array[i]); 
    }
    
    if (third_array[sizeof(third_array) - 1] != 0)      //displays whether the array terminated 
    {
        printf("\nTerminated: no\n");
    } else 
    {
        printf("\nTerminated: yes\n"); 
    }
    third_array[6] = '\0';      //assigns the 'null' operator to the 7th value of third_array 
    printf("Bytes: ");      //displays the 'bytes' designator 
    for (unsigned int i = 0; i < sizeof(third_array); i++)      //displays each char in the string as a hex value
    {
        printf("%02x ", third_array[i]); 
    }
    
    if (third_array[sizeof(third_array) - 1] != 0)      //displays whether the array terminated 
    {
        printf("\nTerminated: no\n");
    } else 
    {
        printf("\nTerminated: yes\n"); 
    }
    printf("Value: %s\n", third_array);     //displays the string as copied 
   
    return 0; 
}