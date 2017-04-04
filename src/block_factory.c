#include "block_factory.h"

BlockType spawn(Block* b, BlockType t) {
    switch(t) {
        case I: spawn_I(b); break;
        case O: spawn_O(b); break;
        case T: spawn_T(b); break;
        case Z: spawn_Z(b); break;
        case S: spawn_S(b); break;
        case J: spawn_J(b); break;
        case L: spawn_L(b); break;
    }
    b->x = SPAWN_X;
    b->y = 1;

    int r = rand() % NUM_BLOCKS;
    return r;
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
