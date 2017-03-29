#ifndef SOFTSYS_BOMBASSTIC_BAMBOO_UTILS_H
#define SOFTSYS_BOMBASSTIC_BAMBOO_UTILS_H

/*
 * External constants to be used in other files
 */
extern const int GRID_W;
extern const int GRID_H;
extern const int OFFSET;
extern const int SPAWN_X;
extern const int NUM_BLOCKS;

extern const int IBlock[4][2];
extern const int OBlock[4][2];
extern const int TBlock[4][2];
extern const int ZBlock[4][2];
extern const int SBlock[4][2];
extern const int JBlock[4][2];
extern const int LBlock[4][2];

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
  Representation of generic Tetris block
*/
typedef struct {
    int cells[4][2];
    int x;
    int y;
    BlockColor color;
    BlockType type;
} Block;

#endif
