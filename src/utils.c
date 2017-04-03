#include "utils.h"

// Note that here the positive Y axis points "down"
const int IBlock[4][2] = {{0,0}, {2,0}, {-1,0}, {1,0}};
const int OBlock[4][2] = {{0,0}, {1,0}, {1,-1}, {0,-1}};
const int TBlock[4][2] = {{0,0}, {1,0}, {-1,0}, {0,-1}};
const int ZBlock[4][2] = {{0,0}, {1,0}, {0,-1}, {-1,-1}};
const int SBlock[4][2] = {{0,0}, {-1,0}, {0,-1}, {1,-1}};
const int JBlock[4][2] = {{0,0}, {1,0}, {-1,0}, {-1,-1}};
const int LBlock[4][2] = {{0,0}, {-1,0}, {1,0}, {1,-1}};
const int rotation_matrix_R[2][2] = {{0,-1}, {1,0}};
const int rotation_matrix_L[2][2] = {{0,1}, {-1,0}};
