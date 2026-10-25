/* CYBR 470 - Exercise9_3 - Remove a rule
 *
 * Student:
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
    int n = 0;

    if (pHead == NULL)
    {
        printf("(empty)\n");
    }
    for (const struct Rule *p = pHead; p != NULL; p = p->pNext)
    {
        n++;
        printf("%d: %-5s %s\n", n, p->action, p->addr);
    }
    printf("end of chain\n");
}

int main(void)
{
    struct Rule *pHead = NULL;
    struct Rule *pTail = NULL;
    char line[128];
    char action[8];
    char addr[16];
    int status = 0;

    /* Build the starting chain from the lines before "---".
     * Each rule is added at the end, so the chain keeps the input order.
     * pTail always points to the last rule. */
    while (fgets(line, sizeof line, stdin) != NULL)
    {
        if (strncmp(line, "---", 3) == 0)
        {
            break;
        }
        if (sscanf(line, "%7s %15s", action, addr) != 2)
        {
            continue;
        }

        struct Rule *pRule = malloc(sizeof *pRule);
        if (pRule == NULL)
        {
            fprintf(stderr, "out of memory\n");
            status = 1;
            break;
        }
        snprintf(pRule->action, sizeof pRule->action, "%s", action);
        snprintf(pRule->addr, sizeof pRule->addr, "%s", addr);
        pRule->pNext = NULL;
        if (pHead == NULL)
        {
            pHead = pRule;
        }
        else
        {
            pTail->pNext = pRule;
        }
        pTail = pRule;
    }

    if (status == 0)
    {
        print_chain(pHead);
    }

    /* Each line after "---" looks like: remove 10.0.0.5 */
    while (status == 0 && fgets(line, sizeof line, stdin) != NULL)
    {
        if (sscanf(line, "remove %15s", addr) != 1)
        {
            continue;
        }
        line[strcspn(line, "\n")] = '\0';
        printf("> %s\n", line);

        //added code

        struct Rule *pPrev = pHead;  //creates a Rule pointer to traverse list for target value
        if (strcmp(addr, pHead->addr) == 0)
        {

            struct Rule *pRemove = pHead; 
            pHead = pHead->pNext; 
            free(pRemove);
            print_chain(pHead); 
            continue; 
        }
        printf("%p outside loop\n", pPrev); 
        while (pPrev != NULL && strcmp(addr, pPrev->pNext->addr) != 0) //excutes until the target value is found 
        {
            printf("%s\n", "this is before the next step");
            pPrev = pPrev->pNext;
            printf("%p inside traverse loop\n", pPrev);
        }
        if (pPrev == NULL)   //executes if target value is not found 
        {
            printf("%s: no such rule\n", addr);
        }else
        {
            struct Rule *pRemove = pPrev->pNext; 
            pPrev->pNext = pRemove->pNext; 
            free(pRemove);
        }
        
        /* TODO 1: Remove the first rule whose addr field matches the addr
         *   read from the line (use strcmp).
         *   - If no rule matches, print "<addr>: no such rule". The chain
         *     is printed either way.
         *   - Removing the first rule changes pHead.
         *   - Removing any other rule changes the pNext of the rule
         *     before it. Keep a pointer to the previous rule as you walk.
         *   - Free the rule you removed. */

        print_chain(pHead);
    }
    struct Rule *pCurrentForFree = pHead;   //declares a Rule pointer to traverse the list and free each node from memory
    while (pCurrentForFree != NULL)        //executes while pCurrent has data
    {
        struct Rule *pNextNode = pCurrentForFree->pNext;   //declares a pointer to the next node in the list
        free(pCurrentForFree);     //frees the memory for the current node
        pCurrentForFree = pNextNode;   //sets the current pointer to the next node to continue freeing memory
    }
    pHead = NULL;     //sets the pHead pointer to NULL, allowing list to be reused
    pTail = NULL;     //sets the pTail pointer to NULL, allowing it to be reused
    /* TODO 2: Free every rule left in the chain. */

    return status;
}
