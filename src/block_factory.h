#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

void copy_cells(BlockType t, int cells[4][2]);
void spawn(State* s);

/*
 * Make sure that all cells occupied by the block are empty.
 * Perform this check immediately after spawning a block so that blocks do not
 * spawn in eachother.
 */
int spawnSpaceAvailable(State* s);

void spawnI(Block* b);
void spawnO(Block* b);
void spawnT(Block* b);
void spawnZ(Block* b);
void spawnS(Block* b);
void spawnJ(Block* b);
void spawnL(Block* b);

#endif

