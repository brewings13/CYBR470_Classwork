#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Location.h"

static char *quote_remover(char *line_to_strip)     //removes quotes from each line item, same as item.c
{   
    if (line_to_strip == NULL)
    {
        return NULL; 
    }
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
 *  Loads the map from filename into locations[].  Each line of the file is:
 *      "name","description","assetType",protected,north,east,south,west,target
 *  Returns the number of locations loaded, or -1 if the file cannot be
 *  opened or no valid locations are found.  Malformed lines are skipped.
 */
int LocationReadMap(Location locations[], int maxLocations, char *filename)     //inits location vars, same as item.c
{
    FILE *fp = fopen(filename, "r"); 
    if (fp == NULL)
    {
        perror("fopen");
        return -1; 
    }
    char line[256]; 
    int count = 0; 
    while (fgets(line, sizeof(line), fp) != NULL && count <= maxLocations)
    {
        char *next_item = line; 
        strncpy(locations[count].name, quote_remover(strsep(&next_item, ",")), MAX_LOC_NAME_STRING); 
        strncpy(locations[count].description, quote_remover(strsep(&next_item, ",")), MAX_LOC_DESCRIPTION_STRING); 
        strncpy(locations[count].asset.type, quote_remover(strsep(&next_item, ",")), MAX_ASSET_TYPE_STRING);
        if (*locations[count].asset.type != '\0')
        {
            locations[count].asset.present = true;
        }
        locations[count].asset.is_protected = atoi(strsep(&next_item, ","));
        locations[count].north = atoi(strsep(&next_item, ","));
        locations[count].east = atoi(strsep(&next_item, ","));
        locations[count].south = atoi(strsep(&next_item, ","));
        locations[count].west = atoi(strsep(&next_item, ","));
        locations[count].asset.is_target = atoi(strsep(&next_item, ","));
        count++; 
    }
    fclose(fp); 

    if (count == 0)
    {
        return -1; 
    }

    return count;
}

// attempt to use pTool against the asset in pLocation.  Returns an EXPLOIT_* code.
int LocationExploit(Location *pLocation, Item *pTool)
{
    if (pTool == NULL || pTool->itemUse == 0)       //executes if the item being used is not a tool
    {
        return EXPLOIT_NOT_A_TOOL;
    }
   
    if (strcmp(pTool->targetAsset, pLocation->asset.type) != 0 && *pLocation->asset.type != '\0')   //executes if the item target does not match target at location
    {
        return EXPLOIT_WRONG_TARGET;
    }

    if (pTool != NULL && pTool->itemUse == 2)       //executes if the tool is not NULL and is an exploit tool
    {
        if (strcmp(pTool->targetAsset, pLocation->asset.type) == 0)     //if the tool target matches the item in the room
        {
            if (pLocation->asset.is_protected == 1)     //executes if asset is protected
            {
                return EXPLOIT_BLOCKED;
            }
            if (pLocation->asset.infected == true)      //executes if asset is already infected
            {
                return EXPLOIT_ALREADY_INFECTED;
            }
            pLocation->asset.infected = true;       //set infected status to true
            return EXPLOIT_SUCCESS;     //successful exploit
        }
    }
    
    return EXPLOIT_NO_ASSET;
}

void LocationAddItem(Location *pLocation, void *pItem)  //adds item to location
{
    InventoryAdd(&pLocation->items, pItem);
}

void LocationRemoveItem(Location *pLocation, void *pItem)   //removes item from location
{
    InventoryRemove(&pLocation->items, pItem); 
}

bool LocationHasItem(Location *pLocation, void *pItem)      //checks if item is at location 
{
    if (InventoryHas(&pLocation->items, pItem))
    {
        return true; 
    } 
    return false;
}
