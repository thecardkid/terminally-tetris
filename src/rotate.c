#include "rotate.h"

void rotate_block(Block* b, const int rotation_matrix[2][2]){
    /* Rotates block 90 degrees
    using matrix multiplication with rotation matrix.*/
    int matC[4][2]={0};
    int i,j,k,z,r=4,c=2;

    for(i=0;i<r;i++){     //row of first matrix
      for(j=0;j<c;j++){   //column of second matrix
      int sum=0;
        for(k=0;k<c;k++) {
          sum=sum+(b->cells[i][k])*rotation_matrix[k][j];
          matC[i][j]=sum;
    }}};

    // reassign block's cells to the rotated coordinates
    memcpy(b->cells, matC, sizeof(b->cells));
};

void rotate_right(Block* b){
  /* Rotates block 90 degrees CLOCKWISE.
  Checks block type for exception rotation cases. */
  switch(b->type) {
    case O: break; // O Block rotated is itself
    default: rotate_block(b, rotation_matrix_R); break;
  }
};

void rotate_left(Block* b){
  /* Rotates block 90 degrees COUNTER-CLOCKWISE.
  Checks block type for exception rotation cases. */
  switch(b->type) {
    case O: break; // O Block rotated is itself
    default: rotate_block(b, rotation_matrix_L); break;

  }
};
