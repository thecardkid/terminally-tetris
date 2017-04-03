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
#include "scorer.h"
#include "rotate.h"

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
void act_on_user_input(char user_input, State* state, int* frame_counter);

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
int move_block(State* state, int delta_x, Rotation r);

void begin_game(State* state);

#endif
