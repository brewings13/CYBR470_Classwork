#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

char *quote_remover(char *line_to_strip)
{
    if (strlen(line_to_strip) < 2)
    {
        return line_to_strip; 
    }
    if (line_to_strip[0] == '\"')
    {
        line_to_strip++; 
    }
    line_to_strip[strcspn(line_to_strip, "\"")] = '\0'; 
    return line_to_strip; 
}


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
        char *next_item = line; 
        strncpy(items[count].itemName, quote_remover(strsep(&next_item, ",")), MAX_ITEM_NAME_STRING); 
        strncpy(items[count].itemDescription, quote_remover(strsep(&next_item, ",")), MAX_ITEM_DESCRIPTION_STRING); 
        strncpy(items[count].targetAsset, quote_remover(strsep(&next_item, ",")), MAX_ASSET_TYPE_STRING); 
        strncpy(items[count].actionText, quote_remover(strsep(&next_item, ",")), MAX_ACTION_TEXT_STRING); 
        items[count].itemUse = atoi(strsep(&next_item, ","));
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
