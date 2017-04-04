#ifndef UTILS_H
#define UTILS_H

/*
 * External constants to be used in other files
 */
#define GRID_W 10
#define GRID_H 22
#define OFFSET 2
#define SPAWN_X 4
#define NUM_BLOCKS 7

/*
 * Controls
 */
#define UP_KEY 'k'
#define DOWN_KEY 'j'
#define LEFT_KEY 'h'
#define RIGHT_KEY 'l'
#define ROTATE_CW_KEY 'f'
#define ROTATE_CCW_KEY 'd'
#define PAUSE_KEY 'p'
#define QUIT_KEY 'q'
#define BOSS_MODE_KEY 'b'

extern const int IBlock[4][2];
extern const int OBlock[4][2];
extern const int TBlock[4][2];
extern const int ZBlock[4][2];
extern const int SBlock[4][2];
extern const int JBlock[4][2];
extern const int LBlock[4][2];
extern const int rotation_matrix_R[2][2];
extern const int rotation_matrix_L[2][2];

/*
 * Taken from https://i.stack.imgur.com/JLRFu.png
 *
 * Not defined as enum class to allow implicit casting to int
 */
typedef enum {Empty, Cyan, Blue, White, Yellow, Green, Purple, Red} BlockColor;

/*
 * Taken from http://tetris.wikia.com/wiki/Tetromino
 */
typedef enum {I, O, T, Z, S, J, L} BlockType;

/*
 * Define rotation parameter
 */
typedef enum {LEFT, NO_ROTATE, RIGHT} Rotation;

/*
  Representation of generic Tetris block
*/
typedef struct {
    int cells[4][2];
    int x;
    int y;
    BlockColor color;
    BlockType type;
} Block;

typedef struct {
   int grid[GRID_W][GRID_H];
   int score;
   int level;
   int running; // 1: Game in progress 0: Game over
   Block* block;
   BlockType next;
} State;

#endif
