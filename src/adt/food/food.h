#ifndef FOOD_H
#define FOOD_H

#include <stdio.h>
#include "../time/time.h"
#include "../charmachinefood/charmachine.c"
#include "../wordmachinefood/wordmachine.c"

typedef struct
{
    int id;
    Word name;
    Time exptime;
    Time deltime;
    Word act;
} Food;

#define Id(f) (f).id
#define Name(f) (f).name
#define ExpTime(f) (f).exptime
#define DelTime(f) (f).deltime
#define Act(f) (f).act

void addID(Foodlist *f, int i);
void addName(Foodlist *f, int i);
void addExpTime(Foodlist *f, int i);
void addDelTime(Foodlist *f, int i);
void addAct(Foodlist *f, int i);
void addList();
void displayFood(Food food);

#endif