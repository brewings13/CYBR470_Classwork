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
    int accepted_line = 0;
    int malformed_line = 0;
    while ((new_line = fgets(string_buffer, BUFFER_SIZE, readable_file)) != NULL)
    {
        char *first_colon = strchr(new_line, ':');
        int key_length = first_colon - new_line; 
        if (first_colon != NULL && new_line != first_colon)
        {
            printf("Line %d: key=%.*s ", line, key_length, new_line);
            printf("value=%s", first_colon + 1); 
            line++; 
            accepted_line++; 
        }else if (first_colon == NULL)
        {
            printf("Line %d: malformed, no colon\n", line);
            line++; 
            malformed_line++; 
        } else if (new_line == first_colon)
        {
            printf("Line %d: malformed, no key\n", line);
            line++; 
            malformed_line++; 
        } else
        {
            printf("Line %d: malformed, no value\n", line);
            line++; 
            malformed_line++; 
        }
        printf("%p\n", first_colon + 1);
        //printf("%p\n", new_line); 
        //printf("%d\n", key_length);
        //printf("%p\n", (new_line + key_length)); 
    }
    printf("Pairs parsed: %d\n", accepted_line);
    printf("Malformed lines: %d\n", malformed_line);
    
    return 0; 
}