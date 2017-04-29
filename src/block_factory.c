#include "block_factory.h"

void copy_cells(BlockType t, int cells[4][2]) {
    switch(t) {
        case I: memcpy(cells, I_Block, sizeof(I_Block)); break;
        case O: memcpy(cells, O_Block, sizeof(I_Block)); break;
        case T: memcpy(cells, T_Block, sizeof(I_Block)); break;
        case Z: memcpy(cells, Z_Block, sizeof(I_Block)); break;
        case S: memcpy(cells, S_Block, sizeof(I_Block)); break;
        case J: memcpy(cells, J_Block, sizeof(I_Block)); break;
        case L: memcpy(cells, L_Block, sizeof(I_Block)); break;
    }
}

BlockType choose_next(BlockType current) {
    int n;

    n = rand() % (NUM_BLOCKS + 1);

    if (n == NUM_BLOCKS || n == current) {
        n = rand() % NUM_BLOCKS;
    }

    return n;
}

void spawn(State* s) {
    switch(s->next) {
        case I: spawn_I(s->block); break;
        case O: spawn_O(s->block); break;
        case T: spawn_T(s->block); break;
        case Z: spawn_Z(s->block); break;
        case S: spawn_S(s->block); break;
        case J: spawn_J(s->block); break;
        case L: spawn_L(s->block); break;
    }
    s->block->x = SPAWN_X;
    s->block->y = 1;

    int n;

    if (spawn_space_available(s)) {
        s->can_hold = 1;
        s->next = choose_next(s->next);
        project_ghost(s);
    } else {
        s->mode = ENDGAME;
    }
}

int spawn_space_available(State* s) {
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        if (s->grid[x][y] != EMPTY) {
            return 0;
        }
    }
    return 1;
}

void spawn_I(Block* b) {
    copy_cells(I, b->cells);
    b->color = CYAN;
    b->type = I;
}

void spawn_O(Block* b) {
    copy_cells(O, b->cells);
    b->color = YELLOW;
    b->type = O;
}

void spawn_T(Block* b) {
    copy_cells(T, b->cells);
    b->color = PURPLE;
    b->type = T;
}

void spawn_Z(Block* b) {
    copy_cells(Z, b->cells);
    b->color = RED;
    b->type = Z;
}

void spawn_S(Block* b) {
    copy_cells(S, b->cells);
    b->color = GREEN;
    b->type = S;
}

void spawn_J(Block* b) {
    copy_cells(J, b->cells);
    b->color = BLUE;
    b->type = J;
}

void spawn_L(Block* b) {
    copy_cells(L, b->cells);
    b->color = WHITE;
    b->type = L;
}
