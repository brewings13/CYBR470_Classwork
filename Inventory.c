
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inventory.h"

// set the list to empty with no display handler
void InventoryInit(Inventory *pList)
{
    if (pList != NULL)  //executes if the inventory pointer is not NULL
    {
        pList->count = 0;   //set the list count to 0 
        pList->displayCallback = NULL;  //set the displayCallback to NULL
    }
}

// set the list to empty and remember the display handler
void InventoryInitWithHandlers(Inventory *pList, 
                    DisplayHandler displayCallback)
{
    if (pList != NULL) //executes if the Inventory pointer is not NULL
    {
        pList->count = 0;   //set the count to 0
        pList->displayCallback = displayCallback;   //set the displayCallback struct variable to given displayCallback
    }
}

// add an object to the end of the list.  Returns 1 if added, 0 if not.
int InventoryAdd(Inventory *pList, void *pObject)
{
    if (pList == NULL || pObject == NULL || pList->count >= MAX_OBJECTS)    //if the list or object are NULL or the list is full, return 0
    {
        return 0;
    }
    for (int i = 0; i < pList->count; i++)  //execute while list is not full
    {
        if (pList->objects[i] == pObject)   // if item already in list, return 0
        {
            return 0; 
        }
    }
    pList->objects[pList->count] = pObject;     //add item to list
    pList->count++;     //increment the count to reflect the added item 
    return 1;       //return 1 to reflect successful add
}

// remove an object from the list.  Returns 1 if removed, 0 if not found.
int InventoryRemove(Inventory *pList, void *pObject)
{
    if (pList != NULL)  //executes if the Inventory pointer is not NULL
    {
        for (int i = 0; i < MAX_OBJECTS; i++)   //executes while the iterator is not greater than the max objects
        {
            if (pList->objects[i] == pObject)   //executes if object is found 
            {
                for (int j = i; j < pList->count - 1; j++)  //executes while iterator is less than remaining list count
                {
                    pList->objects[j] = pList->objects[j+1];    //moves each item to the left one spot
                }
                pList->count--;     //decrements count to reflect removed item
                pList->objects[pList->count] = NULL;    //sets space at end of list to NULL to reflect removed item
                return 1;   //returns 1 to reflect successful removal 
            }
        }
    }
    return 0; 
}

// returns true if the object is in the list
bool InventoryHas(Inventory *pList, void *pObject)
{
    if (pList != NULL)  //executes if Inventory pointer is not NULL
    {
        for (int i = 0; i < MAX_OBJECTS; i++)   //executes while the iterator is less than max number of objects
        {
            if (pObject != NULL)    //executes if the object pointer is not NULL
            {
                if (pList->objects[i] == pObject)   //executes if the given object name matches a name in the list
                {
                    return true; 
                }
            }
        }
    }
    return false;
}

// call the display handler for one object
void InventoryDisplayObject(Inventory *pList, void *pObject, int displayOption)
{
    if (pList != NULL)  //executes if the Inventory pointer is not NULL
    {
        pList->displayCallback(pObject, displayOption);     //calls the display handler for one object 
    }
}

// call the display handler for every object in the list
void InventoryDisplayList(Inventory *pList, int displayOption)
{
    if (pList != NULL)  //executes if Inventory pointer is not NULL
    {
        for  (int i = 0; i < pList->count; i++)     //executes while list has items 
        {
            if (pList->displayCallback != NULL)     //executes if the displayCallback struct var is not NULL
            {
                pList->displayCallback(pList->objects[i], displayOption);   //calls display handler
            }
        }
    }
}
