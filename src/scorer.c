#include "scorer.h"

void shift_rows_down(int grid[GRID_W][GRID_H]) {
    int c, r, shift = 0;

    for (r=GRID_H-1; r>=0; r--) {
        // This loop moves from the bottom of the grid upwards
        // to count how many times we need to shift populated
        // rows downwards
        for (c=0; c<GRID_W; c++) {
            if (grid[c][r] != EMPTY) {
                break;
            }
        }

        if (c == GRID_W) {
            // cumulate # rows to shift downwards
            shift++;
        } else if (shift > 0) {
            // if row is populated and there are empty rows
            // beneath it, perform shift
            for (c=0; c<GRID_W; c++) {
                grid[c][r+shift] = grid[c][r];
                grid[c][r] = EMPTY;
            }
        }
    }
}

int is_empty(int grid[GRID_W][GRID_H]) {
    for (int i=0; i<GRID_W; i++) {
        if (grid[i][GRID_H-1] != EMPTY) {
            return 0;
        }
    }

    return 1;
}

int set_speed(int level, int curr_speed) {
    switch (level) {
        case 0: return 48;
        case 1: return 43;
        case 2: return 38;
        case 3: return 33;
        case 4: return 28;
        case 5: return 23;
        case 6: return 18;
        case 7: return 13;
        case 8: return 8;
        case 9: return 6;
        case 10: return 5;
        case 13: return 4;
        case 16: return 3;
        case 19: return 2;
        case 29: return 1;
        default: return curr_speed;
    }
}

void score_block(State* s) {
    s->score += 10 * (s->level+1);
    s->block_count++;

    if (s->block_count == CRITICAL_BLOCK) {
        s->block_count = 0;
        s->level++;
        s->speed = set_speed(s->level, s->speed);
    }
}

void score_rows(State* s, int rows_cleared) {
    int multiplier = 0;
    switch (rows_cleared) {
        case 1: multiplier = 50; break;
        case 2: multiplier = 150; break;
        case 3: multiplier = 350; break;
        case 4: multiplier = 1000; break;
        default: break;
    }

    if (is_empty(s->grid)) {
        multiplier += 2000;
    }

    s->score += multiplier * (s->level);
}

void clear_row(int r, State* s) {
    for (int c=0; c<GRID_W; c++) {
        s->grid[c][r] = EMPTY;
    }
}

void clear_rows(State* s) {
    int c,
        r,
        rows_full = 0;

    for (int i=0; i<4; i++) {
        // for each row that the block occupies
        r = s->block->y + s->block->cells[i][1];
        for (c=0; c<GRID_W; c++) {
            if (s->grid[c][r] == EMPTY) {
                break;
            }
        }

        // if that row is empty, clear it
        if (c == GRID_W) {
            clear_row(r, s);
            rows_full++;
        }
    }

    // shift all rows down to occupy cleared rows
    if (rows_full > 0) {
        shift_rows_down(s->grid);
        score_rows(s, rows_full);
    }
}

void update_score(State* s) {
    score_block(s);
    clear_rows(s);
}

