#ifndef TETRIS_H
#define TETRIS_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
 * @file tetris.h
 * @brief Game logic library header
 ************************************************************/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

#define PI_2 1.57079632679489661923

#define FIELD_HEIGHT 26
#define FIELD_WIDTH 16
#define BORDER_SIZE 3
#define FIGURE_HEIGHT 2
#define FIGURE_WIDTH 4
#define PIXEL_EMPTY 0

#define STATES_COUNT 3
#define SIGNALS_COUNT 8
#define FIGURES_COUNT 7

#define DATAFILE_PATH "./data_tetris"

#define LEVEL_MIN 1
#define LEVEL_MAX 10
#define SPEED_MIN 1
#define SPEED_MAX 10
#define LEVEL_TRESHOLD 600

#define SCORE_ROWS_1 100
#define SCORE_ROWS_2 300
#define SCORE_ROWS_3 700
#define SCORE_ROWS_4 1500

#define ROTATION_MIN 0
#define ROTATION_MAX 3

/************************************************************
 * @brief States for fsm
 *
 * Game states, used as states (rows) for finite state
 * machine table
 ************************************************************/
typedef enum {
  START = 0,
  GAME,
  GAMEOVER,
} GameState_t;

/************************************************************
 * @brief Signals for fsm
 *
 * User input, used as signals (columnss) for finite state
 * machine table
 ************************************************************/
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
} UserAction_t;

/************************************************************
 * @brief Game data struct
 *
 * Game logic data
 *
 * @param field Game field with borders
 * @param next Next spafn figure for preview
 * @param score Game score
 * @param high_score Game high score from file
 * @param level Gamel level, max 10
 * @param speed Game speed, max 10
 * @param pause Pause flag
 ************************************************************/
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/************************************************************
 * @brief Figure data struct
 *
 * Current and next figure parameters
 *
 * @param typeNext Type of next figure
 * @param type Type of current figure
 * @param rotation Number of rotation to PI/2 angle: 0..3
 * @param x Field x coordinate of figure center
 * @param y Field y coordinate of figure center
 ************************************************************/
typedef struct {
  int typeNext;
  int type;
  int rotation;
  int x;
  int y;
} Figure_t;

typedef struct {
  bool showSecondaryField;
  const char *secondaryField;
  bool showLeftKey;
  const wchar_t *leftKey;
  bool showRightKey;
  const wchar_t *rightKey;
  bool showDownKey;
  const wchar_t *downKey;
  bool showActionKey;
  const wchar_t *actionKey;
} UI_messages_t;

/************************************************************
 * @brief Game parameters struct
 *
 * All game parameters with current field, figure, state
 *
 * @param data Game data with field
 * @param state Game current state
 * @param isActive Flag for activate game loop
 * @param figure Current figure data
 ************************************************************/
typedef struct {
  const char *gameName;
  GameInfo_t *data;
  GameState_t state;
  bool isActive;
  Figure_t *figure;
  UI_messages_t messages;
  int **gameField;
} GameParams_t;

/************************************************************
 * @brief User's input processing
 *
 * Activate function, assigned to game state and action
 * into finite state model table.
 *
 * @param action User's action
 * @param hold Parameter whether pressed key hol or not
 ************************************************************/
void userInput(UserAction_t action, bool hold);

/************************************************************
 * @brief Update current game state
 *
 * Update current game state by shifting figure one pixel down.
 ************************************************************/
GameInfo_t updateCurrentState(void);

typedef void (*funcPointer)(GameParams_t *params);

/************************************************************
 * @brief Update game parameters
 *
 * Update game parameters in static variable.
 *
 * @param params Pointer to GameParams_t struct
 * @return GameParams_t
 ************************************************************/
GameParams_t *updateTetrisParams(GameParams_t *params);

/************************************************************
 * @brief Initialize game parameters
 *
 * Initialize game parameters: allocate memory for
 * arrays, assign inital values to game data.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void initializeTetrisParams(GameParams_t *params);

/************************************************************
 * @brief Remove game parameters
 *
 * Clear allocated memory for arrays, assign null pointers.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void removeParams(GameParams_t *params);

/************************************************************
 * @brief Reset game field
 *
 * Reset game field to inital state.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void resetField(GameParams_t *params);

/************************************************************
 * @brief Start game
 *
 * Change game state to START, spawns next figure
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void startGame(GameParams_t *params);

/************************************************************
 * @brief Generate random figure
 *
 * Generate random number of figure
 *
 * @param params Pointer to the next array for preview
 * @return Figure type number in figures array
 ************************************************************/
int generateRandomFigure(int **next);

/************************************************************
 * @brief Spawn next figure
 *
 * Spawn next figure on field above the visible screen.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void spawnNextFigure(GameParams_t *params);

/************************************************************
 * @brief Move figure to the left
 *
 * Move figure one pixel left if possible.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void moveLeft(GameParams_t *params);

/************************************************************
 * @brief Move figure to the right
 *
 * Move figure one pixel right if possible.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void moveRight(GameParams_t *params);

/************************************************************
 * @brief Rotate figure clockwise
 *
 * Move figure clockwise to 90 degrees if possible.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void rotate(GameParams_t *params);

/************************************************************
 * @brief Move figure down to the end
 *
 * Move figure down whil possible.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void moveDown(GameParams_t *params);

/************************************************************
 * @brief Shift figure down
 *
 * Shift figure down one pixel if possible or active
 * attach function.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void shift(GameParams_t *params);

/************************************************************
 * @brief Attach
 *
 * Clear filled rows, update score, spawn next figure and
 * check if gameover.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void attach(GameParams_t *params);

/************************************************************
 * @brief Pause game
 *
 * Pause game.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void pauseGame(GameParams_t *params);

/************************************************************
 * @brief Add figure to the field
 *
 * Add figure to the field.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void addFigure(GameParams_t *params);

/************************************************************
 * @brief Check if figure collides
 *
 * Check if figure collides during moving, shiftig, rotating.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
bool isFigureNotCollide(GameParams_t *params);

/************************************************************
 * @brief Remove figure from field
 *
 * Remove figure from field.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
void clearFigure(GameParams_t *params);

/************************************************************
 * @brief Allocate memory for 2d array
 *
 * Dynamically allocate memory for 2d array.
 *
 * @param params Pointer to GameParams_t struct
 ************************************************************/
int **allocate2DArray(int nRows, int nCols);

#ifdef __cplusplus
}
#endif

#endif
