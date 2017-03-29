#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "renderer.h"
#include "block_factory.h"
#include "controller.h"

// Create grid and initialize all cells to zero (empty)
void initialize_grid(int grid[GRID_W][GRID_H]) {
    for (int x=0; x<GRID_W; x++)
        for (int y=0; y<GRID_H; y++)
            grid[x][y] = 0;
}

int main(int argc, char** argv) {
    // Seed random generator for block spawning
    srand(time(NULL));

    int grid[GRID_H][GRID_W];
    initialize_grid(grid);

    set_up_screen();
    begin_game(grid);
}

