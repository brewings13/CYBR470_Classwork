#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#define BUFFER_SIZE 64

int main() 
{
    char string_buffer[BUFFER_SIZE];    //declares a char array buffer to store each string 
    FILE *readable_file;    //declares a file pointer to use with fgets
    readable_file = stdin;      //reads a file from stdin
    char *new_line;     //declares a char pointer to store the address of each line as it's being processed 
    int line = 1;       //declares an int variable to store the number of the line being processed
    int accepted_line = 0;      //declares an int variable to store how many lines were acceptable 
    int malformed_line = 0;     //declares an int variable to store how many lines were malformed 

    /*This while-loop executes while the file has data. The loop reads one line at a time and then processes
    the line through various if-statements to determine if the line is acceptable or not. If the line 
    is accceptable, the key and value are displayed If the line is not acceptable, the reasoning is displayed.*/

    while ((new_line = fgets(string_buffer, BUFFER_SIZE, readable_file)) != NULL)       
    {
        string_buffer[strcspn(string_buffer,"\n")] = '\0';      //strips the newline character from each line
        char *first_colon = strchr(new_line, ':');      //declares a char pointer to store the colon if the line contains one 
        int key_length = first_colon - new_line;        //declares an int variable to store the length of the key (pointer arithmetic)
        char *next_addr_after_colon = first_colon + 1;      //declares a char pointer to store the address of the next char past the colon

        /*Test to make sure the line has a colon, the colon isn't the first char of the line, 
        and there is data after the colon rather than a null char or other whitespace*/
        if (first_colon != NULL && new_line != first_colon && *next_addr_after_colon != '\0' && *next_addr_after_colon != ' ')
        {
            printf("Line %d: key=%.*s ", line, key_length, new_line);
            printf("value=%s\n", next_addr_after_colon); 
            line++; 
            accepted_line++; 
        }else if (first_colon == NULL)      //this branch executes if the line has no colon 
        {
            printf("Line %d: malformed, no colon\n", line);
            line++; 
            malformed_line++; 
        } else if (new_line == first_colon)     //this branch executes if the colon is the first char on the line (no key)
        {
            printf("Line %d: malformed, no key\n", line);
            line++; 
            malformed_line++; 
        } else      //this branch executes if all other branches fail (line has no value in this case)
        {
            printf("Line %d: malformed, no value\n", line);
            line++; 
            malformed_line++; 
        }
    }
    printf("Pairs parsed: %d\n", accepted_line);    //display the total number of acceptable lines
    printf("Malformed lines: %d\n", malformed_line);        //display the total number of malformed lines 
    
    return 0; 
}