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

void run_mode(State* s, int* frame_counter, WINDOW* game) {
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
    render(s, game);
    refresh();

    // Assuming execution of loop takes negligible time
    usleep(US_DELAY);
}

void pause_mode(State* s) {
    mvprintw(MENU_ROW, MENU_COL, "***** PAUSED *****");
    wait_until_resume();

    s->mode = RUNNING;
}

int wait_until_option_selected(const char* title, const char** items, int num_items) {
    char user_input;
    int selection = 0;

    while (user_input != SELECT_KEY) {
        // Non-blocking user-input
        timeout(10);
        user_input = getch();

        // Navigate through the menu based on user-input
        switch (user_input) {
            case UP_KEY_1:
                decrement_with_min(&selection, 0);
                break;
            case DOWN_KEY_1:
                increment_with_max(&selection, num_items-1);
                break;
        }

        // Render the menu
        render_menu(title, items, num_items, selection);
    }

    return selection;
}

void endgame_mode(State* s) {
    const char* title = "***** GAME OVER *****";
    const char* items[] = { "New Game", "Quit" };
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
    const char* title = "***** QUIT? *****";
    const char* items[] = { "NO", "YES" };
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
    State* s){


    Movement* m = s->net_move;

    switch(user_input) {
        case DROP_KEY_1:
            m->drop = 1;
            break;
        case DOWN_KEY_1:
            m->y = 1; // Move down by 1
            *frame_counter = 0; // Reset counter for default downwards move
            break;
        case LEFT_KEY_1:
            m->x--; // Move left by 1
            break;
        case RIGHT_KEY_1:
            m->x++; // Move right by 1
            break;
        case HOLD_KEY_1:
            decide_hold(s); // hold current tetronimo
            break;
        case ROTATE_KEY_1: // rotate block clockwise
            m->r = 1;
            break;
        case PAUSE_KEY: // pause the game
            s->mode = PAUSED;
            break;
        case QUIT_KEY: // confirm the user wants to quit
            s->mode = CONFIRM_QUIT;
            break;
    }
}

void decide_hold(State* s) {
    if (s->can_hold) {
        hold_piece(s);
        s->can_hold = 0;
    }
}

void hold_piece(State* s) {
    BlockType type;

    if (s->held_block != NONE) {
        type = s->held_block;
        s->next = type;
    }

    s->held_block = s->block->type;
    clear_block(s);
    clear_ghost(s);
    spawn(s);
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
    s->can_hold = 1;
    s->held_block = NONE;
}

// set Initial Screen
void setInitialScreen(){
    int start_x = 9;
    int start_y = 5;

    int i = 1;

    WINDOW* init = newwin(25,70,0,0);
    box(init,ACS_VLINE, ACS_HLINE);
    wrefresh(init);

    //T
    wattron(init, COLOR_PAIR(i));
    mvwprintw(init, start_y,start_x,"      ");
    mvwprintw(init, start_y+1,start_x+2,"  ");
    mvwprintw(init, start_y+2,start_x+2,"  ");
    mvwprintw(init, start_y+3,start_x+2,"  ");
    mvwprintw(init, start_y+4,start_x+2,"  ");
    wattroff(init, COLOR_PAIR(i));
    start_x+= 9; i++;

    //E
    wattron(init, COLOR_PAIR(i));
    mvwprintw(init, start_y,start_x,"      ");
    mvwprintw(init, start_y+1,start_x,"  ");
    mvwprintw(init, start_y+2,start_x,"      ");
    mvwprintw(init, start_y+3,start_x,"  ");
    mvwprintw(init, start_y+4,start_x,"      ");
    wattroff(init, COLOR_PAIR(i));
    start_x+=9; i++;

    //T
    wattron(init, COLOR_PAIR(i));
    mvwprintw(init, start_y,start_x,"      ");
    mvwprintw(init, start_y+1,start_x+2,"  ");
    mvwprintw(init, start_y+2,start_x+2,"  ");
    mvwprintw(init, start_y+3,start_x+2,"  ");
    mvwprintw(init, start_y+4,start_x+2,"  ");
    wattroff(init, COLOR_PAIR(i));
    start_x+= 9; i++;

    //R
    wattron(init, COLOR_PAIR(i));
    mvwprintw(init, start_y,start_x,"    ");
    mvwprintw(init, start_y+1,start_x,"  "); 
    mvwprintw(init, start_y+1,start_x+4, "  ");
    mvwprintw(init, start_y+2,start_x,"    ");
    mvwprintw(init, start_y+3,start_x,"  ");
    mvwprintw(init, start_y+3,start_x+4,"  ");
    mvwprintw(init, start_y+4,start_x,"  ");
    mvwprintw(init, start_y+4,start_x+4,"  ");
    wattroff(init, COLOR_PAIR(i));
    start_x+=9; i++;

    //I
    wattron(init, COLOR_PAIR(i));
    mvwprintw(init, start_y,start_x,"      ");
    mvwprintw(init, start_y+1,start_x+2,"  "); 
    mvwprintw(init, start_y+2,start_x+2,"  ");
    mvwprintw(init, start_y+3,start_x+2,"  ");
    mvwprintw(init, start_y+4,start_x,"      ");
    wattroff(init, COLOR_PAIR(i));
    start_x+=9; i++;

    //E
    wattron(init, COLOR_PAIR(i));
    mvwprintw(init, start_y,start_x,"      ");
    mvwprintw(init, start_y+1,start_x,"  ");
    mvwprintw(init, start_y+2,start_x,"      ");
    mvwprintw(init, start_y+3,start_x+4,"  ");
    mvwprintw(init, start_y+4,start_x,"      ");
    wattroff(init, COLOR_PAIR(i));

    //press Any key to start
    mvwprintw(init, 15, 24, "press Any key to start");

    //Team info
    //mvwprintw(init, 23, 56, "By.OSS Team 7");

    wrefresh(init);
    getchar();
    endwin();
}

// start game mode
void begin_game() {
    State* s = malloc(sizeof(State));
    s->block = malloc(sizeof(Block));
    s->net_move = malloc(sizeof(Movement));
    WINDOW* game = newwin(GRID_H+1, 2*GRID_W+2, 0, 0);
    wrefresh(game);
    setup_state(s);
    spawn(s);

    int frame_counter = 0;

    setInitialScreen();

    while (1) {
        switch (s->mode) {
            case RUNNING:
                run_mode(s, &frame_counter, game);
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
