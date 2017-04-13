#include "utils.h"

// Note that here the positive Y axis points "down"
const int I_Block[4][2] = {{0,0}, {2,0}, {-1,0}, {1,0}};
const int O_Block[4][2] = {{0,0}, {1,0}, {1,-1}, {0,-1}};
const int T_Block[4][2] = {{0,0}, {1,0}, {-1,0}, {0,-1}};
const int Z_Block[4][2] = {{0,0}, {1,0}, {0,-1}, {-1,-1}};
const int S_Block[4][2] = {{0,0}, {-1,0}, {0,-1}, {1,-1}};
const int J_Block[4][2] = {{0,0}, {1,0}, {-1,0}, {-1,-1}};
const int L_Block[4][2] = {{0,0}, {-1,0}, {1,0}, {1,-1}};
const int rotation_matrix_L[2][2] = {{0,-1}, {1,0}};
const int rotation_matrix_R[2][2] = {{0,1}, {-1,0}};

int in_grid(int x, int y) {
    if (x < 0 || x >= GRID_W || y < 0 || y >= GRID_H) return 0;
    return 1;
}

void project_ghost(State* s) {
    int x,
        y = s->block->y + 3;
    int i;
    int r, c;
    int has_space = 1;

    for (int h=y; h<GRID_H-OFFSET; h++) {
        x++; y++;
        for (i=0; i<4; i++) {
            r = y + s->block->cells[i][1];
            x = s->block->x + s->block->cells[i][0];
            has_space = (s->grid[c][r] == EMPTY) && has_space;
        }

        if (!has_space) {
            break;
        }
    }

    s->block->ghostx = s->block->x;
    s->block->ghosty = y-1;
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
