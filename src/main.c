#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#include "utils.h"
#include "renderer.h"

#define US 1000000 // 1 million microseconds per second
#define TICK_RATE 60 // Steps per second
#define DELAY US/TICK_RATE // Delay in microseconds to achieve tick rate
#define MOVE_RATE 12 // Steps per movement

/*
    Initialize a given block as a new block of random type.
*/
void spawn_block(Block *block) {
    // TODO: @hnguyen Make this random
    block->color = Purple;
    memcpy(block->cells, TBlock, sizeof(TBlock));
    block->xpos = GRID_W/2 - 1; 
    block->ypos = 2;
}

/*
    Given a block and a desired shifting of that block,
    check to see if there are any obstructions in the way.

    If no obsctructions are present, move the block into new position.

    Only a change in x position is passed as a parameter since
    all movements include 1 step down no matter what.

    Rotations of the block should be performed before attempting movement.

    @returns 0 if the block was blocked from moving vertically, indicating that
    the block has "settled" and will no longer be interactive
*/
int move_block(int grid[GRID_W][GRID_H], Block *block, int delta_x) {
    // Clear cells occupied by the block
    for (int i = 0; i < 4; i++) {
        int x = block->cells[i][0] + block->xpos;
        int y = block->cells[i][1] + block->ypos;

        grid[x][y] = Empty;
    }

    // Check the cells that the shift would move the block into for emptyness
    int canMove = 1;

    // Check for collision with bottom of stage
    if (block->ypos >= GRID_H - 2) canMove = 0;

    // Check for collision with other blocks and sides of stage
    if (canMove) {
        for (int i = 0; i < 4; i++) {
            int x = block->cells[i][0] + block->xpos;
            int y = block->cells[i][1] + block->ypos;

            // Check for collision with sides of stage
            if (x + delta_x < 0 || x + delta_x > GRID_W - 1) delta_x = 0;

            // Check for collision with other blocks
            if (grid[x + delta_x][y + 1] != Empty) {
                canMove = 0;
                break;
            }
        }
    }

    // Update block position if no collisions
    if (canMove) {
        block->xpos += delta_x;
        block->ypos++;
    }

    // Set cells occupied by block to correct color
    for (int i = 0; i < 4; i++) {
        int x = block->cells[i][0] + block->xpos;
        int y = block->cells[i][1] + block->ypos;

        grid[x][y] = block->color;
    }

    return canMove;
}

void begin_game(int grid[GRID_W][GRID_H]) {
    // Hardcoded to spawn block at beginning of game
    // TODO @hnguyen
    Block *block = malloc(sizeof(Block));
    block->color = Yellow;
    memcpy(block->cells, OBlock, sizeof(OBlock));
    block->xpos = GRID_W/2 - 1; 
    block->ypos = 2;

    int frameCounter = 0;
    while (1) {
        frameCounter++;

        // Rendering loop
        clear();
        render(grid);
        refresh();

        // Piece movement
        if (frameCounter >= MOVE_RATE) {
            // TODO: @skelly override frame counter to force downward move on user input
            // TODO: @skelly provide horizontal movement on user input
            if (!move_block(grid, block, 0)) {
                // Block has hit the bottom of stage or top of another block
                // No longer meaningful to keep track of the block

                // Spawn a new block
                spawn_block(block);
            }
            frameCounter = 0;
        }

        usleep(DELAY); // Assuming execution of loop takes negligible time
    }
}

// Create grid and initialize all cells to zero (empty)
void initialize_grid(int grid[GRID_W][GRID_H]) {
    for (int x=0; x<GRID_W; x++)
        for (int y=0; y<GRID_H; y++)
            grid[x][y] = 0;
}

int main(int argc, char** argv) {
    int grid[GRID_W][GRID_H];
    initialize_grid(grid);

    set_up_screen();
    begin_game(grid);
}

