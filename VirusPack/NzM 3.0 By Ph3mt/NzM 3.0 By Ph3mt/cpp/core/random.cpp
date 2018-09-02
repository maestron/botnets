#include "../../headers/includes.h"
#include "../../headers/functions.h"

#include "../../headers/externs.h"

int brandom(int bot,int top) { return (int)((float)(top-bot)*rand()/(RAND_MAX+1.0))+bot; }
int get_random_number(int range) { return rand()%range; }
