#include "block_factory.h"

BlockType spawn(Block* b, BlockType t) {
    switch(t) {
        case I: spawnI(b); break;
        case O: spawnO(b); break;
        case T: spawnT(b); break;
        case Z: spawnZ(b); break;
        case S: spawnS(b); break;
        case J: spawnJ(b); break;
        case L: spawnL(b); break;
    }
    b->x = SPAWN_X;
    b->y = 1;

    int r = rand() % NUM_BLOCKS;
    return r;
}

void spawnI(Block* b) {
    memcpy(b->cells, IBlock, sizeof(IBlock));
    b->color = Cyan;
    b->type = I;
}

void spawnO(Block* b) {
    memcpy(b->cells, OBlock, sizeof(IBlock));
    b->color = Yellow;
    b->type = O;
}

void spawnT(Block* b) {
    memcpy(b->cells, TBlock, sizeof(IBlock));
    b->color = Purple;
    b->type = T;
}

void spawnZ(Block* b) {
    memcpy(b->cells, ZBlock, sizeof(IBlock));
    b->color = Red;
    b->type = Z;
}

void spawnS(Block* b) {
    memcpy(b->cells, SBlock, sizeof(IBlock));
    b->color = Green;
    b->type = S;
}

void spawnJ(Block* b) {
    memcpy(b->cells, JBlock, sizeof(IBlock));
    b->color = Blue;
    b->type = J;
}

void spawnL(Block* b) {
    memcpy(b->cells, LBlock, sizeof(IBlock));
    b->color = White;
    b->type = L;
}
