#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

void spawn(State* s);
void spawnI(Block* b);
void spawnO(Block* b);
void spawnT(Block* b);
void spawnZ(Block* b);
void spawnS(Block* b);
void spawnJ(Block* b);
void spawnL(Block* b);

#endif

