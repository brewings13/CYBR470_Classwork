/* CYBR 470 - Exercise9_2 - Insert a rule after another rule
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
    char target[16];
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

    /* Each line after "---" looks like: after 10.0.0.5 allow 10.0.0.9 */
    while (status == 0 && fgets(line, sizeof line, stdin) != NULL)
    {
        if (sscanf(line, "after %15s %7s %15s", target, action, addr) != 3)
        {
            continue;
        }
        line[strcspn(line, "\n")] = '\0';
        printf("> %s\n", line);
        if (strcmp(target, addr) != 0)
        {
            printf("<%s>: no such rule", target);
        }
        struct Rule *pCurrent = pHead;
        while (pCurrent != NULL && strcmp(target, addr) != 0)
        {
            pCurrent = pCurrent->pNext;
        }
        struct Rule *pNewRule = malloc(sizeof(*pNewRule));
        if (pNewRule == NULL)
        {
            fprintf(stderr, "out of memory");
            status = 1; 
            break;
        }
        snprintf(pNewRule->action, sizeof(pNewRule->action), "%s", action);
        snprintf(pNewRule->addr, sizeof(pNewRule->addr), "%s", addr);
        pCurrent->pNext = pNewRule; 
        
        /* TODO 1: Find the first rule whose addr matches target (use strcmp).
         *   - If no rule matches, print "<target>: no such rule". The starter
         *     code prints the chain after your code either way.
         *   - Otherwise malloc a new rule. If malloc returns NULL, print
         *     "out of memory" to stderr, set status to 1, and break.
         *   - Copy action and addr into the new rule with snprintf.
         *   - Link the new rule in right after the rule you found. */

        print_chain(pHead);
    }

    /* TODO 2: Free every rule in the chain. */
    free(pHead);
    return status;
}
