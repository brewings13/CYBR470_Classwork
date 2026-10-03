#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"


/*
 *  Loads items from filename into items[].  Each line of the file is:
 *      "name","description","targetAsset","actionText",use
 *  Returns the number of items loaded, or -1 if the file cannot be opened
 *  or no valid items are found.  Malformed lines are skipped.
 */

int ItemLoadFromFile(Item items[], int maxItems, char *filename)
{ 

    FILE *fp = fopen(filename, "r"); 
    if (fp == NULL)
    {
        perror("fopen");
        return -1; 
    }
    char line[256]; 
    int count = 0; 
    while (fgets(line, sizeof(line), fp) != NULL && count <= maxItems)
    {
        strncpy(items[count].itemName, strtok(line + 1, "\","), MAX_ITEM_NAME_STRING); 
        printf("%s\n", items[count].itemName);
        strncpy(items[count].itemDescription, strtok(NULL, "\","), MAX_ITEM_DESCRIPTION_STRING); 
        printf("%s\n", items[count].itemDescription);
        strncpy(items[count].targetAsset, strsep(line, "\","), MAX_ASSET_TYPE_STRING); 
        printf("%s\n", items[count].targetAsset);
        strncpy(items[count].actionText, strsep(line, "\","), MAX_ACTION_TEXT_STRING); 
        printf("%s\n", items[count].actionText);
        char *token = strtok(NULL, "\",");
        if (token == NULL)
        {
            perror("bad read"); 
        } 
        items[count].itemUse = atoi(token); 
        printf("%d\n", items[count].itemUse); 
        count++; 
    }
    fclose(fp); 

    return count;
}

//look for the item with the specified name itemName.  Returns NULL if not found.
Item *ItemFindByName(Item items[], int maxItems, char *itemName)
{
    (void)items; (void)maxItems; (void)itemName;
    return NULL;
}

// display the item.  displayAll = 0 shows the name, otherwise name and description.
void ItemShow(void *pItem, int displayAll)
{
    (void)pItem; (void)displayAll;
}
