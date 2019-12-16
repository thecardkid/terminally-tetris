#include "renderer.h"

int preview_cells[4][2];

void set_up_screen() {
    initscr();
    start_color();
    noecho();
    curs_set(false);

    use_default_colors();
    // Set up color schemes for each block
    init_pair(CYAN, -1, COLOR_CYAN);
    init_pair(BLUE, -1, COLOR_BLUE);
    init_pair(WHITE, -1, COLOR_WHITE);
    init_pair(YELLOW, -1, COLOR_YELLOW);
    init_pair(GREEN, -1, COLOR_GREEN);
    init_pair(PURPLE, -1, COLOR_MAGENTA);
    init_pair(RED, -1, COLOR_RED);
    init_pair(GHOST, COLOR_WHITE, -1);
}

void display_grid(WINDOW* game, int grid[GRID_W][GRID_H]) {
    int i, j, block;

    for (int y = 1; y < GRID_H; y++) {
        for (int x = 0; x < GRID_W; x++) {
            if ((block = grid[x][y]) != EMPTY) {
                wattron(game, COLOR_PAIR(block));

                if (block == GHOST) {
                    mvwprintw(game, y, 2*x+1, "[]");
                } else {
                    mvwprintw(game, y, 2*x+1, "  ");
                }

                wattroff(game, COLOR_PAIR(block));
            } else {
                mvwprintw(game, y, 2*x+1, "  ");
            }
        }
    }

    box(game, ACS_VLINE, ACS_HLINE);
    wrefresh(game);
}

int display_controls(int row) {
    mvprintw(row++, MENU_COL, "CONTROLS:");
    mvprintw(row++, MENU_COL, "Down ---------------- arrow down");
    mvprintw(row++, MENU_COL, "Left ---------------- arrow left");
    mvprintw(row++, MENU_COL, "Right --------------- arrow right");
    mvprintw(row++, MENU_COL, "Drop ---------------- [space bar]");
    mvprintw(row++, MENU_COL, "Rotate -------------- R(r) or A(a)");
    mvprintw(row++, MENU_COL, "Hold ---------------- H");

    mvprintw(row++, MENU_COL, "---------------------------");
    mvprintw(row++, MENU_COL, "---------------------------");
    mvprintw(row++, MENU_COL, "Pause --------------- 1");
    mvprintw(row++, MENU_COL, "Resume -------------- 2");
    mvprintw(row++, MENU_COL, "Quit ---------------- 3");
    mvprintw(row++, MENU_COL, "Select -------------- [Enter]");
    return row;
}

void display_preview(int row, BlockType next) {
    // must assign string of 4 spaces to index into
    // later on

    copy_cells(next, preview_cells);
    mvprintw(row, MENU_COL+1, "NEXT:");
    display_block(row + 2, MENU_COL, next);
}

void display_hold(int row, BlockType t) {
    copy_cells(t, preview_cells);
    display_block(row, MENU_COL+10, t);
}

void display_block(int row, int col, BlockType type) {
    // must assign string of 4 spaces to index into
    // later on
    char preview[2][5] = {"    ", "    "};
    int x, y;

    for (int i=0; i<4; i++) {
        x = preview_cells[i][0];
        y = preview_cells[i][1];
        preview[y+1][x+1] = '@';
    }

    for (int i=0; i<5; i++) {
        if (preview[0][i] == '@') {
            attron(COLOR_PAIR(type+1));
        }
        mvprintw(row, col+2*i, "  ");
        attroff(COLOR_PAIR(type+1));
        if (preview[1][i] == '@') {
            attron(COLOR_PAIR(type+1));
        }
        mvprintw(row+1, col+2*i, "  ");
        attroff(COLOR_PAIR(type+1));
    }
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
        mvprintw(MENU_ROW+1+i, MENU_COL+7, items[i]);
        attroff(A_STANDOUT);
    }
}

void render(State* state, WINDOW* game) {
    int row = 1;

    refresh();
    display_grid(game, state->grid);
    row = display_controls(row);
    row++; // blank line
    mvprintw(row++, MENU_COL, "SCORE: %d", state->score);
    mvprintw(row++, MENU_COL, "LEVEL: %d", state->level);
    row++; // blank line

    mvprintw(row, MENU_COL+10, " HOLD:");
    if (state->held_block != NONE) {
        display_hold(row+2, state->held_block);
    }

    if (state->level < 5) {
        display_preview(row, state->next);
    } else {
        mvprintw(row++, MENU_COL, "NO PREVIEW");
        mvprintw(row++, MENU_COL, "AT LEVELS");
        mvprintw(row++, MENU_COL, "5 OR ABOVE");
    }
}
