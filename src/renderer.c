#include "renderer.h"

int preview_cells[4][2];

void set_up_screen() {
    initscr();
    start_color();
    noecho();
    curs_set(false);

    // Set up color schemes for each block
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(PURPLE, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GHOST, COLOR_BLACK, COLOR_WHITE);
}

void display_grid(int grid[GRID_W][GRID_H]) {
    int i, j, block;

    for (int y = OFFSET; y < GRID_H; y++) {
        mvprintw(y-OFFSET, 0, "|");
        for (int x = 0; x < GRID_W; x++) {
            if ((block = grid[x][y]) != EMPTY) {
                attron(COLOR_PAIR(block));

                if (block == GHOST) {
                    printw(" ");
                } else {
                    printw("@");
                }

                attroff(COLOR_PAIR(block));
            } else {
                printw(" ");
            }
        }
        printw("|\n");
    }

    mvprintw(GRID_H-OFFSET, 0, "------------");
}

void display_endgame(State* s) {
    int row = 1;
    int col = 3;
    mvprintw(row++, col, "GAME OVER");
}

int display_controls(int row) {
    mvprintw(row++, MENU_COL, "CONTROLS:");
    mvprintw(row++, MENU_COL, "Down ---------------- %c", DOWN_KEY);
    mvprintw(row++, MENU_COL, "Left ---------------- %c", LEFT_KEY);
    mvprintw(row++, MENU_COL, "Right --------------- %c", RIGHT_KEY);
    mvprintw(row++, MENU_COL, "Rotate -- ----------- %c", ROTATE_KEY);
    mvprintw(row++, MENU_COL, "Pause --------------- %c", PAUSE_KEY);
    mvprintw(row++, MENU_COL, "Quit ---------------- %c", QUIT_KEY);
    mvprintw(row++, MENU_COL, "Boss Mode ----------- %c", BOSS_MODE_KEY);
    mvprintw(row++, MENU_COL, "Resume -------------- %c", RESUME_KEY);
    mvprintw(row++, MENU_COL, "Select -------------- %s", "ENTER");
    return row;
}

void display_preview(int row, BlockType next) {
    // must assign string of 4 spaces to index into
    // later on
    char preview[2][5] = {"    ", "    "};
    int x, y;

    copy_cells(next, preview_cells);
    mvprintw(row++, MENU_COL, "NEXT:");

    attron(COLOR_PAIR(next+1));

    for (int i=0; i<4; i++) {
        x = preview_cells[i][0];
        y = preview_cells[i][1];
        preview[y+1][x+1] = '@';
    }

    mvprintw(row++, MENU_COL, preview[0]);
    mvprintw(row++, MENU_COL, preview[1]);

    attroff(COLOR_PAIR(next+1));
}


void render_default_boss_mode() {
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

void render_menu(const char* title,
        const char** items,
        int num_items,
        int selection) {
    // Render the menu title
    mvprintw(MENU_ROW, MENU_COL, title);

    for (int i=0; i<num_items; i++) {
        // Highlight the currently selected menu item
        if (i == selection) {
            attron(A_STANDOUT);
        }

        // Render each menu item
        mvprintw(MENU_ROW+1+i, MENU_COL+2, items[i]);
        attroff(A_STANDOUT);
    }
}

void render(State* state) {
    int row = 1;

    display_grid(state->grid);
    row = display_controls(row);
    row++; // blank line
    mvprintw(row++, MENU_COL, "SCORE: %d", state->score);
    row++; // blank line

    if (state->level < 5) {
        display_preview(row, state->next);
    }
}

