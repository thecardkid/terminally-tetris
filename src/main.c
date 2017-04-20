#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "utils.h"
#include "renderer.h"
#include "controller.h"

int main(int argc, char** argv) {
    // Seed random generator for block spawning
    srand(time(NULL));

    set_up_screen();
    begin_game();
}
