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

    if (spawn_space_available(s)) {
        s->next = rand() % NUM_BLOCKS;
    } else {
        s->mode = SHUTDOWN;
    }
}

int spawn_space_available(State* s) {
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        if (s->grid[x][y] != Empty) {
            return 0;
        }
    }
    return 1;
}

void spawn_I(Block* b) {
    memcpy(b->cells, I_Block, sizeof(I_Block));
    b->color = Cyan;
    b->type = I;
}

void spawn_O(Block* b) {
    memcpy(b->cells, O_Block, sizeof(I_Block));
    b->color = Yellow;
    b->type = O;
}

void spawn_T(Block* b) {
    memcpy(b->cells, T_Block, sizeof(I_Block));
    b->color = Purple;
    b->type = T;
}

void spawn_Z(Block* b) {
    memcpy(b->cells, Z_Block, sizeof(I_Block));
    b->color = Red;
    b->type = Z;
}

void spawn_S(Block* b) {
    memcpy(b->cells, S_Block, sizeof(I_Block));
    b->color = Green;
    b->type = S;
}

void spawn_J(Block* b) {
    memcpy(b->cells, J_Block, sizeof(I_Block));
    b->color = Blue;
    b->type = J;
}

void spawn_L(Block* b) {
    memcpy(b->cells, L_Block, sizeof(I_Block));
    b->color = White;
    b->type = L;
}
