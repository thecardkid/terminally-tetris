#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>

#include "utils.h"

void set_up_screen();
void render(State* state);
void display(int grid[GRID_W][GRID_H]);

#endif

