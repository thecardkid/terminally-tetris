#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "utils.h"
#include "renderer.h"
#include "block_factory.h"
#include "controller.h"

// Create grid and initialize all cells to zero (empty)
void initialize_grid(int grid[GRID_W][GRID_H]) {
    for (int x=0; x<GRID_W; x++) {
        for (int y=0; y<GRID_H; y++) {
            grid[x][y] = Empty;
        }
    }
}

State* create_game() {
    State* state = malloc(sizeof(State));
    initialize_grid(state->grid);
    state->score = 0;
    // TODO @hnguyen accept command line argument for level
    state->level = 1;
    return state;
}

int main(int argc, char** argv) {
    // Seed random generator for block spawning
    srand(time(NULL));

    int grid[GRID_W][GRID_H];
    initialize_grid(grid);
    State* state = create_game();

    set_up_screen();
    begin_game(state);
}

