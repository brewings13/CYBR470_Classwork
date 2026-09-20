#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#define BUFFER_SIZE 64

int main() 
{
    char string_buffer[BUFFER_SIZE];
    FILE *readable_file; 
    readable_file = stdin; 
    char *new_line; 
    int line = 1; 
    while ((new_line = fgets(string_buffer, BUFFER_SIZE, readable_file)) != NULL)
    {
        char *first_colon = strchr(new_line, ':');
        if (first_colon != NULL)
        {
            printf("Line %d: key=%ld ", line, (first_colon - new_line));
            printf("value=%s", first_colon + 1); 
            line++; 
        }else if (first_colon == NULL)
        {
            printf("Line %d: malformed, no colon\n", line);
            line++; 
        } else if ((first_colon - new_line) == 0)
        {
            printf("Line %d: malformed, no key\n", line);
        }
    }
    //printf("%s", new_line); 
    //char formatted_buffer[BUFFER_SIZE]; 
    //strncpy(new_line, formatted_buffer, index_of_first_colon); 
    //char *first_colon = strchr(new_line, ':'); 
    //printf("%d\n", *first_colon);
    /*int index_of_first_colon = 0; 
    for (unsigned int i = 0; i < strlen(new_line); i++)
    {
        if (new_line[i] == 58)
        {
            index_of_first_colon = i; 
            break; 
        }
    }*/
    //strncpy(new_line, formatted_buffer, index_of_first_colon); 
    //printf("%s", formatted_buffer);
    //printf("%d", index_of_first_colon);
    return 0; 
}