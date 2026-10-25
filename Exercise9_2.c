/* CYBR 470 - Exercise9_2 - Insert a rule after another rule
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
    struct Rule *pHead = NULL;      //declare a Rule pointer to point to the head node
    struct Rule *pTail = NULL;      //declare a Rule pointer to point to the tail node
    char line[128];     //create a char array to store the line being read in 
    char target[16];    //create a char array to store the target value of the line 
    char action[8];     //create a char array to store the action of the current line 
    char addr[16];      //create a char array to store the addr of the current line 
    int status = 0;     //create an int variable to store the program status

    /* Build the starting chain from the lines before "---".
     * Each rule is added at the end, so the chain keeps the input order.
     * pTail always points to the last rule. */
    while (fgets(line, sizeof line, stdin) != NULL)
    {
        if (strncmp(line, "---", 3) == 0)       //executes when line reaches the divider 
        {
            break;
        }
        if (sscanf(line, "%7s %15s", action, addr) != 2)    //skips blank lines 
        {
            continue;
        }

        struct Rule *pRule = malloc(sizeof *pRule);     //declares a Rule pointer and allocates memory to write data from current line 
        if (pRule == NULL)      //executes if Rule pointer is NULL
        {
            fprintf(stderr, "out of memory\n");
            status = 1;
            break;
        }
        snprintf(pRule->action, sizeof pRule->action, "%s", action);       //prints action string into action buffer
        snprintf(pRule->addr, sizeof pRule->addr, "%s", addr);              //prints addr string into addr buffer
        pRule->pNext = NULL;    //sets next pointer to NULL since each node is added at end of list
        if (pHead == NULL)      //executes if pRule is first node being added to the list
        {
            pHead = pRule;
        }
        else
        {
            pTail->pNext = pRule;       //adds pRule to end of list 
        }
        pTail = pRule;      //sets the tail pointer to the newly added rule 
    }
    
    if (status == 0)
    {
        print_chain(pHead);
    }

    /* Each line after "---" looks like: after 10.0.0.5 allow 10.0.0.9 */
    while (status == 0 && fgets(line, sizeof line, stdin) != NULL)
    {
        if (sscanf(line, "after %15s %7s %15s", target, action, addr) != 3)     //skips blank lines
        {
            continue;
        }
        line[strcspn(line, "\n")] = '\0';   //strips newline character from current line 
        printf("> %s\n", line);

        //added code

        struct Rule *pCurrentForWrite = pHead;  //creates a Rule pointer to traverse list for target value
        while (pCurrentForWrite != NULL && strcmp(target, pCurrentForWrite->addr) != 0) //executes until the target value is found 
        {
            pCurrentForWrite = pCurrentForWrite->pNext;
        }

        if (pCurrentForWrite == NULL)   //executes if target value is not found 
        {
            printf("%s: no such rule\n", target);
        } else
        {
            struct Rule *pNewRule = malloc(sizeof(*pNewRule));      //declares Rule pointer for new rule and allocates memory to write new rule data
            if (pNewRule == NULL)   //executes if no memory is available
            {
                fprintf(stderr, "out of memory");
                status = 1; 
                break;
            }
            snprintf(pNewRule->action, sizeof(pNewRule->action), "%s", action);     //prints action string into action buffer
            snprintf(pNewRule->addr, sizeof(pNewRule->addr), "%s", addr);       //prints addr string into addr buffer
            pNewRule->pNext = pCurrentForWrite->pNext;      //sets the next pointer for the new rule equal to the next pointer for the current rule 
            pCurrentForWrite->pNext = pNewRule;     //sets the current rule next pointer to the new rule (places new rule into proper spot in list behind current node)
        }
       
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
    return status;      //return the status variable
}
