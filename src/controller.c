#include "controller.h"

int hit_bottom_grid(int y) {
    if (y >= GRID_H - 1) return 1;
    return 0;
}

int is_within_grid(int x, int delta_x) {
    if (x + delta_x < 0 || x + delta_x > GRID_W - 1) return 1;
    return 0;
}

int move_block(int grid[GRID_W][GRID_H], Block *block, int delta_x) {
    // Clear cells occupied by the block
    for (int i = 0; i < 4; i++) {
        int x = block->cells[i][0] + block->x;
        int y = block->cells[i][1] + block->y;

        grid[x][y] = Empty;
    }

    // Check the cells that the shift would move the block into for emptyness
    int canMove = 1;

    if (hit_bottom_grid(block->y)) canMove = 0;

    // Check for collision with other blocks and sides of stage
    if (canMove) {
        for (int i = 0; i < 4; i++) {
            int x = block->cells[i][0] + block->x;
            int y = block->cells[i][1] + block->y;

            if (is_within_grid(block->x, delta_x)) delta_x = 0;

            // Check for collision with other blocks
            if (grid[x + delta_x][y + 1] != Empty) {
                canMove = 0;
                break;
            }
        }
    }

    // Update block position if no collisions
    if (canMove) {
        block->x += delta_x;
        block->y++;
    }

    // Set cells occupied by block to correct color
    for (int i = 0; i < 4; i++) {
        int x = block->cells[i][0] + block->x;
        int y = block->cells[i][1] + block->y;

        grid[x][y] = block->color;
    }

    return canMove;
}

void begin_game(int grid[GRID_W][GRID_H]) {
    Block *block = malloc(sizeof(Block));
    BlockType next = spawn(block, rand() % NUM_BLOCKS);

    int frameCounter = 0;
    while (1) {
        frameCounter++;

        // Rendering loop
        clear();
        render(grid);
        refresh();

        // Piece movement
        if (frameCounter >= MOVE_RATE) {
            // TODO: @skelly override frame counter to force downward move on 
            //       user input
            // TODO: @skelly provide horizontal movement on user input
            if (!move_block(grid, block, 0)) {
                // Block has hit the bottom of stage or top of another block. 
                // No longer meaningful to keep track of the 
                // block --> Spawn a new block
                next = spawn(block, next);
            }
            frameCounter = 0;
        }

        // Assuming execution of loop takes negligible time
        usleep(DELAY);
    }
}
