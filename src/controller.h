#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "utils.h"
#include "renderer.h"
#include "block_factory.h"

#define US 1000000 // 1 million microseconds per second
#define TICK_RATE 60 // Steps per second
#define US_DELAY US/TICK_RATE // Delay in microseconds to achieve tick rate
#define MOVE_RATE 20 // Steps per movement


/*
 * Check if the user has pressed any keys
 */
int is_user_input();

/*
 * Modify the state of the game based on user input
 */
void act_on_user_input(char user_input, int grid[GRID_W][GRID_H],
    int* frame_counter, Block* block);

/*
 * Check if y coordinate has hit the bottom of the grid
 *
 * @param y: current y coordinate of the block
 */
int hit_bottom_grid(int y);

/*
 * Check if horizontal translation is allowed
 *
 * @param x: current x coordinate of the block
 * @param delta_x: horizontal translation of block
 */
int is_within_grid(int x, int delta_x);

/*
 * Helper method used by `clear_rows`
 *
 * @param shift: how many rows to shift by downwards
 * @param grid: tetris game state
 */
void shift_rows_down_by(int shift, int grid[GRID_W][GRID_H]);

/*
 * Helper method used by the game loop that clears
 * completed rows
 *
 * @param grid: tetris game state
 */
void clear_rows(int grid[GRID_W][GRID_H]);

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

#endif

