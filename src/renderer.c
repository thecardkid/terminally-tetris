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
}

void display_grid(int grid[GRID_W][GRID_H]) {
    int i, j, block;

    for (int y = OFFSET; y < GRID_H; y++) {
        mvprintw(y-OFFSET, 0, "|");
        for (int x = 0; x < GRID_W; x++) {
            if ((block = grid[x][y]) != EMPTY) {
                attron(COLOR_PAIR(block));
                printw("@");
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
    mvprintw(row++, GRID_W+5, "CONTROLS:");
    mvprintw(row++, GRID_W+5, "Up ------------------ %c", UP_KEY);
    mvprintw(row++, GRID_W+5, "Down ---------------- %c", DOWN_KEY);
    mvprintw(row++, GRID_W+5, "Left ---------------- %c", LEFT_KEY);
    mvprintw(row++, GRID_W+5, "Right --------------- %c", RIGHT_KEY);
    mvprintw(row++, GRID_W+5, "Clockwise ----------- %c", ROTATE_CW_KEY);
    mvprintw(row++, GRID_W+5, "Counter-Clockwise --- %c", ROTATE_CCW_KEY);
    mvprintw(row++, GRID_W+5, "Pause --------------- %c", PAUSE_KEY);
    mvprintw(row++, GRID_W+5, "Quit ---------------- %c", QUIT_KEY);
    mvprintw(row++, GRID_W+5, "Boss Mode ----------- %c", BOSS_MODE_KEY);
    mvprintw(row++, GRID_W+5, "Resume -------------- %c", RESUME_KEY);
    return row;
}

void display_preview(int row, BlockType next) {
    // must assign string of 4 spaces to index into
    // later on
    char preview[2][5] = {"    ", "    "};
    int x, y;

    copy_cells(next, preview_cells);
    mvprintw(row++, GRID_W+5, "NEXT:");

    attron(COLOR_PAIR(next+1));

    for (int i=0; i<4; i++) {
        x = preview_cells[i][0];
        y = preview_cells[i][1];
        preview[y+1][x+1] = '@';
    }

    mvprintw(row++, GRID_W+5, preview[0]);
    mvprintw(row++, GRID_W+5, preview[1]);

    attroff(COLOR_PAIR(next+1));
}

void render(State* state) {
    int row = 1;

    display_grid(state->grid);
    row = display_controls(row);
    row++; // blank line
    mvprintw(row++, GRID_W+5, "SCORE: %d", state->score);
    row++; // blank line

    if (state->level < 5) {
        display_preview(row, state->next);
    }
}

