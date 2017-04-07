#ifndef SCORER_H
#define SCORER_H

#include "utils.h"

/*
 * Helper method used by `clear_rows`
 *
 * @param shift: how many rows to shift by downwards
 */
void shift_rows_down(int grid[GRID_W][GRID_H]);

/*
 * Returns 1 if grid is empty
 */
int is_empty(int grid[GRID_W][GRID_H]);

/*
 * Recompute the height of each column
 */
void compute_heights(State* s);

/*
 * Score a block when it is placed
 */
void score_block(State* s);

/*
 * Score rows cleared. Info from
 * https://www.gamedev.net/topic/290296-does-anyone-know-how-the-scoring-system-works-in-tetris/
 */
void score_rows(State* s, int rows_cleared);

/*
 * Clear row r
 */
void clear_row(int r, State* s);

/*
 * Helper method to clear completed rows
 */
void clear_rows(State* state);

/*
 * Called by the game loop to update the score every time
 * a block has been placed
 */
void update_score(State* state);

#endif
