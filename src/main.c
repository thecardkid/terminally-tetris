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
            printf("  up........%c\n", UP_KEY);
            printf("  down......%c\n", DOWN_KEY);
            printf("  left......%c\n", LEFT_KEY);
            printf("  right.....%c\n", RIGHT_KEY);
            printf("  hold......%c\n", HOLD_KEY);
            printf("  rotate....%c\n", ROTATE_KEY);
            printf("  drop......[space]\n");
            printf("\nMODES\n");
            printf("  boss......%c\n", BOSS_MODE_KEY);
            printf("  pause.....%c\n", PAUSE_KEY);
            printf("  quit......%c\n", QUIT_KEY);
            printf("  resume....%c\n", RESUME_KEY);
            printf("  select....[enter]\n\n");
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
