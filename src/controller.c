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

void act_on_user_input(char user_input, State* s,
    int* frame_counter) {

    int frames_until_next_move;
    switch(user_input) {
        case DOWN_KEY: // move block down
            frames_until_next_move = MOVE_RATE - (*frame_counter % MOVE_RATE);
            if (frames_until_next_move == 0) frames_until_next_move = MOVE_RATE;
            *frame_counter += frames_until_next_move;
            break;
        case LEFT_KEY: // move block left
            move_block(s, -1, 0);
            break;
        case RIGHT_KEY: // move block right
            move_block(s, 1, 0);
            break;
        case ROTATE_CW_KEY: // rotate block clockwise
            move_block(s, 0, 1);
            break;
        case ROTATE_CCW_KEY: // rotate block counter-clockwise
            move_block(s, 0, -1);
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

int move_block(State* s, int delta_x, int rotation) {
    // Clear cells occupied by the block
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        s->grid[x][y] = Empty;
    }

    // Check the cells that the shift would move the block into for emptyness
    int canMove = 1;

    if (hit_bottom_grid(s->block->y)) canMove = 0;

    // Check for collision with other blocks and sides of stage
    if (canMove) {

        // Check for block rotation
        switch(rotation){
          case 0: break;
          case -1: rotate_left(s->block);break; // rotate COUNTER-CLOCKWISE
          case 1: rotate_right(s->block);break; // rotate CLOCKWISE
        }

        // Resolve lateral movement before checking vertical movement
        for (int i = 0; i < 4; i++) {
            int x = s->block->cells[i][0] + s->block->x;
            int y = s->block->cells[i][1] + s->block->y;

            if (is_within_grid(x, delta_x)) delta_x = 0;
        }

        // Resolve vertical movement
        for (int i = 0; i < 4; i++) {
            int x = s->block->cells[i][0] + s->block->x;
            int y = s->block->cells[i][1] + s->block->y;

            // Check for collision with other blocks
            if (s->grid[x + delta_x][y + 1] != Empty) {
                canMove = 0;
                break;
            }
        }
    }

    // Update block position if no collisions
    if (canMove) {
        s->block->x += delta_x;
        s->block->y++;
    }

    // Set cells occupied by block to correct color
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        s->grid[x][y] = s->block->color;
    }

    return canMove;
}
void begin_game(State* s) {
    s->block = malloc(sizeof(Block));
    s->next = spawn(s->block, rand() % NUM_BLOCKS);

    int frameCounter = 0;
    char user_input;

    while (1) {
        frameCounter++;

        // Rendering loop
        clear();
        render(s);
        refresh();

        // Piece movement
        if (frameCounter >= MOVE_RATE) {
            if (!move_block(s, 0, 0)) {
                // Block has hit the bottom of stage or top of another block.
                // No longer meaningful to keep track of the
                // block. Spawn a new block

                update_score(s);
                s->next = spawn(s->block, s->next);
            }
            frameCounter = 0;
        }

        // Get user input
        if (is_user_input()) {
            // The user has pressed a key, take appropriate action
            user_input = getchar();
            act_on_user_input(user_input, s, &frameCounter);
        }

        // Assuming execution of loop takes negligible time
        usleep(US_DELAY);
    }
}
