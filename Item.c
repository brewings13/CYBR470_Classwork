#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

static char *quote_remover(char *line_to_strip)     //this function strips the quotes from each item of the line 
{   
    if (line_to_strip == NULL)      //executes if the line pointer is NULL
    {
        return NULL; 
    }
    if (strlen(line_to_strip) < 2)      //executes if the line length is less than 2 (line is int, no quotes)
    {
        return line_to_strip; 
    }
    if (line_to_strip[0] == '\"')       //executes if the first character of the line is a \" (line has quotes)
    {
        line_to_strip++;        //advances pointer to first char past quotes
    }
    line_to_strip[strcspn(line_to_strip, "\"")] = '\0';     //strips quotes from the end of the line 
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

    FILE *fp = fopen(filename, "r");    //create a FILE pointer variable to store the file to parse 
    if (fp == NULL)
    {
        perror("fopen");
        return -1; 
    }
    char line[256];     //create a char array to store each line as it's parsed
    int count = 0;      //create a count variable to track how many items are in the list 
    while (fgets(line, sizeof(line), fp) != NULL && count <= maxItems)      //executes while the given file has data
    {
        char *next_item = line;     //creates pointer variable to use with strsep() function 
        strncpy(items[count].itemName, quote_remover(strsep(&next_item, ",")), MAX_ITEM_NAME_STRING);   //store item name in itemName var of struct
        strncpy(items[count].itemDescription, quote_remover(strsep(&next_item, ",")), MAX_ITEM_DESCRIPTION_STRING);     //store description in itemDescription var of struct
        strncpy(items[count].targetAsset, quote_remover(strsep(&next_item, ",")), MAX_ASSET_TYPE_STRING);   //store target in targetAsset var of struct
        strncpy(items[count].actionText, quote_remover(strsep(&next_item, ",")), MAX_ACTION_TEXT_STRING);   //store action in actionText var of struct
        items[count].itemUse = atoi(strsep(&next_item, ","));   //store use int in itemUse var of struct
        count++; 
    }
    fclose(fp);        //close the file 

    if (count == 0)
    {
        return -1;      //return -1 if the item list is empty 
    }

    return count;       //return number of items in list 
}

//look for the item with the specified name itemName.  Returns NULL if not found.
Item *ItemFindByName(Item items[], int maxItems, char *itemName)
{
    for (int i = 0; i < maxItems; i++)  //execute while there are items in the list 
    {
        if (itemName != NULL && items != NULL)  //execute if itemName and list of items not NULL
        {
            if (strcmp(items[i].itemName, itemName) == 0)   //execute if the given item matches an item in the list
            {
                return &items[i];   //return the matching item 
            }
        }
    }
    return NULL;    //return NULL if item is not found 
    }

// display the item.  displayAll = 0 shows the name, otherwise name and description.
void ItemShow(void *pItem, int displayAll)
{
    //TO-DO
    (void)pItem; (void)displayAll;
}
