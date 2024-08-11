#include "snake.h"

using namespace s21;

/************************************************************
 * @brief Finite state machine table
 *
 * Finite state machine table
 ************************************************************/
// std::map<GameState_t, std::map<UserAction_t, GameField>> GameField::fsmTable
// = {
//     {GameState_t::START,
//      {
//          {UserAction_t::Start, &GameField::startGame},
//          {UserAction_t::Pause, nullptr},
//          {UserAction_t::Terminate, &GameField::removeParams},
//          {UserAction_t::Left, nullptr},
//          {UserAction_t::Right, nullptr},
//          {UserAction_t::Up, nullptr},
//          {UserAction_t::Down, nullptr},
//          {UserAction_t::Action, nullptr},
//      }},
//     {GameState_t::GAME,
//      {
//          {UserAction_t::Start, nullptr},
//          {UserAction_t::Pause, &GameField::pauseGame},
//          {UserAction_t::Terminate, &GameField::removeParams},
//          {UserAction_t::Left, &GameField::turnLeft},
//          {UserAction_t::Right, &GameField::turnRight},
//          {UserAction_t::Up, nullptr},
//          {UserAction_t::Down, nullptr},
//          {UserAction_t::Action, nullptr},
//      }},
//     {GameState_t::GAMEOVER,
//      {
//          {UserAction_t::Start, &GameField::startGame},
//          {UserAction_t::Pause, nullptr},
//          {UserAction_t::Terminate, &GameField::removeParams},
//          {UserAction_t::Left, nullptr},
//          {UserAction_t::Right, nullptr},
//          {UserAction_t::Up, nullptr},
//          {UserAction_t::Down, nullptr},
//          {UserAction_t::Action, nullptr},
//      }},
// };

void userInput(UserAction_t action, bool hold) {
  if (hold) std::cout << " ";
  GameParams_t *params = updateSnakeParams(NULL);
  params->game->processUserInput(action);
}

GameInfo_t updateCurrentState(void) {
  GameParams_t *data = updateSnakeParams(NULL);
  data->game->moveForward();
  data->game->updateField();
  return *data->game->data->data;
}

GameParams_t *updateSnakeParams(GameParams_t *params) {
  static GameParams_t *data;
  if (params != NULL) data = params;
  return data;
}

void GameSnake::processUserInput(UserAction_t action) {
  if (data->state == GameState_t::START) {
    if (action == UserAction_t::Start) {
      startGame();
    }
    if (action == UserAction_t::Pause) {
    }
    if (action == UserAction_t::Terminate) {
      removeParams();
    }
    if (action == UserAction_t::Left) {
    }
    if (action == UserAction_t::Right) {
    }
    if (action == UserAction_t::Up) {
    }
    if (action == UserAction_t::Down) {
    }
    if (action == UserAction_t::Action) {
    }
  }
  if (data->state == GameState_t::GAME) {
    if (action == UserAction_t::Start) {
    }
    if (action == UserAction_t::Pause) {
      pauseGame();
    }
    if (action == UserAction_t::Terminate) {
      removeParams();
    }
    if (action == UserAction_t::Left) {
      turnLeft();
    }
    if (action == UserAction_t::Right) {
      turnRight();
    }
    if (action == UserAction_t::Up) {
    }
    if (action == UserAction_t::Down) {
    }
    if (action == UserAction_t::Action) {
    }
  }
  if (data->state == GameState_t::GAMEOVER) {
    if (action == UserAction_t::Start) {
      startGame();
    }
    if (action == UserAction_t::Pause) {
    }
    if (action == UserAction_t::Terminate) {
      removeParams();
    }
    if (action == UserAction_t::Left) {
    }
    if (action == UserAction_t::Right) {
    }
    if (action == UserAction_t::Up) {
    }
    if (action == UserAction_t::Down) {
    }
    if (action == UserAction_t::Action) {
    }
  }
}

void initializeSnakeParams(GameParams_t *params) {
  srand((unsigned)time(NULL));

  params->game = new GameSnake(params);
  params->state = START;
  params->isActive = true;

  params->messages.showSecondaryField = false;
  params->messages.showLeftKey = true;
  params->messages.leftKey = L"←   - Turn left";
  params->messages.showRightKey = true;
  params->messages.rightKey = L"→   - Turn right";
  params->messages.showDownKey = false;
  params->messages.showActionKey = false;
}

GameSnake::GameSnake(GameParams_t *params) {
  data = params;
  data->data->field = allocate2DArray(FIELD_HEIGHT, FIELD_WIDTH);
  data->data->next = allocate2DArray(FIGURE_HEIGHT, FIGURE_WIDTH);
  resetField();
  data->data->score = 0;

  FILE *fp = fopen(DATAFILE_PATH, "r");
  if (!fp) {
    data->data->high_score = 0;
    fp = fopen(DATAFILE_PATH, "w");
    fprintf(fp, "0\n");
  } else {
    int highScore;
    fscanf(fp, "%d\n", &highScore);
    data->data->high_score = highScore;
  }
  fclose(fp);

  data->data->level = LEVEL_MIN;
  data->data->speed = SPEED_MIN;
  data->data->pause = 0;

  snake = new Snake();
  food = new SnakeItem(fieldSizeX / 2, fieldSizeY / 2);
}

void GameSnake::updateField() {
  resetField();
  data->data->field[food->y][food->x] = FOOD_COLOR;

  for (size_t i = 0; i < snake->snakeBody.size(); ++i) {
    data->data->field[snake->snakeBody[i]->y][snake->snakeBody[i]->x] =
        SNAKE_COLOR;
  }
}

void GameSnake::resetField() {
  for (int row = 0; row < fieldSizeY; ++row) {
    for (int col = 0; col < fieldSizeX; ++col) {
      data->data->field[row][col] = 0;
    }
  }
}

int **GameSnake::allocate2DArray(int nRows, int nCols) {
  int **arr = new int *[nRows];

  for (size_t rowIdx = 0; rowIdx < (size_t)nRows; rowIdx++)
    arr[rowIdx] = new int[nCols];

  return arr;
}

void GameSnake::startGame() {
  data->state = GameState_t::GAME;
  data->data->pause = false;
  data->data->score = 0;
  data->data->level = LEVEL_MIN;
  data->data->speed = SPEED_MIN;
  snake->reset();
  food->x = fieldSizeX / 2;
  food->y = fieldSizeY / 2;
}

SnakeItem::SnakeItem(int coordX, int coordY) {
  x = coordX;
  y = coordY;
}

Snake::Snake() { reset(); }

void Snake::reset() {
  snakeBody.clear();

  for (int i = 0; i < snakeBeginSize; ++i) {
    snakeBody.insert(snakeBody.begin(), new SnakeItem(i, 0));
  }

  snakeDirection = SnakeDirection::right;
}

void GameSnake::moveForward() {
  SnakeItem *newSnakeItem;
  SnakeItem *head = snake->snakeBody[0];

  if (snake->snakeDirection == Snake::SnakeDirection::right) {
    newSnakeItem = new SnakeItem(head->x + 1, head->y);
  } else if (snake->snakeDirection == Snake::SnakeDirection::left) {
    newSnakeItem = new SnakeItem(head->x - 1, head->y);
  } else if (snake->snakeDirection == Snake::SnakeDirection::up) {
    newSnakeItem = new SnakeItem(head->x, head->y - 1);
  } else {
    newSnakeItem = new SnakeItem(head->x, head->y + 1);
  }

  for (size_t i = 0; i < snake->snakeBody.size(); ++i) {
    if ((newSnakeItem->x == snake->snakeBody[i]->x &&
         newSnakeItem->y == snake->snakeBody[i]->y) ||
        newSnakeItem->x < 0 || newSnakeItem->x > fieldSizeX - 1 ||
        newSnakeItem->y < 0 || newSnakeItem->y > fieldSizeY - 1) {
      gameOver();
      return;
    }
  }

  if (newSnakeItem->x == food->x && newSnakeItem->y == food->y) {
    spawnFood();
    data->data->score++;

    if (data->data->speed < SPEED_MAX) {
      data->data->speed++;
      data->data->level++;
    }
  } else {
    snake->snakeBody.pop_back();
  }

  snake->snakeBody.insert(snake->snakeBody.begin(), newSnakeItem);
}

void GameSnake::spawnFood() {
  food->x = rand() % (fieldSizeX - 1);
  food->y = rand() % (fieldSizeY - 1);

  for (size_t i = 0; i < snake->snakeBody.size(); ++i) {
    if (food->x == snake->snakeBody[i]->x &&
        food->y == snake->snakeBody[i]->y) {
      return spawnFood();
    }
  }
}

void GameSnake::turnLeft() {
  if (snake->snakeDirection == Snake::SnakeDirection::up) {
    snake->snakeDirection = Snake::SnakeDirection::left;
  } else if (snake->snakeDirection == Snake::SnakeDirection::down) {
    snake->snakeDirection = Snake::SnakeDirection::right;
  } else if (snake->snakeDirection == Snake::SnakeDirection::left) {
    snake->snakeDirection = Snake::SnakeDirection::down;
  } else {
    snake->snakeDirection = Snake::SnakeDirection::up;
  }
}

void GameSnake::turnRight() {
  if (snake->snakeDirection == Snake::SnakeDirection::up) {
    snake->snakeDirection = Snake::SnakeDirection::right;
  } else if (snake->snakeDirection == Snake::SnakeDirection::down) {
    snake->snakeDirection = Snake::SnakeDirection::left;
  } else if (snake->snakeDirection == Snake::SnakeDirection::left) {
    snake->snakeDirection = Snake::SnakeDirection::up;
  } else {
    snake->snakeDirection = Snake::SnakeDirection::down;
  }
}

void GameSnake::pauseGame() { data->data->pause = !data->data->pause; }

void GameSnake::gameOver() { data->state = GameState_t::GAMEOVER; }

void GameSnake::removeParams() {
  if (data->data->field) {
    for (size_t rowIdx = 0; rowIdx < FIELD_HEIGHT; rowIdx++) {
      delete[] data->data->field[rowIdx];
      data->data->field[rowIdx] = NULL;
    }
    delete[] data->data->field;
    data->data->field = NULL;
  }

  data->state = GAMEOVER;
  data->isActive = false;
}
