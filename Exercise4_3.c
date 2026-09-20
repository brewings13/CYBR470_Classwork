/*Exercise 4_3 : Reading Input Safely
  CYBR470 Fall 2026
  Student: Christopher Stahl
  
  This program demonstrates a method for only 
  reading strings into a buffer up to its allocation.
  If the string length is less than the alloc, the string
  is read into the buffer. If it's longer, it's rejected. */


#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 32

void determine_string_acceptability(char given_buffer[], FILE *given_file)      //function to determine acceptability of each line of the given file
{
    int line = 1;   //declares a variable to track which line is being processed
    int accepted = 0;   //declares a variable to track the number of lines accepted 
    int rejected = 0;   //declares a varaible to track the number of lines rejected
    char *new_line;     //creates a pointer variable to store each line for processing using fgets()
    while ((new_line = fgets(given_buffer, BUFFER_SIZE, given_file)) != NULL)   //executes while there is data in the given file
    {
        char *newline_char = strchr(new_line, '\n');    //declares a pointer variable to store result of strchr() (is there a \n in the line)
        new_line[strcspn(new_line, "\n")] = '\0';   //strips the \n from the line if it exists
        int line_length = strlen(new_line);     //declares a variable to store the length of the line without the \n character 
        if (newline_char)   //executes if the line contains a \n character
        {
            printf("Line %d: accepted, length %d: %s\n", line, line_length, new_line);  //display required information for accepted line 
            accepted++;     //increment accepted variable to track line
        }else
        {
            printf("Line %d: rejected, longer than 31 characters\n", line);     //display required information for rejected line
            while (fgetc(given_file) != '\n')       //parse through remainder of rejected line so the next read starts at the next line 
            {
                continue; 
            }
            rejected++;     //increment rejected variable to track line 
        }
        line++; 
    }
    printf("Lines accepted: %d\n", accepted);   //display total number of lines accepted
    printf("Lines rejected: %d\n", rejected);   //display total number of lines rejected 
}   

int main() 
{
    char string_buffer[BUFFER_SIZE];    //declare a char array to store line being processed
    FILE *readable_file = stdin;    //declares a FILE pointer variable to store the file that is piped in 
    determine_string_acceptability(string_buffer, readable_file);   //call to execute file to determine line-by-line acceptability of file
    return 0; 
}