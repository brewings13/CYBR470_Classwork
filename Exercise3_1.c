#include <stdio.h> 
#include <stdlib.h> 

FILE *filePointer;      //creates a pointer to store the address of the .txt file 

char buffer[256];       //creates a buffer to store each line in 

int main() {
    filePointer = fopen("Exercise3_1.txt", "r");    // used to open the .txt file

    if (filePointer == NULL)        // check to make sure fopen() was successful 
    {
        printf("Error. Could not open file.\n"); 
        return 1; 
    }

    return 0; 
} 