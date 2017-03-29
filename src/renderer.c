#include "renderer.h"

void set_up_screen() {
    initscr();
    start_color();
    noecho();
    curs_set(false);

    // Set up color schemes for each block
    init_pair(Cyan, COLOR_CYAN, COLOR_BLACK);
    init_pair(Blue, COLOR_BLUE, COLOR_BLACK);
    init_pair(White, COLOR_WHITE, COLOR_BLACK);
    init_pair(Yellow, COLOR_YELLOW, COLOR_BLACK);
    init_pair(Green, COLOR_GREEN, COLOR_BLACK);
    init_pair(Purple, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(Red, COLOR_RED, COLOR_BLACK);
}

void render(int grid[GRID_W][GRID_H]) {
    int i, j, block;

    for (int y = OFFSET; y < GRID_H; y++) {
        mvprintw(y-OFFSET, 0, "|");
        for (int x = 0; x < GRID_W; x++) {
            if ((block = grid[x][y]) != Empty) {
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
