#ifndef SNAKE_H
#define SNAKE_H

#include <wchar.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

#define STATES_COUNT 3
#define SIGNALS_COUNT 8

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10
#define FIGURE_HEIGHT 2
#define FIGURE_WIDTH 4
#define BORDER_SIZE 0

#define DATAFILE_PATH "./data_snake"

#define LEVEL_MIN 1
#define LEVEL_MAX 10
#define SPEED_MIN 5
#define SPEED_MAX 9

#define SNAKE_COLOR 5
#define FOOD_COLOR 7

namespace s21 {
class GameSnake;
class Snake;
class SnakeItem;
}  // namespace s21

typedef enum {
  START = 0,
  GAME,
  GAMEOVER,
} GameState_t;

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

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

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

typedef struct {
  GameInfo_t *data;
  GameState_t state;
  s21::GameSnake *game;
  bool isActive;
  UI_messages_t messages;
} GameParams_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);

void initializeSnakeParams(GameParams_t *params);
GameParams_t *updateSnakeParams(GameParams_t *params);

namespace s21 {
class GameSnake {
 public:
  GameSnake(GameParams_t *params);
  ~GameSnake();

  GameParams_t *data;

  void processUserInput(UserAction_t action);
  void startGame();
  void pauseGame();
  void gameOver();
  void removeParams();
  void turnLeft();
  void turnRight();
  void moveForward();
  void updateField();
  void resetField();
  void spawnFood();
  int **allocate2DArray(int nRows, int nCols);

  static std::map<GameState_t, std::map<UserAction_t, GameSnake>> fsmTable;

 private:
  Snake *snake;
  SnakeItem *food;
  static const int fieldSizeX = FIELD_WIDTH;
  static const int fieldSizeY = FIELD_HEIGHT;
};

class SnakeItem {
  friend Snake;
  friend GameSnake;

 public:
  SnakeItem(int coordX, int coordY);

 private:
  int x;
  int y;
  int color;
};

class Snake {
  friend GameSnake;

 public:
  Snake();

 private:
  static const int snakeBeginSize = 4;
  std::vector<SnakeItem *> snakeBody;
  enum SnakeDirection { up, left, down, right };
  SnakeDirection snakeDirection;

  void reset();
};

}  // namespace s21

#endif