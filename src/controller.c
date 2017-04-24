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

void wait_until_resume() {
    while (getch() != RESUME_KEY);
}

void run_mode(State* s, int* frame_counter) {
    (*frame_counter)++;
    // Collect desired total movement in this frame
    aggregate_movement(s, frame_counter);

    // Clear interactables such as the block and ghost
    clear_block(s);
    clear_ghost(s);

    // Perform movement
    if (!move_block(s)) {
        // Draw block before we reassign its pointer
        draw_block(s);

        // Perform row clear if needed and update score
        update_score(s);

        // Spawn a new block
        spawn(s);
    }

    // Draw block and ghost to grid
    draw_ghost(s);
    draw_block(s);

    // Rendering loop
    erase();
    render(s);
    refresh();

    // Assuming execution of loop takes negligible time
    usleep(US_DELAY);
}

void boss_mode(State* s) {
    erase();

    FILE *fp;
    char path[1035];

    // pipe command into a temp file stream
    fp = popen("/bin/ls -l /etc/", "r");
    if (fp == NULL) {
        // print default text if error happened
        render_default_boss_mode();
    } else {
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
            printw("%s", path);
        }

        pclose(fp);
    }

    wait_until_resume();

    s->mode = RUNNING;
}

void pause_mode(State* s) {
    mvprintw(MENU_ROW, MENU_COL, "*** PAUSED ***");
    wait_until_resume();

    s->mode = RUNNING;
}

int wait_until_option_selected(const char* title,
        const char** items,
        int num_items) {
    char user_input;
    int selection = 0;

    while (user_input != SELECT_KEY) {
        // Non-blocking user-input
        timeout(10);
        user_input = getch();

        // Navigate through the menu based on user-input
        switch (user_input) {
            case UP_KEY:
                decrement_with_min(&selection, 0);
                break;
            case DOWN_KEY:
                increment_with_max(&selection, num_items-1);
                break;
        }

        // Render the menu
        render_menu(title, items, num_items, selection);
    }

    return selection;
}

void endgame_mode(State* s) {
    const char* title = "*** GAME OVER ***";
    const char* items[] = { "new game", "quit" };
    const int num_items = 2;

    int selection = wait_until_option_selected(title, items, num_items);
    int level;

    switch (selection) {
        case 0: // new game
            setup_state(s);
            break;
        case 1: // quit
            s->mode = SHUTDOWN;
            break;
    }
}

void confirm_quit_mode(State* s) {
    const char* title = "*** QUIT? ***";
    const char* items[] = { "no", "yes" };
    const int num_items = 2;

    // Until the user presses the select key
    int selection = wait_until_option_selected(title, items, num_items);

    // Take action based on what the user selected from the menu
    switch (selection) {
        case 0: // no, do not quit
            s->mode = RUNNING;
            break;
        case 1: // yes, quit
            s->mode = SHUTDOWN;
            break;
    }
}

void shutdown_mode(State* s) {
    free(s->net_move);
    free(s->block);
    free(s);
    endwin();
    exit(0);
}

void act_on_user_input( char user_input,
    int* frame_counter,
    State* s) {
    Movement* m = s->net_move;

    switch(user_input) {
        case DROP_KEY:
            m->drop = 1;
            break;
        case DOWN_KEY:
            m->y = 1; // Move down by 1
            *frame_counter = 0; // Reset counter for default downwards move
            break;
        case LEFT_KEY:
            m->x--; // Move left by 1
            break;
        case RIGHT_KEY:
            m->x++; // Move right by 1
            break;
        case ROTATE_KEY: // rotate block clockwise
            m->r = 1;
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

int move_block(State* s) {
    // Flags
    Movement* m = s->net_move;
    int applied_move = 1;
    int can_move_vert = 1;

    if (m->drop) {
        s->block->y = s->block->ghosty;
        m->drop = 0;
        return 0;
    }

    // Keep attempty to apply moves until no moves can be applied
    while (applied_move) {
        applied_move = 0;

        // Try to move vertically
        if (m->y != 0) {
            can_move_vert = move_block_vertically(s);
            if (can_move_vert) {
                applied_move = 1;
            } 
        }

        // Try to move horizontally
        if (m->x != 0) {
            if (move_block_horizontally(s)) {
                applied_move = 1;
            }
        }

        // Try to rotate
        if (m->r) {
            if (rotate_block(s)) {
                applied_move = 1;
            }
        }
    }

    // Recalculate ghost position
    project_ghost(s);

    return can_move_vert;
}

void aggregate_movement(State* s, int* frame_counter) {
    // Initialize with zero movement
    Movement* m = s->net_move;
    m->x = 0;
    m->y = 0;
    m->r = 0;

    // Default downwards movement
    if (*frame_counter > s->speed) {
        m->y = 1;
        *frame_counter = 0;
    }

    // Get user input
    if (is_user_input()) {
        // The user has pressed a key, take appropriate action
        char user_input = getchar();
        act_on_user_input(user_input, frame_counter, s);
    }
}

void setup_state(State* s) {
    initialize_grid(s->grid);
    s->next = rand() % NUM_BLOCKS;
    s->mode = RUNNING;
    s->level = 0;
    s->speed = 48;
    s->block_count = 0;
    s->score = 0;
}

void begin_game() {
    State* s = malloc(sizeof(State));
    s->block = malloc(sizeof(Block));
    s->net_move = malloc(sizeof(Movement));
    setup_state(s);
    spawn(s);

    int frame_counter = 0;

    while (1) {
        switch (s->mode) {
            case RUNNING:
                run_mode(s, &frame_counter);
                break;
            case BOSS:
                boss_mode(s);
                break;
            case PAUSED:
                pause_mode(s);
                break;
            case CONFIRM_QUIT:
                confirm_quit_mode(s);
                break;
            case ENDGAME:
                endgame_mode(s);
                break;
            case SHUTDOWN:
                shutdown_mode(s);
                break;
        }
    }
}
