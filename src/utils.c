#include "utils.h"

// Note that here the positive Y axis points "down"
const int I_Block[4][2] = {{0,0}, {2,0}, {-1,0}, {1,0}};
const int O_Block[4][2] = {{0,0}, {1,0}, {1,-1}, {0,-1}};
const int T_Block[4][2] = {{0,0}, {1,0}, {-1,0}, {0,-1}};
const int Z_Block[4][2] = {{0,0}, {1,0}, {0,-1}, {-1,-1}};
const int S_Block[4][2] = {{0,0}, {-1,0}, {0,-1}, {1,-1}};
const int J_Block[4][2] = {{0,0}, {1,0}, {-1,0}, {-1,-1}};
const int L_Block[4][2] = {{0,0}, {-1,0}, {1,0}, {1,-1}};
const int ROTATION_MATRIX_R[2][2] = {{0,1}, {-1,0}};

int in_grid(int x, int y) {
    if (x < 0 || x >= GRID_W || y < 0 || y >= GRID_H) return 0;
    return 1;
}

void clear_block(State* s) {
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        s->grid[x][y] = EMPTY;
    }
}

void clear_ghost(State* s) {
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->ghosty;

        s->grid[x][y] = EMPTY;
    }
}

void draw_block(State* s) {
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        s->grid[x][y] = s->block->color;
    }
}

void draw_ghost(State* s) {
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->ghosty;

        s->grid[x][y] = GHOST;
    }
}

void project_ghost(State* s) {
    int ghost_y = s->block->y;

    if (ghost_y > GRID_H-OFFSET) ghost_y = GRID_H-OFFSET;

    // It can be assumed that the ghost fits in the starting position since
    //  it starts in the same place as the block.
    while (ghost_y < GRID_H) {
        int can_move_down = 1;
        for (int i = 0; i < 4; i++) {
            int x = s->block->cells[i][0] + s->block->x;
            int y = s->block->cells[i][1] + ghost_y;

            if(!in_grid(x, y+1) || s->grid[x][y+1] != EMPTY) {
                can_move_down = 0;
            }
        }

        if (can_move_down) {
            ghost_y++;
        } else {
            break;
        }
    }

    s->block->ghosty = ghost_y;
}

void increment_with_max(int* num, int max) {
    (*num)++;
    if (*num > max) {
        *num = max;
    }
}

void decrement_with_min(int* num, int min) {
    (*num)--;
    if (*num < min) {
        *num = min;
    }
}

void initialize_grid(int grid[GRID_W][GRID_H]) {
    for (int x=0; x<GRID_W; x++) {
        for (int y=0; y<GRID_H; y++) {
            grid[x][y] = EMPTY;
        }
    }
}

void rotate(Block* b){
    if (b->type == O) {
        return;
    }

    int rotated_cells[4][2], sum;

    for (int i = 0; i < 4; i++) {//row of first matrix
        for (int j = 0; j < 2; j++) {   //column of second matrix
            sum = 0;
            for (int k = 0; k < 2; k++) {
                sum += (b->cells[i][k]) * ROTATION_MATRIX_R[k][j];
                rotated_cells[i][j]=sum;
            }
        }
    }

    // reassign block's cells to the rotated coordinates
    memcpy(b->cells, rotated_cells, sizeof(b->cells));
};

