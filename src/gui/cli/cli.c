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
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;
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
      drawStartScreen(params.data);
    else if (params.state == GAME) {
      drawGui();
      drawInfo(params.data);
      drawField(params.data->field);
    } else if (params.state == GAMEOVER)
      drawGameoverScreen(params.data);

    if (params.data->pause)
      mvprintw(1 + FIELD_SIZE_Y / 2, FIELD_SIZE_X - 1, "PAUSE");

    pressedKey = getch();
    action = getAction(pressedKey);
    if (action != Up) {
      userInput(action, hold);
    }
  }
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
  for (int row = 0; row < FIELD_SIZE_Y; row++)
    for (int col = 0; col < FIELD_SIZE_X; col++)
      if (field[row + 3][col + 3]) {
        attron(COLOR_PAIR(field[row + 3][col + 3]));
        mvaddch(1 + row, 1 + col * 2, ACS_CKBOARD);
        mvaddch(1 + row, 1 + col * 2 + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(field[row + 3][col + 3]));
      }
  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}

void drawInfo(GameInfo_t *data) {
  mvprintw(2, FIELD_SIZE_X * 2 + 3, "HIGH SCORE: %d", data->high_score);
  mvprintw(4, FIELD_SIZE_X * 2 + 3, "SCORE: %d", data->score);
  mvprintw(6, FIELD_SIZE_X * 2 + 3, "LEVEL: %d", data->level);
  mvprintw(8, FIELD_SIZE_X * 2 + 3, "SPEED: %d", data->speed);
  mvprintw(10, FIELD_SIZE_X * 2 + 3, "NEXT");
  for (int row = 0; row < FIGURE_HEIGHT; row++)
    for (int col = 0; col < FIGURE_WIDTH; col++) {
      if (data->next[row][col]) {
        attron(COLOR_PAIR(data->next[row][col]));
        mvaddch(11 + row, FIELD_SIZE_X * 2 + 6 * 2 + col * 2, ACS_CKBOARD);
        mvaddch(11 + row, FIELD_SIZE_X * 2 + 6 * 2 + col * 2 + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(data->next[row][col]));
      }
    }

  mvprintw(15, FIELD_SIZE_X * 2 + 3, "SPACE - Pause game");
  mvaddwstr(16, FIELD_SIZE_X * 2 + 5, L"←   - Move left");
  mvaddwstr(17, FIELD_SIZE_X * 2 + 5, L"→   - Move right");
  mvaddwstr(18, FIELD_SIZE_X * 2 + 5, L"↓   - Move down");
  mvaddwstr(19, FIELD_SIZE_X * 2 + 5, L"R   - Rotate");
  mvaddwstr(20, FIELD_SIZE_X * 2 + 4, L"ESC  - Exit game");
  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}

void drawStartScreen(GameInfo_t *data) {
  drawGui();
  drawInfo(data);

  mvprintw(1 + FIELD_SIZE_Y / 2, 1, "Press ENTER to start");

  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}

void drawGameoverScreen(GameInfo_t *data) {
  drawGui();
  drawInfo(data);
  drawField(data->field);

  mvprintw(FIELD_SIZE_Y / 2, 7, "GAMEOVER");
  mvprintw(FIELD_SIZE_Y / 2 + 1, 5, "Press  ENTER");
  mvprintw(FIELD_SIZE_Y / 2 + 2, 4, "to start again");

  move(FIELD_SIZE_Y + 1, FIELD_SIZE_X * 2 + INFO_SIZE_X * 2 + 3);
}
