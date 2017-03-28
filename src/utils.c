#include "utils.h"

const int GRID_W = 10;
const int GRID_H = 24;

// Encoding of cells occupied by an O block
// Note that here the positive Y axis points "down"
const int OBlock[4][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
const int TBlock[4][2] = {{0, 1}, {-1, 1}, {1, 1}, {0, 0}};
