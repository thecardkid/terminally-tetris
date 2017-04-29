#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>

#include "utils.h"
#include "block_factory.h"

/*
 * Set up ncurses and attribute key-value pairs
 * for rendering
 */
void set_up_screen();

/*
 * Display current game grid
 */
void display_grid(int grid[GRID_W][GRID_H]);

void display_endgame(State* s);

/*
 * Display control menu
 *
 * @param row: row to print from
 * @return row: last row printed on
 */
int display_controls(int row);

/*
 * Display method for NEXT and HOLD
 * @param row: row to print from
 * @param next: block to render
  */
void display_preview(int row, BlockType next);

/*
 * Display block currently on hold
 * @param row: row to print from
 * @param next: block currently in hold domain
  */
void display_hold(int row, Block* b);

/*
 * Display next block that will spawn
 *
 * @param row: row to print from
 * @param next: block that will spawn next
 */
void display_block(int row, int col, int cells[4][2], BlockType type);

/*
 * Default text for when boss mode is incurred and
 * `popen` fails
 */
void render_default_boss_mode();

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
void render_menu(const char* title,
        const char* items[],
        int num_items,
        int selection);

/*
 * Called by the controller, this renders the
 * current game state
 */
void render(State* state);

#endif
