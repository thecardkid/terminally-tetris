#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

/*
 * A synonym for memcpy
 */
void copy_cells(BlockType t, int cells[4][2]);

/*
 * Choose the next block based on this logic:
 * 1. Pick a random num between 0-7 (7 being a dummy). If
 *    the result is 7 or the current block, go to step 2.
 * 2. Pick a random num between 0-6.
 * Return that number
 * Source: https://gaming.stackexchange.com/questions/13057/tetris-difficulty
 */
BlockType choose_next(BlockType current);

/*
 * Make sure that all cells occupied by the block are empty.
 * Perform this check immediately after spawning a block so that blocks do not
 * spawn in eachother.
 */
int spawn_space_available(State* s);

void spawn(State* s);
void spawn_I(Block* b);
void spawn_O(Block* b);
void spawn_T(Block* b);
void spawn_Z(Block* b);
void spawn_S(Block* b);
void spawn_J(Block* b);
void spawn_L(Block* b);

#endif

