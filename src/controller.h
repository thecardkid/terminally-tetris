#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>

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
 * Increment an integer by one without surpassing a specified maximum
 *
 * @param num: the integer to increment
 * @param max: the maximum value that the integer can be incremented to
 */
void increment_with_max(int* num, int max);

/*
 * Decrement an integer by one without surpassing a specified minimum
 *
 * @param num: the integer to deccrement
 * @param max: the minimum value that the integer can be deccremented to
 */
void decrement_with_min(int* num, int min);

/*
 * Render a user-scrollable menu with specified characteristics
 *
 * @param menu_title: the title line of the menu
 * @param menu_items: an array of items the user can select from
 * @param num_menu_items: the number of items in the menu_items array
 * @param curr_selection: the index of the current user-selected item
 * @param row: row where the menu should render (left-most row)
 * @param col: column where the menu should render (upper-most column)
 */
void render_menu(const char* title, const char* items[], int num_items,
        int curr_selection, int row, int col);

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
 * Pauses the game
 */
void pause_mode();

/*
 * Renders a menu that allows the player to clarify if they want to quit.
 * Quits or resumes based on the user's menu selection.
 */
void quit_mode();

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
