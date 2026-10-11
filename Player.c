#include <stdio.h>
#include "Player.h"

void PlayerInit(Player *pPlayer, int locationNumber)    //initiate a player
{
    if (pPlayer != NULL)        //executes if Player pointer is not NULL
    {
        pPlayer->items.count = 0;   //set the count to 0 
        pPlayer->location = locationNumber;     //init the location
    }
}

void PlayerAddItem(Player *pPlayer, void *pItem)    //add to player inventory
{
    if (pPlayer != NULL)    //executes if Player pointer is not NULL
    {
        InventoryAdd(&pPlayer->items, pItem);       //add item to player inventory list 
    }
}

void PlayerRemoveItem(Player *pPlayer, void *pItem)     //remove from player inventory
{
    if (pPlayer != NULL)    //executes if Player pointer is not NULL
    {
        InventoryRemove(&pPlayer->items, pItem);        //remove an item from player inventory list 
    }
}

bool PlayerHasItem(Player *pPlayer, void *pItem)    //check if player has item in inventory 
{
    if (pPlayer != NULL)    //executes if Player pointer is not NULL
    {
        if (InventoryHas(&pPlayer->items, pItem))   //executes if player has item in inventory 
        {
            return true; 
        }
    }        
    return false;
}
