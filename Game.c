
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Inventory.h"
#include "Game.h"

// initialize the game using GAME_DEFAULT_SEED
int GameInitialize(Game *game)
{
    if (game != NULL)
    {
        game->numLocations = 0;
        LocationReadMap(game->map, MAX_MAP_LOCATIONS, "map.txt");  
        game->itemCount = 0; 
        ItemLoadFromFile(game->items, MAX_ITEM_COUNT, "item.txt"); 
        PlayerInit(&game->player, 0); 
        game->moveCount = 0; 
        game->alarmCount = 0; 
        game->dataExfiltrated = false; 
        game->seed = GAME_DEFAULT_SEED;
        return 0;  
    }
    return -1;
}

/*
 *  Loads the map and the items, places the player in location 0 and
 *  scatters the items across the map.  The same seed must always give the
 *  same item placement.  Returns 0 on success, -1 on failure.
 */
int GameInitializeWithSeed(Game *game, unsigned int seed)
{
    if (game != NULL)
    {
        GameInitialize(game); 
        game->seed = seed; 
        return 0; 
    }
    return -1;
}

// count the target assets that have not been infected yet
int GameTargetsRemaining(Game *game)
{
    if (game != NULL)
    {
        int targets_remaining = 3;
        for (int i = 0; i < game->numLocations; i++)
        {
            if (game->map->asset.infected == true)
            {
                targets_remaining--;
            }
        }
        return targets_remaining; 
    }
    return 0; 
}

// returns true once alarmCount has reached MAX_ALARMS
bool GameIsLost(Game *game)
{
    if (game != NULL && game->alarmCount >= MAX_ALARMS)
    {
        return true; 
    } 
    return false;
}
