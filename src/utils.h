#ifndef SOFTSYS_BOMBASSTIC_BAMBOO_UTILS_H
#define SOFTSYS_BOMBASSTIC_BAMBOO_UTILS_H

/*
 * External constants to be used in other files
 */
extern const int GRID_W;
extern const int GRID_H;
extern const int OFFSET;

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

#endif
