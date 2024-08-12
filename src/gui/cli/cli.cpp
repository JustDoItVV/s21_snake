/************************************************************
 * @file cli.c
 * @brief CLI GUI source
 ************************************************************/

#include "cli.h"

void initGui(void) {
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_CYAN);
  init_pair(2, COLOR_BLUE, COLOR_BLUE);
  init_pair(3, COLOR_RED, COLOR_YELLOW);
  init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);
  init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(7, COLOR_RED, COLOR_RED);
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, true);
  timeout(READ_DELAY);
}

void destroyGui(void) {
  printw("\nThe Game is ended. Closing application...\n");
  refresh();
  sleep(1);
  clear();
  refresh();
  endwin();
}

void gameLoop(void) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;
  UserAction_t action;
  int pressedKey;
  double counter = 0.;
  bool hold = false;

  initializeParams(&params);
  updateParams(&params);

  while (params.isActive) {
    if (counter >= 1.50 - params.data->speed * SPEED_RATE) {
      if (params.state == GAME && !params.data->pause) {
        updateCurrentState();
      }
      counter = 0.;
    }

    counter = counter + READ_DELAY * 1E-3;

    if (params.state == START)
      drawStartScreen(&params);
    else if (params.state == GAME) {
      drawGui();
      drawInfo(&params);
      drawField(params.data->field);
    } else if (params.state == GAMEOVER)
      drawGameoverScreen(&params);

    if (params.data->pause)
      mvprintw(1 + FIELD_SIZE_Y / 2, FIELD_SIZE_X - 1, "PAUSE");

    pressedKey = getch();
    action = getAction(pressedKey);
    if (action != Up) {
      userInput(action, hold);
    }
  }

#ifdef SNAKE
  delete params.game;
#endif
}

UserAction_t getAction(int pressedKey) {
  UserAction_t action = Up;

  if (pressedKey == 10)
    action = Start;
  else if (pressedKey == ' ')
    action = Pause;
  else if (pressedKey == 27)
    action = Terminate;
  else if (pressedKey == KEY_LEFT)
    action = Left;
  else if (pressedKey == KEY_RIGHT)
    action = Right;
  else if (pressedKey == KEY_DOWN)
    action = Down;
  else if (pressedKey == 'r')
    action = Action;

  return action;
}

void drawGui(void) {
  clear();

  mvhline(0, 0, ACS_HLINE, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 2);
  mvhline(FIELD_SIZE_Y + 1, 0, ACS_HLINE,
          FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 2);
  mvhline(FIELD_SIZE_Y - 6, FIELD_SIZE_X * 2 + 2, ACS_HLINE, INFO_SIZE_X * 2);
  mvvline(1, 0, ACS_VLINE, FIELD_SIZE_Y);
  mvvline(1, FIELD_SIZE_X * 2 + 1, ACS_VLINE, FIELD_SIZE_Y);
  mvvline(1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 2, ACS_VLINE, FIELD_SIZE_Y);

  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 2, ACS_URCORNER);
  mvaddch(FIELD_SIZE_Y + 1, 0, ACS_LLCORNER);
  mvaddch(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 2,
          ACS_LRCORNER);
  mvaddch(0, FIELD_SIZE_X * 2 + 1, ACS_TTEE);
  mvaddch(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + 1, ACS_BTEE);

  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}

void drawField(int **field) {
  for (int row = BORDER_SIZE; row < FIELD_SIZE_Y + BORDER_SIZE; row++)
    for (int col = BORDER_SIZE; col < FIELD_SIZE_X + BORDER_SIZE; col++)
      if (field[row][col]) {
        attron(COLOR_PAIR(field[row][col]));
        mvaddch(1 + (row - BORDER_SIZE), 1 + (col - BORDER_SIZE) * 2,
                ACS_CKBOARD);
        mvaddch(1 + (row - BORDER_SIZE), 1 + (col - BORDER_SIZE) * 2 + 1,
                ACS_CKBOARD);
        attroff(COLOR_PAIR(field[row][col]));
      }
  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}

void drawInfo(GameParams_t *params) {
  mvprintw(2, FIELD_SIZE_X * 2 + 3, "HIGH SCORE: %d", params->data->high_score);
  mvprintw(4, FIELD_SIZE_X * 2 + 3, "SCORE: %d", params->data->score);
  mvprintw(6, FIELD_SIZE_X * 2 + 3, "LEVEL: %d", params->data->level);
  mvprintw(8, FIELD_SIZE_X * 2 + 3, "SPEED: %d", params->data->speed);

  if (params->data->next) {
    if (params->messages.showSecondaryField) {
      mvprintw(10, FIELD_SIZE_X * 2 + 3, params->messages.secondaryField);
    }
    for (int row = 0; row < FIGURE_HEIGHT; row++)
      for (int col = 0; col < FIGURE_WIDTH; col++) {
        if (params->data->next[row][col]) {
          attron(COLOR_PAIR(params->data->next[row][col]));
          mvaddch(11 + row, FIELD_SIZE_X * 2 + 6 * 2 + col * 2, ACS_CKBOARD);
          mvaddch(11 + row, FIELD_SIZE_X * 2 + 6 * 2 + col * 2 + 1,
                  ACS_CKBOARD);
          attroff(COLOR_PAIR(params->data->next[row][col]));
        }
      }
  }

  int hintsCoordY = 15;
  mvprintw(hintsCoordY, FIELD_SIZE_X * 2 + 3, "SPACE - Pause game");
  hintsCoordY++;
  if (params->messages.showLeftKey) {
    mvaddwstr(hintsCoordY, FIELD_SIZE_X * 2 + 5, params->messages.leftKey);
    hintsCoordY++;
  }
  if (params->messages.showRightKey) {
    mvaddwstr(hintsCoordY, FIELD_SIZE_X * 2 + 5, params->messages.rightKey);
    hintsCoordY++;
  }
  if (params->messages.showDownKey) {
    mvaddwstr(hintsCoordY, FIELD_SIZE_X * 2 + 5, params->messages.downKey);
    hintsCoordY++;
  }
  if (params->messages.showActionKey) {
    mvaddwstr(hintsCoordY, FIELD_SIZE_X * 2 + 5, params->messages.actionKey);
    hintsCoordY++;
  }
  mvaddwstr(hintsCoordY, FIELD_SIZE_X * 2 + 4, L"ESC  - Exit game");
  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}

void drawStartScreen(GameParams_t *params) {
  drawGui();
  drawInfo(params);

  mvprintw(1 + FIELD_SIZE_Y / 2, 1, "Press ENTER to start");

  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}

void drawGameoverScreen(GameParams_t *params) {
  drawGui();
  drawInfo(params);
  drawField(params->data->field);

  mvprintw(FIELD_SIZE_Y / 2, 7, "GAMEOVER");
  mvprintw(FIELD_SIZE_Y / 2 + 1, 5, "Press  ENTER");
  mvprintw(FIELD_SIZE_Y / 2 + 2, 4, "to start again");

  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}
