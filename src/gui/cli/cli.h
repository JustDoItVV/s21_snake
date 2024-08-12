#ifndef GUI_CLI_H
#define GUI_CLI_H

/************************************************************
 * @file cli.h
 * @brief CLI GUI header
 ************************************************************/
#define _XOPEN_SOURCE_EXTENDED

#include <locale.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#include "../../controller/controller.h"

#define FRAME_RATE 60  // fps
#define READ_DELAY 50  // milliseconds
#define FIELD_SIZE_X 10
#define FIELD_SIZE_Y 20
#define INFO_SIZE_X 10
#define INFO_SIZE_Y 20
#define GUI_SCALE 1
#define SPEED_RATE 0.5

/************************************************************
 * @brief GUI initialization
 *
 * Initialize ncurses cli window, ncurses settings, colors
 ************************************************************/
void initGui(void);

/************************************************************
 * @brief GUI destcrution
 *
 * Destroy ncurses window, closing application
 ************************************************************/
void destroyGui(void);

/************************************************************
 * @brief Game main loop
 *
 * Game main loop with drawing screens, processing user input.
 ************************************************************/
void gameLoop(void);

/************************************************************
 * @brief Get user action
 *
 * Get user action enum value depending on pressed button.
 ************************************************************/
UserAction_t getAction(int pressedKey);

/************************************************************
 * @brief Draw GUI
 *
 * Draw static part of GUI
 *
 * @param pressedKey Keyboard button char or int
 * @return UserACtion_t
 ************************************************************/
void drawGui(void);

/************************************************************
 * @brief Draw game field
 *
 * Draw colored game field.
 ************************************************************/
void drawField(int **field);

/************************************************************
 * @brief Draw info block
 *
 * Draw info block with game data, next figure colored preview.
 ************************************************************/
void drawInfo(GameParams_t *params);

/************************************************************
 * @brief Draw start screen
 *
 * Draw static start screen.
 ************************************************************/
void drawStartScreen(GameParams_t *params);

/************************************************************
 * @brief Draw gameover screen
 *
 * Draw static gameover screen.
 ************************************************************/
void drawGameoverScreen(GameParams_t *params);

#endif