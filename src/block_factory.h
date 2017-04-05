#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

void copy_cells(BlockType t, int cells[4][2]);
BlockType spawn(Block* b, BlockType t);
void spawn_I(Block* b);
void spawn_O(Block* b);
void spawn_T(Block* b);
void spawn_Z(Block* b);
void spawn_S(Block* b);
void spawn_J(Block* b);
void spawn_L(Block* b);

#endif

