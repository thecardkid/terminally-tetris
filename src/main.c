#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "utils.h"
#include "renderer.h"
#include "controller.h"

int main(int argc, char** argv) {
    // Seed random generator for block spawning
    srand(time(NULL));

    State* state = malloc(sizeof(State));
    initialize_grid(state->grid);
    state->score = 0;
    state->level = 1; // TODO @hnguyen accept command line arg here
    set_up_screen();
    begin_game(state);
}
