/* CYBR 470 - Exercise9_1 - Build the rule chain
 *
 * Student: Christopher Stahl 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Rule
{
    char         action[8];    /* "allow" or "deny" */
    char         addr[16];     /* IPv4 address, such as 10.0.0.5 */
    struct Rule *pNext;
};

/* Prints every rule in order, numbered from 1. Do not change this function. */
static void print_chain(const struct Rule *pHead)
{
    int n = 0;      //declares an int variable to track the line number 

    if (pHead == NULL)      //executes if the pHead pointer is pointing to NULL
    {
        printf("(empty)\n");
    }
    for (const struct Rule *p = pHead; p != NULL; p = p->pNext) //iterates through each line 
    {
        n++;    //increments line number variable
        printf("%d: %-5s %s\n", n, p->action, p->addr);     //displays information for current line 
    }
    printf("end of chain\n");
}

int main(void)
{
    struct Rule *pHead = NULL;  //declares a pointer variable for the head pointer
    char line[128];     //creates a char array to read each line into
    char action[8];     //creates a char array to read in the line action
    char addr[16];      //creates a char array to read in the line address 
    int status = 0;     //creates an int variable to store the status of main

    while (fgets(line, sizeof line, stdin) != NULL)     //executes while the given file is not empty
    {
        if (sscanf(line, "%7s %15s", action, addr) != 2)    //executes if line is blank
        {
            continue;       /* skip blank lines */
        }
        struct Rule *pNewRule = malloc(sizeof(*pNewRule));  //declares a Rule pointer and allocates memory
        if (pNewRule == NULL)   //executes if Rule pointer is NULL
        {
            fprintf(stderr, "out of memory\n");
            status = 1; 
            break;
        }
        snprintf(pNewRule->action, sizeof(pNewRule->action), "%s", action); //prints action string into action buffer
        snprintf(pNewRule->addr, sizeof(pNewRule->addr), "%s", addr);   //prints addr string into addr buffer
        pNewRule->pNext = pHead;    //sets pNewRule's 'next' pointer to the current head of the list
        pHead = pNewRule;   //sets the head pointer to point at pNewRule, which is the new head of the list
    }

    if (status == 0)    //executes if status is 0 (loop was successful)
    {
        print_chain(pHead);
    }

    free(pHead);    //frees the memory allocated for the head pointer which frees the entire list 
    return status;  //return status variable 
}
