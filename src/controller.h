#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#include "utils.h"
#include "renderer.h"

#define US 1000000 // 1 million microseconds per second
#define TICK_RATE 60 // Steps per second
#define DELAY US/TICK_RATE // Delay in microseconds to achieve tick rate
#define MOVE_RATE 12 // Steps per movement

/*
 * Check if y coordinate has hit the bottom of the grid
 */
int hit_bottom_grid(int y);
int is_within_grid(int x, int delta_x);

/*
 * Given a block and a desired shifting of that block, check to see if there 
 * are any obstructions in the way.
 *
 * If no obsctructions are present, move the block into new position.
 *
 * Only a change in x position is passed as a parameter since all movements 
 * include 1 step down no matter what.
 *
 * Rotations of the block should be performed before attempting movement.
 *
 * @returns 0 if the block was blocked from moving vertically, indicating that 
 * the block has "settled" and will no longer be interactive
*/
int move_block(int grid[GRID_W][GRID_H], Block *block, int delta_x);

void begin_game(int grid[GRID_W][GRID_H]);

