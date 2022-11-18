#include <stdio.h>
#include <stdlib.h>
#include "gameState.h"
#include "../inventory/inventory.h"
#include "../delivery/delivery.h"
// add include for mac

// Sim Name
char simName[50];

// Find sPos
Point setSimPos(MatrixChar map)
{
    Point simPos;
    for (int i = 0; i < map.rowEff; i++)
    {
        for (int j = 0; j < map.colEff; j++)
        {
            if (map.buffer[i][j] == 'S')
            {
                createPoint(&simPos, j - 1, i - 1);
                return simPos;
            }
        }
    }
}

// Set time
Time setTime(int day, int hour, int minute)
{
    Time retTime;
    createTime(&retTime, day, hour, minute);
    return retTime;
}

// Constructor
void setGameState(GameState *gs, MatrixChar map, Queue inventory, Queue delivery)
{
    // Set sPos
    (*gs).simPos = setSimPos(map);
    // Set time
    (*gs).time = setTime(0, 5, 0);
    // Set inventory
    (*gs).inventory = inventory;
    // Set delivery
    (*gs).delivery = delivery;
    // Set action
    updateAvailableAction(gs, map);
}

// Display
void renderGameState(GameState gs)
{
    printf("\n");

    printf("Posisi %s: (%d,%d)\n", simName, gs.simPos.X, gs.simPos.Y);

    printf("Waktu: ");
    displayTime(gs.time);
    printf("\n");

    printf("Notifikasi: -\n");
    printf("\n");
}

// Update map
void updateMap(GameState gs, MatrixChar *map)
{
    Point currentPos = gs.simPos;
    for (int i = 0; i < (*map).rowEff; i++)
    {
        for (int j = 0; j < (*map).colEff; j++)
        {
            if ((*map).buffer[i][j] == 'S')
            {
                (*map).buffer[i][j] = '#';
            }
        }
    }
    (*map).buffer[currentPos.Y + 1][currentPos.X + 1] = 'S';
}

// Update delivery
void updateDeliveryTime(Queue *delivery, Queue *inventory, int day, int hour, int minute)
{
    address pointer = ADDR_HEAD(*delivery);
    for (int i = 0; i < length(*delivery); i++)
    {
        int subMinutes = (1440 * day) + (60 * hour) + minute;
        Time subTime = minuteToTime(subMinutes);

        Time oldTime = Info(pointer).deltime;
        int oldMinutes = timeToMinute(oldTime);

        if (oldMinutes < subMinutes)
        {
            Food food;
            delDelivery(delivery, &food);
            AddInventory(inventory, food);
        }
        else
        {
            int newMinutes = oldMinutes - subMinutes;
            Time newTime = minuteToTime(newMinutes);
            Info(pointer).deltime = newTime;
        }

        pointer = Next(pointer);
    }
}

// Update delivery
void updateExpirationTime(Queue *inventory, int day, int hour, int minute)
{
    address pointer = ADDR_HEAD(*inventory);
    for (int i = 0; i < length(*inventory); i++)
    {
        int subMinutes = (1440 * day) + (60 * hour) + minute;
        Time subTime = minuteToTime(subMinutes);

        Time oldTime = Info(pointer).exptime;
        int oldMinutes = timeToMinute(oldTime);

        if (oldMinutes <= subMinutes)
        {
            Food food;
            delInventory(inventory, &food);
        }
        else
        {
            int newMinutes = oldMinutes - subMinutes;
            Time newTime = minuteToTime(newMinutes);
            Info(pointer).exptime = newTime;
        }

        pointer = Next(pointer);
    }
}

// Update time
void updateTime(GameState *gs, int day, int hour, int minute)
{
    int minutes = timeToMinute((*gs).time);
    int addedMinutes = (1440 * day) + (60 * hour) + minute;
    int totalMinute = minutes + addedMinutes;
    (*gs).time = minuteToTime(totalMinute);
}

// Update available action
void updateAvailableAction(GameState *gs, MatrixChar map)
{
    // isAbleBuy
    if ((map.buffer[(*gs).simPos.Y][(*gs).simPos.X + 1] == 'T') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X + 2] == 'T') || (map.buffer[(*gs).simPos.Y + 2][(*gs).simPos.X + 1] == 'T') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X] == 'T'))
    {
        (*gs).isAbleBuy = 1;
    }
    else
    {
        (*gs).isAbleBuy = 0;
    }

    // isAbleChop
    if ((map.buffer[(*gs).simPos.Y][(*gs).simPos.X + 1] == 'C') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X + 2] == 'C') || (map.buffer[(*gs).simPos.Y + 2][(*gs).simPos.X + 1] == 'C') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X] == 'C'))
    {
        (*gs).isAbleChop = 1;
    }
    else
    {
        (*gs).isAbleChop = 0;
    }

    // isAbleMix
    if ((map.buffer[(*gs).simPos.Y][(*gs).simPos.X + 1] == 'M') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X + 2] == 'M') || (map.buffer[(*gs).simPos.Y + 2][(*gs).simPos.X + 1] == 'M') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X] == 'M'))
    {
        (*gs).isAbleMix = 1;
    }
    else
    {
        (*gs).isAbleMix = 0;
    }

    // isAbleFry
    if ((map.buffer[(*gs).simPos.Y][(*gs).simPos.X + 1] == 'F') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X + 2] == 'F') || (map.buffer[(*gs).simPos.Y + 2][(*gs).simPos.X + 1] == 'F') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X] == 'F'))
    {
        (*gs).isAbleFry = 1;
    }
    else
    {
        (*gs).isAbleFry = 0;
    }

    // isAbleBoil
    if ((map.buffer[(*gs).simPos.Y][(*gs).simPos.X + 1] == 'B') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X + 2] == 'B') || (map.buffer[(*gs).simPos.Y + 2][(*gs).simPos.X + 1] == 'B') || (map.buffer[(*gs).simPos.Y + 1][(*gs).simPos.X] == 'B'))
    {
        (*gs).isAbleBoil = 1;
    }
    else
    {
        (*gs).isAbleBoil = 0;
    }
}
