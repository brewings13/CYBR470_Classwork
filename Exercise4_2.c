/*Exercise 4_2 : strlen Versus sizeof
  CYBR470 Fall 2026
  Student: Christopher Stahl
  
  This program demonstrates the differences
  between the strlen and sizeof functions and 
  how they differentiate between an array and 
  a pointer variable*/


#include <stdio.h>
#include <string.h>

void get_size_of_array(char given_array[])      //function to demonstrate how strlen and sizeof operate on an array passed into a function
{
    int array_length = strlen(given_array);     //declares a variable to store the length of the given array 
    long unsigned int array_size = sizeof(given_array);     //declares a variable to store the size of the given array 
    printf("Array passed to a function\n");     //displays header for third section of results
    printf("  Contents: %s\n", given_array);    //displays the contents of the given array
    printf("  strlen: %d\n", array_length);     //displays the result of strlen() for the given array 
    printf("  sizeof: %zu\n", array_size);      //displays the result of sizeof() for the given array 

}

int main() 
{
    char location[32] = "Forest";   //declares a char array of 32 bytes that stores the string "Forest"
    int string_length = strlen(location);   //declares a variable to store the length of the string 
    long unsigned int buffer_size = sizeof(location);   //declares a variable to store the size of the array 
    printf("Array in scope\n");     //displays header for the first section of results 
    printf("  Contents: %s\n", location);       //displays the contents of the given array   
    printf("  strlen: %d\n", string_length);    //displays the result of strlen() for the given array
    printf("  sizeof: %zu\n", buffer_size);     //displays the result of sizeof() for the given array

    const char *p = "Forest";       //declares a char pointer variable to store the string "Forest"
    int pointer_length = strlen(p);     //declares a variable to store the result of strlen() using the pointer as an argument
    long unsigned int pointer_size = sizeof(p);     //declares a variable to store the result of sizeof() using the pointer as an argument
    printf("Pointer to literal\n");     //displays header for the second section of results 
    printf("  Contents: %s\n", p);      //displays the contents of the pointer
    printf("  strlen: %d\n", pointer_length);   //displays the result of strlen() for the pointer
    printf("  sizeof: %zu\n", pointer_size);    //displays the result of sizeof() for the pointer

    get_size_of_array(location);    //call to get_size_of_array function with the 'location' array as an arugment 
    return 0; 
}