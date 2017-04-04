#include "block_factory.h"

void spawn(State* s) {
    switch(s->next) {
        case I: spawnI(s->block); break;
        case O: spawnO(s->block); break;
        case T: spawnT(s->block); break;
        case Z: spawnZ(s->block); break;
        case S: spawnS(s->block); break;
        case J: spawnJ(s->block); break;
        case L: spawnL(s->block); break;
    }
    s->block->x = SPAWN_X;
    s->block->y = 1;

    if (spawnSpaceAvailable(s)) {
        s->next = rand() % NUM_BLOCKS;
    } else {
        s->running = 0;
    }
}

/*
 * Make sure that all cells occupied by the block are empty.
 * Perform this check immediately after spawning a block so that blocks do not
 * spawn in eachother.
 */
int spawnSpaceAvailable(State* s) {
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        if (s->grid[x][y] != Empty) {
            return 0;
        }
    }
    return 1;
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
