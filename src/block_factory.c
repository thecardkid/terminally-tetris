#include "block_factory.h"

void spawn(BlockType t, int grid[GRID_H][GRID_W]) {
    switch(t) {
        case I: return spawnI(grid);
        case O: return spawnO(grid);
        case T: return spawnT(grid);
        case Z: return spawnZ(grid);
        case S: return spawnS(grid);
        case J: return spawnJ(grid);
        case L: return spawnL(grid);
        default: return;
    }
}

void spawnI(int grid[GRID_H][GRID_W]) {
    grid[0][5] = Cyan;
    grid[1][5] = Cyan;
    grid[2][5] = Cyan;
    grid[3][5] = Cyan;
}

void spawnO(int grid[GRID_H][GRID_W]) {
    grid[2][4] = Yellow;
    grid[2][5] = Yellow;
    grid[3][4] = Yellow;
    grid[3][5] = Yellow;
}

void spawnT(int grid[GRID_H][GRID_W]) {
    grid[2][4] = Purple;
    grid[3][3] = Purple;
    grid[3][4] = Purple;
    grid[3][5] = Purple;
}

void spawnZ(int grid[GRID_H][GRID_W]) {
    grid[2][4] = Red;
    grid[2][5] = Red;
    grid[3][5] = Red;
    grid[3][6] = Red;
}

void spawnS(int grid[GRID_H][GRID_W]) {
    grid[2][5] = Green;
    grid[2][4] = Green;
    grid[3][4] = Green;
    grid[3][3] = Green;
}

void spawnJ(int grid[GRID_H][GRID_W]) {
    grid[2][3] = Blue;
    grid[3][3] = Blue;
    grid[3][4] = Blue;
    grid[3][5] = Blue;
}

void spawnL(int grid[GRID_H][GRID_W]) {
    grid[2][5] = White;
    grid[3][5] = White;
    grid[3][4] = White;
    grid[3][3] = White;
}
