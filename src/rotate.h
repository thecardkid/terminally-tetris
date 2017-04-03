#ifndef ROTATE_H
#define ROTATE_H

#include "utils.h"

void rotate_block(Block* b, const int rotation_matrix[2][2]);

void rotate_right(Block* b);
void rotate_left(Block *b);

#endif
