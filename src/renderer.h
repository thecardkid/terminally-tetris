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

/*
 * Display control menu
 *
 * @param row: row to print from
 * @return row: last row printed on
 */
int display_controls(int row);

/*
 * Display next block that will spawn
 *
 * @param row: row to print from
 * @param next: block that will spawn next
 */
void display_preview(int row, BlockType next);

/*
 * Called by the controller, this renders the
 * current game state
 */
void render(State* state);

#endif

