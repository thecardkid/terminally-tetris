#ifndef ROTATE_H
#define ROTATE_H

#include <string.h>
#include "utils.h"

/* Rotates block 90 degrees
using matrix multiplication with rotation matrix.*/
void rotate_block(Block* b, const int rotation_matrix[2][2]);

/* Rotates block 90 degrees CLOCKWISE.
Checks block type for exception rotation cases. */
void rotate_right(Block* b);

/* Rotates block 90 degrees COUNTER-CLOCKWISE.
Checks block type for exception rotation cases. */
void rotate_left(Block *b);

#endif
