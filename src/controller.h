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
 * Modify stdin, check for valid user input, and revert stdin to original state.
 *
 * termios - http://man7.org/linux/man-pages/man3/tcsetattr.3.html
 * fcntl - http://man7.org/linux/man-pages/man2/fcntl.2.html
*/
int is_user_input();

/*
 * Default text for when boss mode is incurred and
 * `popen` fails
 */
void default_boss_mode();

/*
 * Pipes the output of `ls -l /etc/` to a file stream
 * and then to the ncurses window, making it look like
 * you were doing work
 */
void boss_mode();

/*
 * Modify the state of the game based on user input
 */
void act_on_user_input(char user_input, Movement* m, int* frame_counter);

/*
 * Most basic movement in the game, attempt to move block down by one step. If
 * this movement is obstructed, return 0.
 *
 * Moves have a set ordering in which they will be executed in the case that
 * some combination of movements is impossible.
 *  1: vertical move
 *  2: horizontal move
 *  3: rotational move
 * in the event that one of these sub-moves is impossible, it will be re-tried
 * once all other sub-moves in the movement are executed.
 */
int move_block(State* s, Movement* m);

/*
 * Collect total movements from all sources
 */
void aggregate_movement(Movement* m, State* s, int* frame_counter);

void begin_game(State* state);

#endif
