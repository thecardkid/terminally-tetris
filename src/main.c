#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#include "utils.h"
#include "renderer.h"

#define DELAY 500000

int p = 1;
void update_piece(int grid[GRID_H][GRID_W]) {
    grid[p-1][4] = Empty;
    grid[p-1][5] = Empty;
    grid[p-1][6] = Empty;
    grid[p][4] = Cyan;
    grid[p][5] = Cyan;
    grid[p+1][6] = Cyan;

    if (p <= GRID_H) p++;
}

void begin_game(int grid[GRID_H][GRID_W]) {
    while (1) {
        clear();
        render(grid);
        refresh();
        update_piece(grid);
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
    begin_game(grid);
}

