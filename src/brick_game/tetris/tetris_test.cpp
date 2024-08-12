#include "tetris.h"

#include <gtest/gtest.h>

TEST(tetris, updateCurrentState) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  updateTetrisParams(&params);
  spawnNextFigure(&params);
  GameInfo_t dataCheck = updateCurrentState();

  EXPECT_EQ(params.data->field, dataCheck.field);
  EXPECT_EQ(params.data->next, dataCheck.next);
  EXPECT_EQ(params.data->high_score, dataCheck.high_score);
  EXPECT_EQ(params.data->score, dataCheck.score);
  EXPECT_EQ(params.data->level, dataCheck.level);
  EXPECT_EQ(params.data->pause, dataCheck.pause);
  EXPECT_EQ(params.data->speed, dataCheck.speed);
  removeParams(&params);
}

TEST(tetris, updateTetrisParams) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  GameParams_t *paramsCheck1 = updateTetrisParams(&params);
  GameParams_t *paramsCheck2 = updateTetrisParams(NULL);

  EXPECT_EQ(&params, paramsCheck1);
  EXPECT_EQ(&params, paramsCheck2);
  removeParams(&params);
}

TEST(tetris, initializeTetrisParams) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);

  EXPECT_EQ(params.data->score, 0);
  EXPECT_EQ(params.data->level, 1);
  EXPECT_EQ(params.data->speed, 1);
  EXPECT_EQ(params.data->pause, 0);
  EXPECT_GE(params.figure->typeNext, 0);
  EXPECT_LE(params.figure->typeNext, 6);
  EXPECT_EQ(params.state, START);
  EXPECT_EQ(params.isActive, true);
  removeParams(&params);
}

TEST(tetris, removeParams_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  removeParams(&params);

  EXPECT_EQ(nullptr, params.data->field);
  EXPECT_EQ(nullptr, params.data->next);
  EXPECT_EQ(params.state, GAMEOVER);
  EXPECT_EQ(params.isActive, false);
}

TEST(tetris, removeParams_2) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;
  params.data->field = NULL;
  params.data->next = NULL;

  removeParams(&params);

  EXPECT_EQ(nullptr, params.data->field);
  EXPECT_EQ(nullptr, params.data->next);
  EXPECT_EQ(params.state, GAMEOVER);
  EXPECT_EQ(params.isActive, false);
}

TEST(tetris, resetField) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  startGame(&params);

  EXPECT_EQ(params.data->score, 0);
  EXPECT_EQ(params.data->level, 1);
  EXPECT_EQ(params.data->speed, 1);
  EXPECT_EQ(params.state, GAME);
  EXPECT_EQ(params.isActive, true);
  removeParams(&params);
}

TEST(tetris, startGame) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.data->field[FIELD_HEIGHT / 2][FIELD_WIDTH / 2] = 1;
  resetField(&params);

  bool isFieldEqual = true;
  for (int row = 0; row < FIELD_HEIGHT && isFieldEqual; row++)
    for (int col = 0; col < FIELD_WIDTH && isFieldEqual; col++) {
      int checkValue = (row > 22 || col < 3 || col > 12) ? 1 : 0;
      isFieldEqual = params.data->field[row][col] == checkValue;
    }
  EXPECT_EQ(isFieldEqual, true);
  removeParams(&params);
}

TEST(tetris, generateRandomFigure) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->typeNext = generateRandomFigure(params.data->next);

  EXPECT_GE(params.figure->typeNext, 0);
  EXPECT_LE(params.figure->typeNext, 6);
  removeParams(&params);
}

TEST(tetris, spawnNextFigure) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->typeNext = 0;
  spawnNextFigure(&params);

  EXPECT_EQ(params.figure->type, 0);
  EXPECT_EQ(params.figure->y, 2);
  EXPECT_EQ(params.figure->x, FIELD_WIDTH / 2);
  EXPECT_EQ(params.figure->rotation, 0);
  removeParams(&params);
}

TEST(tetris, moveLeft_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveLeft(&params);

  EXPECT_NE(params.figure->x, previousX);
  removeParams(&params);
}

TEST(tetris, moveLeft_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  params.data->pause = 1;
  moveLeft(&params);

  EXPECT_EQ(params.figure->x, previousX);
  removeParams(&params);
}

TEST(tetris, moveLeft_3) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = 4;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveLeft(&params);

  EXPECT_EQ(params.figure->x, previousX);
  removeParams(&params);
}

TEST(tetris, moveRight_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveRight(&params);

  EXPECT_NE(params.figure->x, previousX);
  removeParams(&params);
}

TEST(tetris, moveRight_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  params.data->pause = 1;
  moveRight(&params);

  EXPECT_EQ(params.figure->x, previousX);
  removeParams(&params);
}

TEST(tetris, moveRight_3) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH - 6;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveRight(&params);

  EXPECT_EQ(params.figure->x, previousX);
  removeParams(&params);
}

TEST(tetris, rotate_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->rotation = 0;
  params.figure->type = 0;  // I figure
  int previousRotation = params.figure->rotation;
  rotate(&params);

  EXPECT_NE(params.figure->rotation, previousRotation);
  removeParams(&params);
}

TEST(tetris, rotate_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  int previousRotation = params.figure->rotation;
  params.data->pause = 1;
  rotate(&params);

  EXPECT_EQ(params.figure->rotation, previousRotation);
  removeParams(&params);
}

TEST(tetris, rotate_3) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH - 3;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  int previousRotation = params.figure->rotation;
  rotate(&params);

  EXPECT_EQ(params.figure->rotation, previousRotation);
  removeParams(&params);
}

TEST(tetris, moveDown_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousY = params.figure->y;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveDown(&params);

  bool isFieldEqual = true;
  isFieldEqual = params.data->field[params.figure->y][previousY] == 0;
  isFieldEqual = params.data->field[params.figure->y][previousY] == 0;
  isFieldEqual = params.data->field[params.figure->y][previousY] == 0;
  isFieldEqual = params.data->field[params.figure->y][previousY] == 0;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 - 1] == 1;
  isFieldEqual = params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 + 1] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 + 2] == 1;
  EXPECT_EQ(isFieldEqual, true);
  removeParams(&params);
}

TEST(tetris, moveDown_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  params.data->pause = 1;
  moveDown(&params);

  bool isFieldEqual = true;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT / 2][FIELD_HEIGHT / 2 - 1] == 1;
  isFieldEqual = params.data->field[FIELD_HEIGHT / 2][FIELD_HEIGHT / 2] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT / 2][FIELD_HEIGHT / 2 + 1] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT / 2][FIELD_HEIGHT / 2 + 2] == 1;
  EXPECT_EQ(isFieldEqual, true);
  removeParams(&params);
}

TEST(tetris, moveDown_3) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT - 4;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  int previousY = params.figure->y;
  moveDown(&params);

  bool isFieldEqual = true;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 - 1] == 1;
  isFieldEqual = params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 + 1] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 + 2] == 1;
  EXPECT_EQ(isFieldEqual, true);
  removeParams(&params);
}

TEST(tetris, shift_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousY = params.figure->y;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  shift(&params);

  EXPECT_NE(params.figure->y, previousY);
  removeParams(&params);
}

TEST(tetris, shift_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT - 4;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  int previousY = params.figure->y;
  shift(&params);

  bool isFieldEqual = true;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual = params.data->field[previousY][params.figure->x] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 - 1] == 1;
  isFieldEqual = params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 + 1] == 1;
  isFieldEqual =
      params.data->field[FIELD_HEIGHT - 4][FIELD_HEIGHT / 2 + 2] == 1;
  EXPECT_EQ(isFieldEqual, true);
  removeParams(&params);
}

TEST(tetris, attach_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++)
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
  attach(&params);

  EXPECT_EQ(params.data->score, 100);
  removeParams(&params);
}

TEST(tetris, attach_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
  }
  attach(&params);

  EXPECT_EQ(params.data->score, 300);
  removeParams(&params);
}

TEST(tetris, attach_3) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
    params.data->field[FIELD_HEIGHT - 6][col] = 1;
  }
  attach(&params);

  EXPECT_EQ(params.data->score, 700);
  removeParams(&params);
}

TEST(tetris, attach_4) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
    params.data->field[FIELD_HEIGHT - 6][col] = 1;
    params.data->field[FIELD_HEIGHT - 7][col] = 1;
  }
  attach(&params);

  EXPECT_EQ(params.data->score, 1500);
  removeParams(&params);
}

TEST(tetris, attach_5) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.data->score = 6000;
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
    params.data->field[FIELD_HEIGHT - 6][col] = 1;
    params.data->field[FIELD_HEIGHT - 7][col] = 1;
  }
  attach(&params);

  EXPECT_EQ(params.data->score, 7500);
  EXPECT_EQ(params.data->level, 10);
  removeParams(&params);
}

TEST(tetris, attach_6) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.data->field[3][FIELD_WIDTH / 2] = 1;
  attach(&params);

  EXPECT_EQ(params.state, GAMEOVER);
  removeParams(&params);
}

TEST(tetris, attach_7) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.data->score = params.data->high_score + 100;
  attach(&params);

  EXPECT_EQ(params.data->score, params.data->high_score);
  removeParams(&params);
}

TEST(tetris, addFigure) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  addFigure(&params);

  bool isFieldEqual = true;
  isFieldEqual = params.data->field[params.figure->y][params.figure->x - 1] ==
                 params.figure->type + 1;
  isFieldEqual = params.data->field[params.figure->y][params.figure->x] ==
                 params.figure->type + 1;
  isFieldEqual = params.data->field[params.figure->y][params.figure->x + 1] ==
                 params.figure->type + 1;
  isFieldEqual = params.data->field[params.figure->y][params.figure->x + 2] ==
                 params.figure->type + 1;
  EXPECT_EQ(isFieldEqual, true);
  removeParams(&params);
}

TEST(tetris, isFigureNotCollide_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  bool isNotCollide = isFigureNotCollide(&params);

  EXPECT_EQ(isNotCollide, true);
  removeParams(&params);
}

TEST(tetris, isFigureNotCollide_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT - 3;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  bool isNotCollide = isFigureNotCollide(&params);

  EXPECT_EQ(isNotCollide, false);
  removeParams(&params);
}

TEST(tetris, clearFigure) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  clearFigure(&params);

  bool isFieldEqual = true;
  isFieldEqual =
      params.data->field[params.figure->y][params.figure->x - 1] == 0;
  isFieldEqual = params.data->field[params.figure->y][params.figure->x] == 0;
  isFieldEqual =
      params.data->field[params.figure->y][params.figure->x + 1] == 0;
  isFieldEqual =
      params.data->field[params.figure->y][params.figure->x + 2] == 0;
  EXPECT_EQ(isFieldEqual, true);
  removeParams(&params);
}

TEST(tetris, allocate2DArray) {
  GameParams_t params;
  GameInfo_t data;
  data.field = NULL;
  data.next = NULL;
  params.data = &data;

  data.field = allocate2DArray(FIELD_HEIGHT, FIELD_WIDTH);

  EXPECT_NE(nullptr, params.data->field);
  removeParams(&params);
}

TEST(tetris, pause) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeTetrisParams(&params);
  pauseGame(&params);

  EXPECT_EQ(params.data->pause, 1);
  removeParams(&params);
}
