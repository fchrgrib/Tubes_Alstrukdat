#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void setMapRow(MatrixChar *map, char rowContent[], int row)
{
    for (int j = 0; j < (*map).colEff; j++)
    {
        if (j == 0 || j == (*map).colEff - 1)
        {
            (*map).buffer[row][j] = '*';
        }
        else
        {
            (*map).buffer[row][j] = rowContent[j - 1];
        }
    }
}

void setMapDimension(int *mapRow, int *mapCol)
{
    // char directory[] = "../../../config/map.txt";
    char rowStr[NMAX], colStr[NMAX];

    startWord(mapConfig);
    wordToStr(currentWord, rowStr);
    advWord();
    wordToStr(currentWord, colStr);

    *mapRow = atoi(rowStr) + 2;
    *mapCol = atoi(colStr) + 2;
}

void setMapMatrix(MatrixChar *map)
{
    // char directory[] = "../../../config/map.txt";
    startWord(mapConfig);
    advWord();

    // Set top border
    for (int j = 0; j < (*map).colEff; j++)
    {
        (*map).buffer[0][j] = '*';
    }

    // Set bottom border
    for (int j = 0; j < (*map).colEff; j++)
    {
        (*map).buffer[(*map).rowEff - 1][j] = '*';
    }

    // Set map content
    for (int i = 1; i < (*map).rowEff - 1; i++)
    {
        advWord();
        char temp[NMAX];
        wordToStr(currentWord, temp);
        setMapRow(map, temp, i);
    }
}

void setMap(MatrixChar *map)
{
    int mapRow, mapCol;
    setMapDimension(&mapRow, &mapCol);
    createMatrix(map, mapRow, mapCol);
    setMapMatrix(map);
}

void renderMap(MatrixChar m)
{
	printf("fdfdfd\n");
    for (int i = 0; i < m.rowEff; i++)
    {
        for (int j = 0; j < m.colEff; j++)
        {
            if (m.buffer[i][j] == '#')
            {
                printf("  ", m.buffer[i][j]);
            }
            else
            {
                printf("%c ", m.buffer[i][j]);
            }
        }
        printf("\n");
    }
}
