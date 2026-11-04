#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

#define STACK_SIZE 100
#define MAX_WORD_LENGTH 30

typedef struct {
    int count; 
    char words[STACK_SIZE][MAX_WORD_LENGTH];
} WordStack; 

bool StackPush(WordStack *pStack, int value)
{
    // FILE *givenFile = NULL; 
    // char *currentWord = NULL; 
    if (pStack == NULL || pStack->count >= STACK_SIZE)
    {
        return false;
    }
    // pStack->words[pStack->count] = value; 
    pStack->count++;
    return true; 
}

int main ()
{
    WordStack *stack = NULL; 
    StackPush(&stack, 10); 
    StackPush(&stack, 20);
    StackPush(&stack, 30); 
    printf("%s", stack->words);


    return 0; 
}