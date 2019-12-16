#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "utils.h"
#include "renderer.h"
#include "controller.h"
#include "utils.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        if (strcmp(argv[1], "help") == 0) {
            printf("\n=== Terminally-Tetris' key bindings ===\n");
            printf("\nCONTROLS\n");
            printf("  down......arrow down\n");
            printf("  left......arrow left\n");
            printf("  right.....arrow right\n");
            printf("  drop......[Space Bar]\n");
            printf("  rotate....R(r) or A(a)\n");
            printf("  hold......H\n");
            printf("\nMODES\n");
            printf("  pause.....1\n");
            printf("  quit......2\n");
            printf("  resume....3\n");
            printf("  select....[Enter]\n\n");
        } else {
            printf("Did not recognize argument. See man page for help.\n");
        }
    }

    if (argc == 1) {
        // Seed random generator for block spawning
        srand(time(NULL));

        set_up_screen();
        begin_game();
    }

    return 0;
}
