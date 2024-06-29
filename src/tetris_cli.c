/************************************************************
 * @mainpage
 * @author lucamorv
 * @version 1.0
 * @file tetris_cli.c
 * @brief Entry point
 ************************************************************/

#include "gui/cli/cli.h"

int main() {
  srand(time(NULL));
  initGui();
  gameLoop();
  destroyGui();
  return 0;
}
