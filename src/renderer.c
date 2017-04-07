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

int display_controls(int row) {
    mvprintw(row++, MENU_COL, "CONTROLS:");
    mvprintw(row++, MENU_COL, "Up ------------------ %c", UP_KEY);
    mvprintw(row++, MENU_COL, "Down ---------------- %c", DOWN_KEY);
    mvprintw(row++, MENU_COL, "Left ---------------- %c", LEFT_KEY);
    mvprintw(row++, MENU_COL, "Right --------------- %c", RIGHT_KEY);
    mvprintw(row++, MENU_COL, "Clockwise ----------- %c", ROTATE_CW_KEY);
    mvprintw(row++, MENU_COL, "Counter-Clockwise --- %c", ROTATE_CCW_KEY);
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

void render_menu(const char* title, const char* items[], int num_items,
        int curr_selection, int row, int col) {
    // Render the menu title
    mvprintw(col, row, title);

    for (int i=0; i<num_items; i++) {
        // Highlight the currently selected menu item
        if (i == curr_selection) {
            attron(A_STANDOUT);
        }

        // Render each menu item
        mvprintw(col+1+i, row+2, items[i]);
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

