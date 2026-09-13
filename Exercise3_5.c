#include <stdio.h> 
#include <ctype.h>

int getAlphabetPosition(char c)
{
    char lowercaseChar = tolower(c); 
    int position = lowercaseChar - 96; 
    if (position < 1 || position > 26)
    {
        position = -1; 
    }
    printf("%d", position);
    return 0; 
}



int main(int argc, char *argv[])
{
    FILE *filePointer; 

    if (argc == 2)
    {
        filePointer = fopen(argv[1], "r");
        
    }
    //getAlphabetPosition('Z'); 

    return 0;
}