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
