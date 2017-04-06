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
#define MENU_COL GRID_W+5

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
#define RESUME_KEY 'r'
#define SELECT_KEY '\n'

extern const int I_Block[4][2];
extern const int O_Block[4][2];
extern const int T_Block[4][2];
extern const int Z_Block[4][2];
extern const int S_Block[4][2];
extern const int J_Block[4][2];
extern const int L_Block[4][2];
extern const int rotation_matrix_R[2][2];
extern const int rotation_matrix_L[2][2];

/*
 * Checks whether coordinate is inside playable area
 */
int in_grid(int x, int y);

/*
 * Taken from https://i.stack.imgur.com/JLRFu.png
 *
 * Not defined as enum class to allow implicit casting to int
 */
typedef enum {EMPTY, CYAN, BLUE, WHITE, YELLOW, GREEN, PURPLE, RED} BlockColor;

/*
 * Taken from http://tetris.wikia.com/wiki/Tetromino
 */
typedef enum {I, J, L, O, S, T, Z} BlockType;

/*
 * Define rotation parameter
 */
typedef enum {LEFT, NO_ROTATE, RIGHT} Rotation;

/*
 * Modes that the game can be in
 */
typedef enum {RUNNING, PAUSED, CONFIRM_QUIT, SHUTDOWN, BOSS} Gamemode;

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
    Gamemode mode; // 1: Game in progress 0: Game over
    int speed; // speed at which blocks move down without user input
    Block* block;
    BlockType next;
} State;

/*
 * Container for aggregating net movement in a frame.
 */
typedef struct {
    int x;
    int y;
    Rotation r;
} Movement;

#endif
