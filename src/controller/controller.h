#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef TETRIS
#include "../brick_game/tetris/tetris.h"
#elif defined(SNAKE)
#include "../brick_game/snake/snake.h"
#else
#include "../brick_game/tetris/tetris.h"
#endif

void initializeParams(GameParams_t *params);
void updateParams(GameParams_t *params);

#endif