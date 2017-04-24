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

int can_move_vertically(int x, int y, State* s) {
    int delta_y = s->net_move->y;
    int dy;
    if (delta_y < 0) {
        dy = -1;
    } else {
        dy = 1;
    }

    while (dy*dy <= delta_y*delta_y) {
        if (!in_grid(x, y + dy) || s->grid[x][y + dy] != EMPTY) {
            return 0;
        }

        if (delta_y < 0) {
            dy--;
        } else {
            dy++;
        }
    }

    return 1;
}

int can_move_horizontally(int x, int y, State* s) {
    int delta_x = s->net_move->x;
    int dx;
    if (delta_x < 0) {
        dx = -1;
    } else {
        dx = 1;
    }

    while (dx*dx <= delta_x*delta_x) {
        if (!in_grid(x + dx, y) || s->grid[x + dx][y] != EMPTY) {
            return 0;
        }

        if (delta_x < 0) {
            dx--;
        } else {
            dx++;
        }
    }

    return 1;
}

int move_block_vertically(State* s) {
    Movement* m = s->net_move;
    int can_move_vert = 1;
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        // Conditions where move is invalid
        if (!can_move_vertically(x, y, s)) {
            can_move_vert = 0;
            break;
        }
    }
    if (can_move_vert) {
        s->block->y += m->y;
        m->y = 0; // signal that we have performed this operation
        return 1; // signal that A operation was performed
    } else {
        return 0;
    }
}

int move_block_horizontally(State* s) {
    Movement* m = s->net_move;
    int can_move_horiz = 1;
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        // Conditions where move is invalid
        if (!can_move_horizontally(x, y, s)) {
            can_move_horiz = 0;
            break;
        }
    }
    if (can_move_horiz) {
        s->block->x += m->x;
        m->x = 0;
        return 1;
    } else {
        return 0;
    }
}

int rotate_block(State* s) {
    Movement* m = s->net_move;
    int old_cells[4][2];
    int can_rotate = 1;
    // Make copy of current cells
    memcpy(old_cells, s->block->cells, sizeof(I_Block));
    rotate(s->block);

    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        // Conditions where move is invalid
        if (!in_grid(x, y) || s->grid[x][y] != EMPTY) {
            can_rotate = 0;
            break;
        }
    }

    if (!can_rotate) {
        // Undo rotation
        if (m->r) {
            memcpy(s->block->cells, old_cells, sizeof(I_Block));
        }
        return 0;
    } else {
        m->r = 0;
        return 1;
    }
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

