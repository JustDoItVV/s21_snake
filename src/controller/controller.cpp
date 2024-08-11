#include "controller.h"

void initializeParams(GameParams_t *params) {
#ifdef TETRIS
  initializeTetrisParams(params);
#elif defined(SNAKE)
  initializeSnakeParams(params);
#else
  initializeSnakeParams(params);
#endif
}

void updateParams(GameParams_t *params) {
#ifdef TETRIS
  updateTetrisParams(params);
#elif defined(SNAKE)
  updateSnakeParams(params);
#else
  updateSnakeParams(params);
#endif
}
