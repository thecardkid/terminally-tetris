#include "rotate.h"

void rotate_block(Block* b, const int rotation_matrix[2][2]){
    int rotated_cells[4][2], sum;

    for (int i = 0; i < 4; i++) {     //row of first matrix
        for (int j = 0; j < 2; j++) {   //column of second matrix
            sum = 0;
            for (int k = 0; k < 2; k++) {
                sum += (b->cells[i][k]) * rotation_matrix[k][j];
                rotated_cells[i][j]=sum;
            }
        }
    };

    // reassign block's cells to the rotated coordinates
    memcpy(b->cells, rotated_cells, sizeof(b->cells));
};

void rotate_right(Block* b){
    if (b->type == O) {
        return;
    }
    rotate_block(b, rotation_matrix_R);
};

void rotate_left(Block* b){
    if (b->type == O) {
        return;
    }
    rotate_block(b, rotation_matrix_L);
};
