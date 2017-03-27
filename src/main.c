#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#include "utils.h"
#include "renderer.h"
#include "block_factory.h"

#define DELAY 500000

void begin_game(int grid[GRID_H][GRID_W]) {
    while (1) {
        clear();
        render(grid);
        refresh();
        usleep(DELAY);
    }
}

// Create grid and initialize all cells to zero
void initialize_grid(int grid[GRID_H][GRID_W]) {
    for (int x=0; x<GRID_H; x++)
        for (int y=0; y<GRID_W; y++)
            grid[x][y] = 0;
}

int main(int argc, char** argv) {
    int grid[GRID_H][GRID_W];
    initialize_grid(grid);

    set_up_screen();
    spawn(L, grid);
    begin_game(grid);
}

