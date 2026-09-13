#include <stdio.h> 
#include <ctype.h>
#define SPACE 32 
#define TAB 9 
#define NEWLINE 10 
#define CAR_RETURN 13 
#define FORM_FEED 12 
#define VERTICAL_TAB 11

void countLettersAndTokens(FILE *fileToParse)
{
    int c;
    float tokenCount = 0;
    float letterCount = 0; 
    float averageLettersPerToken = 0;
    int inToken = 0; 

    while ((c = fgetc(fileToParse)) != EOF)
    {
        if ((isalpha(c) != 0))
        {
            letterCount++;
        }
        if (c == SPACE || c == TAB || c == NEWLINE || c == CAR_RETURN || c == FORM_FEED || c == VERTICAL_TAB)
        {
            if(inToken)
            {
                tokenCount++;
                inToken = 0;
            } 
        } else
        {
            inToken = 1; 
        }
    }
    if (inToken)
    {
        tokenCount++; 
    }
    if (tokenCount != 0)
    {
        averageLettersPerToken = letterCount / tokenCount; 
        printf("Total tokens: %.0f\nTotal letters: %.0f\nAverage letters per token: %.1f\n", tokenCount, letterCount, averageLettersPerToken);
    } else
    {
        printf("Total tokens: %.0f\nTotal letters: %.0f\nAverage letters per token: 0.0", tokenCount, letterCount);
    }
}



int main(int argc, char *argv[]) 
{
    FILE *filePointer; 

    if (argc == 2)
    {
        filePointer = fopen(argv[1], "r");
        if (filePointer == NULL)
        {
            perror("Error: could not open file.");
            return 1; 
        }
        countLettersAndTokens(filePointer); 
        fclose(filePointer);
    } else if (argc == 1)
    {
        filePointer = stdin;
        countLettersAndTokens(filePointer);  
    }
    return 0; 
}