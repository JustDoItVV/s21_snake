#include "../../tests/tetris_cli_test.h"

// userInput

// updateCurrentState
START_TEST(tc_ok_1) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  updateParams(&params);
  spawnNextFigure(&params);
  GameInfo_t dataCheck = updateCurrentState();

  ck_assert_ptr_eq(params.data->field, dataCheck.field);
  ck_assert_ptr_eq(params.data->next, dataCheck.next);
  ck_assert_int_eq(params.data->high_score, dataCheck.high_score);
  ck_assert_int_eq(params.data->score, dataCheck.score);
  ck_assert_int_eq(params.data->level, dataCheck.level);
  ck_assert_int_eq(params.data->pause, dataCheck.pause);
  ck_assert_int_eq(params.data->speed, dataCheck.speed);
  removeParams(&params);
}
END_TEST

// updateParams
START_TEST(tc_ok_2) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  GameParams_t *paramsCheck1 = updateParams(&params);
  GameParams_t *paramsCheck2 = updateParams(NULL);

  ck_assert_ptr_eq(&params, paramsCheck1);
  ck_assert_ptr_eq(&params, paramsCheck2);
  removeParams(&params);
}
END_TEST

// initializeParams
START_TEST(tc_ok_3) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);

  ck_assert_int_eq(params.data->score, 0);
  ck_assert_int_eq(params.data->level, 1);
  ck_assert_int_eq(params.data->speed, 1);
  ck_assert_int_eq(params.data->pause, 0);
  ck_assert_int_ge(params.figure->typeNext, 0);
  ck_assert_int_le(params.figure->typeNext, 6);
  ck_assert_int_eq(params.state, START);
  ck_assert_int_eq(params.isActive, true);
  removeParams(&params);
}
END_TEST

// removeParams
START_TEST(tc_ok_4) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  removeParams(&params);

  ck_assert_ptr_null(params.data->field);
  ck_assert_ptr_null(params.data->next);
  ck_assert_int_eq(params.state, GAMEOVER);
  ck_assert_int_eq(params.isActive, false);
}
END_TEST

START_TEST(tc_ok_5) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;
  params.data->field = NULL;
  params.data->next = NULL;

  removeParams(&params);

  ck_assert_ptr_null(params.data->field);
  ck_assert_ptr_null(params.data->next);
  ck_assert_int_eq(params.state, GAMEOVER);
  ck_assert_int_eq(params.isActive, false);
}
END_TEST

// resetField
START_TEST(tc_ok_6) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  startGame(&params);

  ck_assert_int_eq(params.data->score, 0);
  ck_assert_int_eq(params.data->level, 1);
  ck_assert_int_eq(params.data->speed, 1);
  ck_assert_int_eq(params.state, GAME);
  ck_assert_int_eq(params.isActive, true);
  removeParams(&params);
}
END_TEST

// startGame
START_TEST(tc_ok_7) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.data->field[FIELD_HEIGHT / 2][FIELD_WIDTH / 2] = 1;
  resetField(&params);

  bool isFieldEqual = true;
  for (int row = 0; row < FIELD_HEIGHT && isFieldEqual; row++)
    for (int col = 0; col < FIELD_WIDTH && isFieldEqual; col++) {
      int checkValue = (row > 22 || col < 3 || col > 12) ? 1 : 0;
      isFieldEqual = params.data->field[row][col] == checkValue;
    }
  ck_assert_int_eq(isFieldEqual, true);
  removeParams(&params);
}
END_TEST

// generateRandomFigure
START_TEST(tc_ok_8) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->typeNext = generateRandomFigure(params.data->next);

  ck_assert_int_ge(params.figure->typeNext, 0);
  ck_assert_int_le(params.figure->typeNext, 6);
  removeParams(&params);
}
END_TEST

// spawnNextFigure
START_TEST(tc_ok_9) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->typeNext = 0;
  spawnNextFigure(&params);

  ck_assert_int_eq(params.figure->type, 0);
  ck_assert_int_eq(params.figure->y, 2);
  ck_assert_int_eq(params.figure->x, FIELD_WIDTH / 2);
  ck_assert_int_eq(params.figure->rotation, 0);
  removeParams(&params);
}
END_TEST

// moveLeft
START_TEST(tc_ok_10) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveLeft(&params);

  ck_assert_int_ne(params.figure->x, previousX);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_11) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  params.data->pause = 1;
  moveLeft(&params);

  ck_assert_int_eq(params.figure->x, previousX);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_12) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = 4;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveLeft(&params);

  ck_assert_int_eq(params.figure->x, previousX);
  removeParams(&params);
}
END_TEST

// moveRight
START_TEST(tc_ok_13) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveRight(&params);

  ck_assert_int_ne(params.figure->x, previousX);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_14) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  params.data->pause = 1;
  moveRight(&params);

  ck_assert_int_eq(params.figure->x, previousX);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_15) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH - 6;
  int previousX = params.figure->x;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  moveRight(&params);

  ck_assert_int_eq(params.figure->x, previousX);
  removeParams(&params);
}
END_TEST

// rotate
START_TEST(tc_ok_16) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->rotation = 0;
  params.figure->type = 0;  // I figure
  int previousRotation = params.figure->rotation;
  rotate(&params);

  ck_assert_int_ne(params.figure->rotation, previousRotation);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_17) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  int previousRotation = params.figure->rotation;
  params.data->pause = 1;
  rotate(&params);

  ck_assert_int_eq(params.figure->rotation, previousRotation);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_18) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH - 3;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  int previousRotation = params.figure->rotation;
  rotate(&params);

  ck_assert_int_eq(params.figure->rotation, previousRotation);
  removeParams(&params);
}
END_TEST

// moveDown
START_TEST(tc_ok_19) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
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
  ck_assert_int_eq(isFieldEqual, true);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_20) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
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
  ck_assert_int_eq(isFieldEqual, true);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_21) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
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
  ck_assert_int_eq(isFieldEqual, true);
  removeParams(&params);
}
END_TEST

// shift
START_TEST(tc_ok_22) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousY = params.figure->y;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  shift(&params);

  ck_assert_int_ne(params.figure->y, previousY);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_23) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
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
  ck_assert_int_eq(isFieldEqual, true);
  removeParams(&params);
}
END_TEST

// attach
START_TEST(tc_ok_24) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++)
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
  attach(&params);

  ck_assert_int_eq(params.data->score, 100);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_25) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
  }
  attach(&params);

  ck_assert_int_eq(params.data->score, 300);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_26) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
    params.data->field[FIELD_HEIGHT - 6][col] = 1;
  }
  attach(&params);

  ck_assert_int_eq(params.data->score, 700);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_27) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
    params.data->field[FIELD_HEIGHT - 6][col] = 1;
    params.data->field[FIELD_HEIGHT - 7][col] = 1;
  }
  attach(&params);

  ck_assert_int_eq(params.data->score, 1500);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_28) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.data->score = 6000;
  for (int col = 0; col < FIELD_WIDTH; col++) {
    params.data->field[FIELD_HEIGHT - 4][col] = 1;
    params.data->field[FIELD_HEIGHT - 5][col] = 1;
    params.data->field[FIELD_HEIGHT - 6][col] = 1;
    params.data->field[FIELD_HEIGHT - 7][col] = 1;
  }
  attach(&params);

  ck_assert_int_eq(params.data->score, 7500);
  ck_assert_int_eq(params.data->level, 10);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_29) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.data->field[3][FIELD_WIDTH / 2] = 1;
  attach(&params);

  ck_assert_int_eq(params.state, GAMEOVER);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_30) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.data->score = params.data->high_score + 100;
  attach(&params);

  ck_assert_int_eq(params.data->score, params.data->high_score);
  removeParams(&params);
}
END_TEST

// addFigure
START_TEST(tc_ok_31) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
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
  ck_assert_int_eq(isFieldEqual, true);
  removeParams(&params);
}
END_TEST

// isFigureNotCollide
START_TEST(tc_ok_32) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  bool isNotCollide = isFigureNotCollide(&params);

  ck_assert_int_eq(isNotCollide, true);
  removeParams(&params);
}
END_TEST

START_TEST(tc_ok_33) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  params.figure->y = FIELD_HEIGHT - 3;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->type = 0;  // I figure
  params.figure->rotation = 0;
  bool isNotCollide = isFigureNotCollide(&params);

  ck_assert_int_eq(isNotCollide, false);
  removeParams(&params);
}
END_TEST

// clearFigure
START_TEST(tc_ok_34) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
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
  ck_assert_int_eq(isFieldEqual, true);
  removeParams(&params);
}
END_TEST

// allocate2DArray
START_TEST(tc_ok_35) {
  GameParams_t params;
  GameInfo_t data;
  data.field = NULL;
  data.next = NULL;
  params.data = &data;

  data.field = allocate2DArray(FIELD_HEIGHT, FIELD_WIDTH);

  ck_assert_ptr_nonnull(params.data->field);
  removeParams(&params);
}
END_TEST

// Pause
START_TEST(tc_ok_36) {
  GameParams_t params;
  GameInfo_t data;
  Figure_t figure;
  params.data = &data;
  params.figure = &figure;

  initializeParams(&params);
  pauseGame(&params);

  ck_assert_int_eq(params.data->pause, 1);
  removeParams(&params);
}
END_TEST

Suite *tetris_suite() {
  Suite *s = suite_create("tetris");
  TCase *tcases_ok;

  tcases_ok = tcase_create("tetris_ok");
  tcase_add_test(tcases_ok, tc_ok_1);
  tcase_add_test(tcases_ok, tc_ok_2);
  tcase_add_test(tcases_ok, tc_ok_3);
  tcase_add_test(tcases_ok, tc_ok_4);
  tcase_add_test(tcases_ok, tc_ok_5);
  tcase_add_test(tcases_ok, tc_ok_6);
  tcase_add_test(tcases_ok, tc_ok_7);
  tcase_add_test(tcases_ok, tc_ok_8);
  tcase_add_test(tcases_ok, tc_ok_9);
  tcase_add_test(tcases_ok, tc_ok_10);
  tcase_add_test(tcases_ok, tc_ok_11);
  tcase_add_test(tcases_ok, tc_ok_12);
  tcase_add_test(tcases_ok, tc_ok_13);
  tcase_add_test(tcases_ok, tc_ok_14);
  tcase_add_test(tcases_ok, tc_ok_15);
  tcase_add_test(tcases_ok, tc_ok_16);
  tcase_add_test(tcases_ok, tc_ok_17);
  tcase_add_test(tcases_ok, tc_ok_18);
  tcase_add_test(tcases_ok, tc_ok_19);
  tcase_add_test(tcases_ok, tc_ok_20);
  tcase_add_test(tcases_ok, tc_ok_21);
  tcase_add_test(tcases_ok, tc_ok_22);
  tcase_add_test(tcases_ok, tc_ok_23);
  tcase_add_test(tcases_ok, tc_ok_24);
  tcase_add_test(tcases_ok, tc_ok_25);
  tcase_add_test(tcases_ok, tc_ok_26);
  tcase_add_test(tcases_ok, tc_ok_27);
  tcase_add_test(tcases_ok, tc_ok_28);
  tcase_add_test(tcases_ok, tc_ok_29);
  tcase_add_test(tcases_ok, tc_ok_30);
  tcase_add_test(tcases_ok, tc_ok_31);
  tcase_add_test(tcases_ok, tc_ok_32);
  tcase_add_test(tcases_ok, tc_ok_33);
  tcase_add_test(tcases_ok, tc_ok_34);
  tcase_add_test(tcases_ok, tc_ok_35);
  tcase_add_test(tcases_ok, tc_ok_36);

  suite_add_tcase(s, tcases_ok);

  return s;
}