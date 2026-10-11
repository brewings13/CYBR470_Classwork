
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Game.h"
#include "Display.h"

#define LINE_MAX  128

Game game;


/* -------------------------------------------------------- */
/* LOOK                                                     */
/* -------------------------------------------------------- */

void Look(int location)     //display information about location and assets
{
    Location *pLocation;

    pLocation = &game.map[location];

    printf("\n%s\n%s\n", pLocation->name, pLocation->description);

    printf("Exits: north: %d, south: %d, east: %d, west: %d\n", pLocation->north, pLocation->south, pLocation->east, pLocation->west);   //print exits

    if (pLocation->asset.present == true)   //executes if location has an asset
    {
        if(pLocation->asset.is_protected == true && pLocation->asset.is_target == true)     //executes if asset is a protected target
        {
            printf("%s is a protected asset and is a target.", pLocation->asset.type); 
        }
        if(pLocation->asset.infected == true && pLocation->asset.is_target == true)     //executes if asset is an infected target
        {
            printf("%s is a target that has already been infected.", pLocation->asset.type);
        }
        if(pLocation->asset.is_protected == false && pLocation->asset.is_target == true)       //executes if asset is an unprotected target
        {
            printf("%s is a target and is not protected.", pLocation->asset.type);
        }
        if(pLocation->asset.is_protected == false && pLocation->asset.is_target == false)   //executes if asset is not protected and not a target
        {
            printf("%s is not a target.", pLocation->asset.type);
        }
    }
    /* TODO: list the items in the location (see InventoryDisplayList) */
    InventoryDisplayList(&pLocation->items, MAX_ITEM_COUNT);    //calls InventoryDisplayList to list items in current location
    printf("\n");
}

/* -------------------------------------------------------- */
/* GET_USER_INPUT                                           */
/* -------------------------------------------------------- */

// returns the length of the line, or -1 at end of input
int GetUserInput(char *aline, int max_line)
{
    size_t len;

    printf("> ");
    fflush(stdout);
    if (fgets(aline, max_line, stdin) == NULL)
    {
        return -1;
    }

    len = strlen(aline);
    if (len > 0 && aline[len - 1] != '\n')
    {
        // the line was too long, throw away the rest of it
        int c;
        while ((c = getchar()) != EOF && c != '\n')
        {
        }
    }
    while (len > 0 && (aline[len - 1] == '\n' || aline[len - 1] == '\r'))
    {
        aline[--len] = '\0';
    }
    return (int)len;
}

/* -------------------------------------------------------- */
/* COMMANDS                                                 */
/* -------------------------------------------------------- */

void Move(int destination, char *directionName)
{
    if (destination == -1)
    {
        printf("You can't go %s.\n", directionName);
    }
    else
    {
        game.player.location = destination;
        game.moveCount += 1;
        Look(game.player.location);
    }
}

void Get(char *noun)
{
    Location *pLocation = &game.map[game.player.location];
    Item *pItem;

    if (noun == NULL)
    {
        printf("Get what?\n");
        return;
    }

    // find the item in the game's list of items.
    // We get a pointer or handle to the item
    pItem = ItemFindByName(game.items, game.itemCount, noun);
    if (pItem == NULL || !InventoryHas(&pLocation->items, pItem))
    {
        printf("There is no %s here.\n", noun);
    }
    else if (!InventoryAdd(&game.player.items, pItem))
    {
        printf("You can't carry any more.\n");
    }
    else
    {
        // the handle moves from the location to the player
        InventoryRemove(&pLocation->items, pItem);
        printf("You picked up the %s.\n", noun);
    }
}

void Drop(char *noun)       //drop an item the player is carrying 
{
    
    Location *pLocation = &game.map[game.player.location];
    Item *pItem;

    if (noun == NULL)
    {
        printf("Drop what?\n");
        return;
    }

    // find the item in the game's list of items.
    // We get a pointer or handle to the item
    pItem = ItemFindByName(game.items, game.itemCount, noun);
    if (pItem == NULL || !InventoryHas(&pLocation->items, pItem))
    {
        printf("You are not carrying the %s.\n", noun);
    }else
    {
        // the handle moves from the player to the location
        InventoryAdd(&game.player.items, pItem);
        printf("You picked up the %s.\n", noun);
    }
}


void ShowInventory(void)
{
    if (game.player.items.count > 0)
    {
        printf("You are carrying the following items:\n");
        InventoryDisplayList(&game.player.items, 1);
    }
    else
    {
        printf("You aren't carrying anything.\n");
    }
}

// returns false when the game is over
bool Exploit(Item *pItem)
{
    /* TODO: call LocationExploit for the current location and print a
     * message for each result code:
     *   EXPLOIT_NOT_A_TOOL        "You can't use that here."
     *   EXPLOIT_NO_ASSET          nothing here to use it on
     *   EXPLOIT_WRONG_TARGET      the tool does not work on this asset
     *   EXPLOIT_ALREADY_INFECTED  the asset is already infected
     *   EXPLOIT_BLOCKED           add 1 to game.alarmCount and say defenses
     *                             blocked it.  If GameIsLost, call
     *                             DisplayLose and return false.
     *   EXPLOIT_SUCCESS           set game.dataExfiltrated, show the item's
     *                             actionText.  If GameTargetsRemaining is 0,
     *                             call DisplayWin and return false.
     */
    (void)pItem;
    return true;
}

// returns false when the game is over
bool Use(char *noun)
{
    /* TODO: use the named item.
     *   - no noun:                    "Use what?"
     *   - the player does not have it: "You are not carrying the <noun>."
     *   - otherwise: return Exploit(pItem)
     */
    (void)noun;
    return true;
}

/* -------------------------------------------------------- */
/* PARSE_USER_INPUT                                         */
/* -------------------------------------------------------- */

// returns false when the game is over
bool ParseUserInput(char *aline)
{
    Location *pLocation = &game.map[game.player.location];
    char *verb;
    char *noun;

    // simple parse to get the noun and the verb from the command
    verb = strtok(aline, " \t");
    noun = strtok(NULL, " \t");
    if (verb == NULL)
    {
        return true;
    }

    switch (verb[0])
    {
    case 'n':
    case 'N':
        Move(pLocation->north, "North");
        break;
    case 'e':
    case 'E':
        Move(pLocation->east, "East");
        break;
    case 's':
    case 'S':
        Move(pLocation->south, "South");
        break;
    case 'w':
    case 'W':
        Move(pLocation->west, "West");
        break;
    case 'g':
    case 'G':
        Get(noun);
        break;
    case 'd':
    case 'D':
        Drop(noun);
        break;
    case 'u':
    case 'U':
        return Use(noun);
    case 'i':
    case 'I':
        ShowInventory();
        break;
    case 'l':
    case 'L':
        Look(game.player.location);
        break;
    case 'q':
    case 'Q':
        printf("Thanks for playing!!\n\n");
        return false;
    default:
        printf("I don't know what you want to do.\n");
        break;
    }
    return true;
}

/* -------------------------------------------------------- */
/* MAIN                                                     */
/* -------------------------------------------------------- */
int main(int argc, char *argv[])
{
    char input[LINE_MAX];
    unsigned int seed = GAME_DEFAULT_SEED;
    char *noColor = getenv("NO_COLOR");

    // NO_COLOR is a common convention for turning off terminal colors
    if (noColor != NULL && noColor[0] != '\0')
    {
        DisplaySetColor(false);
    }

    // usage: Exercise6_5 [seed] [--no-color]
    for (int i = 1; i < argc; i++)
    {
        char *end;
        unsigned long value;

        if (strcmp(argv[i], "--no-color") == 0)
        {
            DisplaySetColor(false);
            continue;
        }
        value = strtoul(argv[i], &end, 10);
        if (argv[i][0] == '\0' || argv[i][0] == '-' || *end != '\0')
        {
            fprintf(stderr, "usage: %s [seed] [--no-color]\n", argv[0]);
            return 1;
        }
        seed = (unsigned int)value;
    }

    DisplayTitle();

    if (GameInitializeWithSeed(&game, seed) != 0)
    {
        printf("ERROR: The game could not be loaded.\n");
        return 1;
    }
    printf("Game seed: %u\n", game.seed);

    // Describes the players location, including any items there
    Look(game.player.location);

    // get and process user commands until the game ends
    while (GetUserInput(input, LINE_MAX) >= 0)
    {
        if (!ParseUserInput(input))
        {
            return 0;
        }
    }
    printf("\nThanks for playing!!\n\n");
    return 0;
}
