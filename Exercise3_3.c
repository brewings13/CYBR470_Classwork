#include <stdio.h> 
#include <ctype.h>
#define SPACE 32    //ASCII value of the space character
#define TAB 9       //ASCII value for the tab character
#define NEWLINE 10  //ASCII value of the newline character
#define CAR_RETURN 13   //ASCII value of the carriage return character
#define FORM_FEED 12    //ASCII value of the form feed character
#define VERTICAL_TAB 11     //ASCII value of the vertical tab character

// this function reads a file character by character, counts each token and letter, calculates the average number of letters, and displays the information
void countLettersAndTokens(FILE *fileToParse)       
{
    int c;      //declares a variable to store each character in the file 
    float tokenCount = 0;   //declares a variable to store the token count
    float letterCount = 0;  //declares a variable to store the letter count
    float averageLettersPerToken = 0;   //declares a variable to store the calculated average of letters 
    int inToken = 0;    //variable to determine whether a token is currently being traversed (1 represents being in a token, 0 represents being out)

    while ((c = fgetc(fileToParse)) != EOF)     //this loop parses the file while an EOF char is not encountered 
    {
        if ((isalpha(c) != 0))  //determines if the current character is a letter 
        {
            letterCount++;  //increments the letter variable 
        }
        if (c == SPACE || c == TAB || c == NEWLINE || c == CAR_RETURN || c == FORM_FEED || c == VERTICAL_TAB)   //determines if the char is a token separator)
        {
            if(inToken)     //this branch runs if inToken = 1
            {
                tokenCount++;   //increments tokenCount
                inToken = 0;    //sets inToken = 0 (so this branch skips if there are multiple spaces between tokens)
            } 
        } else
        {
            inToken = 1;    // sets inToken = 1 so tokenCount is incremented next time a token separator is encountered
        }
    }
    if (inToken)    //counts last token if no token separator character at the end of the file
    {
        tokenCount++;   //increments tokenCount
    }
    if (tokenCount != 0)    //executes if there are tokens present in the file
    {
        averageLettersPerToken = letterCount / tokenCount; 
        printf("Total tokens: %.0f\nTotal letters: %.0f\nAverage letters per token: %.1f\n", tokenCount, letterCount, averageLettersPerToken);
    } else      //executes if no tokens are present in file (avoids dividing by zero)
    {
        printf("Total tokens: %.0f\nTotal letters: %.0f\nAverage letters per token: 0.0", tokenCount, letterCount);
    }
}



int main(int argc, char *argv[])    //main has argc and argv[] parameters to read a file piped in or one given as an argument
{
    FILE *filePointer;  //create a file pointer variable to use with countLettersAndTokens()

    if (argc == 2)  //this branch runs if a file is given to read as argv[1] in the command line (no < symbol)
    {
        filePointer = fopen(argv[1], "r");      //assigns the open file to the filePointer variable
        if (filePointer == NULL)    //makes sure fopen() was successful
        {
            perror("Error: could not open file.");
            return 1; 
        }
        countLettersAndTokens(filePointer);     //parses given file and displays counts
        fclose(filePointer);    //closes the file passed into the filePointer pointer variable 
    } else if (argc == 1)       //this branch runs if a file is piped in for the program to use as (stdin) (< symbol) 
    {
        filePointer = stdin;    //sets the filePointer variable equal to stdin
        countLettersAndTokens(filePointer);     //parses given file and displays counts 
    }
    return 0; 
}