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
int spawn_space_available(State* s);

void spawn_I(Block* b);
void spawn_O(Block* b);
void spawn_T(Block* b);
void spawn_Z(Block* b);
void spawn_S(Block* b);
void spawn_J(Block* b);
void spawn_L(Block* b);

#endif

