#include <ncurses.h>

int main() {
    WINDOW *w;
    char c;
    int row = 0;

    w = initscr();

    while (1) {
        timeout(3000);
        c = getch();
        mvprintw(row, 0, "received %c (%d)\n", c, (int) c);
        row++;
    }
    endwin();
}
