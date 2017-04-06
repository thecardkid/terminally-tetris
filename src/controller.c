#include "controller.h"

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

void run_mode(Movement* net_move, State* s, int* frame_counter) {
    (*frame_counter)++;
    // Collect desired total movement in this frame
    aggregate_movement(net_move, s, frame_counter);

    // Perform movement
    if (!move_block(s, net_move)) {
        // Block was unable to make any valid downwards move.

        // Perform row clear if needed and update score
        update_score(s);

        // Spawn a new block
        spawn(s);
    }

    // Rendering loop
    clear();
    render(s);
    refresh();

    // Assuming execution of loop takes negligible time
    usleep(US_DELAY);
}

void default_boss_mode() {
    printw(
        "user@workstation-312:~/Developer/project $ gem install heroku --no-redoc --no-ri\n"
        "ERROR:  While executing gem ... (Errno::EACCES)\n"
        "    Permission denied - /Users/user/.gem/ruby/1.9.1/cache/heroku-1.9.13.gem\n"
        "\n"
        "user@workstation-312:~/Developer/project $ sudo !!\n"
        "sudo gem install heroku --no-redoc --no-ri\n"
        "Successfully installed heroku-1.9.13\n"
        "1 gem installed\n"
        "\n"
        "user@workstation-312:~/Developer/project $ ls -l\n"
        "total 528\n"
        "drwxr-xr-x    2 user users   4096 Jun  9 17:05 .\n"
        "drwxr-xr-x    4 user users   4096 Jun 10 09:52 ..\n"
        "-rw-r--r--@   1 user users  88583 Jun  9 14:13 .babelrc\n"
        "-rw-r--r--    1 user users  65357 Jun  9 15:40 .git/\n"
        "-rw-r--r--    1 user users   4469 Jun  9 16:17 .gitignore\n"
        "-rw-r--r--    1 user users    455 Jun  9 16:17 index.js\n"
        "-rw-r--r--    1 user users   2516 Jun  9 16:17 node_modules/\n"
        "-rw-r--r--    1 user users    183 Jun  9 16:17 package.json\n"
        "-rw-r--r--    1 user users 349607 Jun  9 16:17 public/\n"
        "-rw-r--r--    1 user users      0 Jun  9 16:17 src/\n"
        "-rw-r--r--    1 user users   9284 Jun  9 17:05 webpack.config.js\n"
        "-rw-r--r--    1 user users    229 Jun  9 16:17 tetris.save\n"
        "\n"
        "user@workstation-312:~/Developer/project $ "
    );
}

void boss_mode() {
    clear();

    FILE *fp;
    char path[1035];

    // pipe command into a temp file stream
    fp = popen("/bin/ls -l /etc/", "r");
    if (fp == NULL) {
        // print default text if error happened
        default_boss_mode();
    } else {
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
            printw("%s", path);
        }

        pclose(fp);
    }

    // wait until game resumed
    while (getch() != RESUME_KEY);
    clear();
}

void pause_mode(State* s) {
    mvprintw(20, GRID_W+5, "*** PAUSED ***");

    // wait until game resumed
    while (getch() != RESUME_KEY);
    s->mode = RUNNING;
}

void confirm_quit_mode(State* s) {
    const char* menu_title = "*** QUIT? ***";
    const char* menu_items[] = { "yes", "no" };
    const int num_menu_items = 2;
    int curr_selection = 0;

    // Until the user presses the select key
    char user_input;
    while (user_input != SELECT_KEY) {
        // Non-blocking user-input
        timeout(10);
        user_input = getch();

        // Navigate through the menu based on user-input
        switch (user_input) {
            case UP_KEY:
                decrement_with_min(&curr_selection, 0);
                break;
            case DOWN_KEY:
                increment_with_max(&curr_selection, num_menu_items-1);
                break;
        }

        // Render the menu
        render_menu(menu_title, menu_items, num_menu_items, curr_selection,
                GRID_W+5, 20);
    }

    // Take action based on what the user selected from the menu
    switch (curr_selection) {
        case 0: // yes, quit
            s->mode = SHUTDOWN;
            break;
        case 1: // no, do not quit
            s->mode = RUNNING;
            break;
    }
}

void shutdown_mode() {
    endwin();
    exit(0);
}

void act_on_user_input(
    char user_input,
    Movement* m,
    int* frame_counter,
    State* s) {

    int frames_until_next_move;
    switch(user_input) {
        case DOWN_KEY:
            m->y = 1; // Move down by 1
            *frame_counter = 0; // Reset counter for default downwards move
            break;
        case LEFT_KEY:
            m->x += -1; // Move left by 1
            break;
        case RIGHT_KEY:
            m->x += 1; // Move right by 1
            break;
        case ROTATE_CW_KEY: // rotate block clockwise
            if (m->r == NO_ROTATE) {
                m->r = RIGHT;
            }
            if (m->r == LEFT) {
                m->r = NO_ROTATE;
            }
            break;
        case ROTATE_CCW_KEY: // rotate block counter-clockwise
            if (m->r == NO_ROTATE) {
                m->r = LEFT;
            }
            if (m->r == RIGHT) {
                m->r = NO_ROTATE;
            }
            break;
        case PAUSE_KEY: // pause the game
            s->mode = PAUSED;
            break;
        case QUIT_KEY: // confirm the user wants to quit
            s->mode = CONFIRM_QUIT;
            break;
        case BOSS_MODE_KEY: // set the game to boss mode
            s->mode = BOSS;
            break;
    }
}

int move_block(State* s, Movement* m) {
    // Clear cells occupied by the block
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        s->grid[x][y] = EMPTY;
    }

    // Flags
    int applied_move = 1;
    int can_move_vert = 1;
    int can_move_horiz = 1;
    int can_rotate = 1;

    // Keep attempty to apply moves until no moves can be applied
    while (applied_move) {
        applied_move = 0;

        // Try to move vertically
        if (m->y != 0) {
            can_move_vert = 1;
            for (int i = 0; i < 4; i++) {
                int x = s->block->cells[i][0] + s->block->x;
                int y = s->block->cells[i][1] + s->block->y;

                // Conditions where move is invalid
                if (!in_grid(x, y + m->y) || s->grid[x][y + m->y] != EMPTY) {
                    can_move_vert = 0;
                    break;
                }
            }
            if (can_move_vert) {
                s->block->y += m->y;
                m->y = 0; // signal that we have performed this operation
                applied_move = 1; // signal that A operation was performed
            }
        }

        // Try to move horizontally
        if (m->x != 0) {
            can_move_horiz = 1;
            for (int i = 0; i < 4; i++) {
                int x = s->block->cells[i][0] + s->block->x;
                int y = s->block->cells[i][1] + s->block->y;

                // Conditions where move is invalid
                if (!in_grid(x + m->x, y) || s->grid[x + m->x][y] != EMPTY) {
                    can_move_horiz = 0;
                    break;
                }
            }
            if (can_move_horiz) {
                s->block->x += m->x;
                m->x = 0;
                applied_move = 1;
            }
        }

        // Try to rotate
        if (m->r != NO_ROTATE) {
            can_rotate = 1;
            switch (m->r) {
                case LEFT: rotate_left(s->block); break;
                case RIGHT: rotate_right(s->block); break;
                default: break;
            }

            for (int i = 0; i < 4; i++) {
                int x = s->block->cells[i][0] + s->block->x;
                int y = s->block->cells[i][1] + s->block->y;

                // Conditions where move is invalid
                if (!in_grid(x, y) || s->grid[x][y] != EMPTY) {
                    can_rotate = 0;
                    break;
                }
            }

            if (!can_rotate) {
                // Undo rotation
                switch (m->r) {
                    case LEFT: rotate_right(s->block); break;
                    case RIGHT: rotate_left(s->block); break;
                    default: break;
                }
            } else {
                m->r = NO_ROTATE;
                applied_move = 1;
            }
        }
    }

    // Set cells occupied by block to correct color
    for (int i = 0; i < 4; i++) {
        int x = s->block->cells[i][0] + s->block->x;
        int y = s->block->cells[i][1] + s->block->y;

        s->grid[x][y] = s->block->color;
    }

    return can_move_vert;
}

void aggregate_movement(Movement* m, State* s, int* frame_counter) {
    // Initialize with zero movement
    m->x = 0;
    m->y = 0;
    m->r = NO_ROTATE;

    // Default downwards movement
    if (*frame_counter > s->speed) {
        m->y = 1;
        *frame_counter = 0;
    }

    // Get user input
    if (is_user_input()) {
        // The user has pressed a key, take appropriate action
        char user_input = getchar();
        act_on_user_input(user_input, m, frame_counter, s);
    }
}

void begin_game(State* s) {
    s->block = malloc(sizeof(Block));
    s->next = rand() % NUM_BLOCKS;
    s->mode = RUNNING;
    s->speed = 48;
    spawn(s);

    int frame_counter = 0;
    Movement* net_move = malloc(sizeof(Movement));

    while (1) {
        switch (s->mode) {
            case RUNNING:
                run_mode(net_move, s, &frame_counter);
                break;
            case BOSS:
                boss_mode();
                break;
            case PAUSED:
                pause_mode(s);
                break;
            case CONFIRM_QUIT:
                confirm_quit_mode(s);
                break;
            case SHUTDOWN:
                shutdown_mode();
                break;
        }
    }

}
