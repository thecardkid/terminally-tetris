#include "controller.h"

/*
 * Modify stdin, check for valid user input, and revert stdin to original state.
 *
 * termios - http://man7.org/linux/man-pages/man3/tcsetattr.3.html
 * fcntl - http://man7.org/linux/man-pages/man2/fcntl.2.html
*/
int is_user_input() {
    struct termios old_term, new_term;
    int old_fd;
    int user_input;

    // Modify stdin with saved copies of original state
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO); // Enable canonical mode, echo input
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    old_fd = fcntl(STDIN_FILENO, F_GETFL, 0); // Copy stdin fd
    fcntl(STDIN_FILENO, F_SETFL, old_fd | O_NONBLOCK); // Non-blocking

    // Grab user input
    user_input = getchar();

    // Revert stdin to original state
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    fcntl(STDIN_FILENO, F_SETFL, old_fd);

    // If user input is valid
    if(user_input != EOF) {
        // Push user input back to stdin to be read again later
        ungetc(user_input, stdin);
        return 1;
    }

    return 0;
}

void act_on_user_input(char user_input, int grid[GRID_W][GRID_H],
    int* frame_counter, Block *block) {
    
    int frames_until_next_move;
    switch(user_input) {
        case DOWN_KEY: // move block down
            frames_until_next_move = MOVE_RATE - (*frame_counter % MOVE_RATE);
            if (frames_until_next_move == 0) frames_until_next_move = MOVE_RATE;
            *frame_counter += frames_until_next_move;
            break;
        case LEFT_KEY: // move block left
            move_block(grid, block, -1);
            break;
        case RIGHT_KEY: // move block right
            move_block(grid, block, 1);
            break;
        case ROTATE_CW_KEY: // rotate block clockwise
            // TODO: @skelly rotate block clockwise
            break;
        case ROTATE_CCW_KEY: // rotate block counter-clockwise
            // TODO: @skelly rotate block counter-clockwise
            break;
        case PAUSE_KEY: // pause the game
            // TODO: @skelly pause the game
            break;
        case QUIT_KEY: // quit the game
            // TODO: @skelly quit the game
            break;
        case BOSS_MODE_KEY: // set the game to boss mode
            // TODO: @skelly set the game to boss mode
            break;
    }
}

int hit_bottom_grid(int y) {
    if (y >= GRID_H - 1) return 1;
    return 0;
}

int is_within_grid(int x, int delta_x) {
    if (x + delta_x < 0 || x + delta_x > GRID_W - 1) return 1;
    return 0;
}

int move_block(int grid[GRID_W][GRID_H], Block *block, int delta_x) {
    // Clear cells occupied by the block
    for (int i = 0; i < 4; i++) {
        int x = block->cells[i][0] + block->x;
        int y = block->cells[i][1] + block->y;

        grid[x][y] = Empty;
    }

    // Check the cells that the shift would move the block into for emptyness
    int canMove = 1;

    if (hit_bottom_grid(block->y)) canMove = 0;

    // Check for collision with other blocks and sides of stage
    if (canMove) {
        for (int i = 0; i < 4; i++) {
            int x = block->cells[i][0] + block->x;
            int y = block->cells[i][1] + block->y;

            if (is_within_grid(block->x, delta_x)) delta_x = 0;

            // Check for collision with other blocks
            if (grid[x + delta_x][y + 1] != Empty) {
                canMove = 0;
                break;
            }
        }
    }

    // Update block position if no collisions
    if (canMove) {
        block->x += delta_x;
        block->y++;
    }

    // Set cells occupied by block to correct color
    for (int i = 0; i < 4; i++) {
        int x = block->cells[i][0] + block->x;
        int y = block->cells[i][1] + block->y;

        grid[x][y] = block->color;
    }

    return canMove;
}

void begin_game(int grid[GRID_W][GRID_H]) {
    Block *block = malloc(sizeof(Block));
    BlockType next = spawn(block, rand() % NUM_BLOCKS);

    int frameCounter = 0;
    char user_input;

    while (1) {
        frameCounter++;

        // Rendering loop
        clear();
        render(grid);
        refresh();

        // Piece movement
        if (frameCounter >= MOVE_RATE) {
            if (!move_block(grid, block, 0)) {
                // Block has hit the bottom of stage or top of another block. 
                // No longer meaningful to keep track of the 
                // block --> Spawn a new block
                next = spawn(block, next);
            }
            frameCounter = 0;
        }

        // Get user input 
        if (is_user_input()) {
            // The user has pressed a key, take appropriate action
            user_input = getchar();
            act_on_user_input(user_input, grid, &frameCounter, block);
        }

        // Assuming execution of loop takes negligible time
        usleep(US_DELAY);

    }
}
