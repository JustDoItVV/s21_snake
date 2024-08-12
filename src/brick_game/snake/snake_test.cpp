#include "snake.h"

#include <gtest/gtest.h>

using namespace s21;

TEST(snake, updateCurrentState) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  updateSnakeParams(&params);
  GameInfo_t dataCheck = updateCurrentState();

  EXPECT_EQ(params.data->field, dataCheck.field);
  EXPECT_EQ(params.data->next, dataCheck.next);
  EXPECT_EQ(params.data->high_score, dataCheck.high_score);
  EXPECT_EQ(params.data->score, dataCheck.score);
  EXPECT_EQ(params.data->level, dataCheck.level);
  EXPECT_EQ(params.data->pause, dataCheck.pause);
  EXPECT_EQ(params.data->speed, dataCheck.speed);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, updateSnakeParams) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  GameParams_t *paramsCheck1 = updateSnakeParams(&params);
  GameParams_t *paramsCheck2 = updateSnakeParams(NULL);

  EXPECT_EQ(&params, paramsCheck1);
  EXPECT_EQ(&params, paramsCheck2);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, initializeSnakeParams) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);

  EXPECT_EQ(params.data->score, 0);
  EXPECT_EQ(params.data->level, 1);
  EXPECT_EQ(params.data->speed, 1);
  EXPECT_EQ(params.data->pause, 0);
  EXPECT_EQ(params.state, START);
  EXPECT_EQ(params.isActive, true);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_constructor) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);

  EXPECT_EQ(params.data->score, 0);
  EXPECT_EQ(params.data->level, 1);
  EXPECT_EQ(params.data->speed, 1);
  EXPECT_EQ(params.data->pause, 0);
  EXPECT_EQ(params.state, START);
  EXPECT_EQ(params.isActive, true);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_START_Start) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->processUserInput(UserAction_t::Start);

  EXPECT_EQ(params.state, GameState_t::GAME);
  EXPECT_EQ(params.data->pause, false);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_START_Terminate) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->processUserInput(UserAction_t::Terminate);

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  EXPECT_EQ(params.isActive, false);
  EXPECT_EQ(params.data->field, nullptr);
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_GAMEOVER_Start) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAMEOVER;
  params.game->processUserInput(UserAction_t::Start);

  EXPECT_EQ(params.state, GameState_t::GAME);
  EXPECT_EQ(params.data->pause, false);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_GAMEOVER_Terminate) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAMEOVER;
  params.game->processUserInput(UserAction_t::Terminate);

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  EXPECT_EQ(params.isActive, false);
  EXPECT_EQ(params.data->field, nullptr);
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_GAME_Pause) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->processUserInput(UserAction_t::Pause);

  EXPECT_EQ(params.data->pause, true);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_GAME_Terminate) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->processUserInput(UserAction_t::Terminate);

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  EXPECT_EQ(params.isActive, false);
  EXPECT_EQ(params.data->field, nullptr);
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_GAME_Left) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->processUserInput(UserAction_t::Left);

  EXPECT_EQ(params.game->getSnake()->snakeDirection, Snake::SnakeDirection::up);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_processUserInput_GAME_Right) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->processUserInput(UserAction_t::Right);

  EXPECT_EQ(params.game->getSnake()->snakeDirection,
            Snake::SnakeDirection::down);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnLeft_up) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::up;
  params.game->processUserInput(UserAction_t::Left);

  EXPECT_EQ(params.game->getSnake()->snakeDirection,
            Snake::SnakeDirection::left);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnLeft_down) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::down;
  params.game->processUserInput(UserAction_t::Left);

  EXPECT_EQ(params.game->getSnake()->snakeDirection,
            Snake::SnakeDirection::right);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnLeft_left) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::left;
  params.game->processUserInput(UserAction_t::Left);

  EXPECT_EQ(params.game->getSnake()->snakeDirection,
            Snake::SnakeDirection::down);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnLeft_right) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::right;
  params.game->processUserInput(UserAction_t::Left);

  EXPECT_EQ(params.game->getSnake()->snakeDirection, Snake::SnakeDirection::up);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnRight_up) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::up;
  params.game->processUserInput(UserAction_t::Right);

  EXPECT_EQ(params.game->getSnake()->snakeDirection,
            Snake::SnakeDirection::right);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnRight_down) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::down;
  params.game->processUserInput(UserAction_t::Right);

  EXPECT_EQ(params.game->getSnake()->snakeDirection,
            Snake::SnakeDirection::left);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnRight_left) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::left;
  params.game->processUserInput(UserAction_t::Right);

  EXPECT_EQ(params.game->getSnake()->snakeDirection, Snake::SnakeDirection::up);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_turnRight_right) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->getSnake()->snakeDirection = Snake::SnakeDirection::right;
  params.game->processUserInput(UserAction_t::Right);

  EXPECT_EQ(params.game->getSnake()->snakeDirection,
            Snake::SnakeDirection::down);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_gameOver) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.state = GameState_t::GAME;
  params.game->gameOver();

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_1) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->moveForward();

  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->x, 4);
  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->y, 0);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_2) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->moveForward();
  params.game->turnRight();
  params.game->moveForward();

  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->x, 4);
  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->y, 1);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_3) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->moveForward();
  params.game->turnRight();
  params.game->moveForward();
  params.game->turnRight();
  params.game->moveForward();

  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->x, 3);
  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->y, 1);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_4) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->moveForward();
  params.game->turnRight();
  params.game->moveForward();
  params.game->turnLeft();
  params.game->moveForward();
  params.game->turnLeft();
  params.game->moveForward();

  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->x, 5);
  EXPECT_EQ(params.game->getSnake()->snakeBody[0]->y, 0);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_5) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->turnLeft();
  params.game->moveForward();

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_6) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.data->high_score = 0;
  params.game->getFood()->x = 4;
  params.game->getFood()->y = 0;
  params.game->moveForward();

  EXPECT_EQ(params.game->getSnake()->snakeBody.size(), 5);
  EXPECT_EQ(params.data->score, 1);
  EXPECT_EQ(params.data->high_score, 1);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_7) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.data->score = 4;
  params.data->speed = 1;
  params.data->level = 1;
  params.game->getFood()->x = 4;
  params.game->getFood()->y = 0;
  params.game->moveForward();

  EXPECT_EQ(params.game->getSnake()->snakeBody.size(), 5);
  EXPECT_EQ(params.data->score, 5);
  EXPECT_EQ(params.data->level, 2);
  EXPECT_EQ(params.data->speed, 2);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_8) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.data->score = 199;
  params.game->getFood()->x = 4;
  params.game->getFood()->y = 0;
  params.game->moveForward();

  EXPECT_EQ(params.data->score, 200);
  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_9) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->getSnake()->snakeBody[0]->x = 9;
  params.game->moveForward();

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_10) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->getSnake()->snakeBody[0]->x = 9;
  params.game->getSnake()->snakeBody[0]->y = 19;
  params.game->turnRight();
  params.game->moveForward();

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_11) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.game->getSnake()->snakeBody[0]->x = 0;
  params.game->getSnake()->snakeBody[0]->y = 19;
  params.game->turnRight();
  params.game->turnRight();
  params.game->moveForward();

  EXPECT_EQ(params.state, GameState_t::GAMEOVER);
  params.game->removeParams();
  delete params.game;
}

TEST(snake, GameSnake_moveForward_12) {
  GameParams_t params;
  GameInfo_t data;
  params.data = &data;

  initializeSnakeParams(&params);
  params.game->startGame();
  params.data->high_score = 10;
  params.game->getFood()->x = 4;
  params.game->getFood()->y = 0;
  params.game->moveForward();

  EXPECT_EQ(params.game->getSnake()->snakeBody.size(), 5);
  EXPECT_EQ(params.data->score, 1);
  EXPECT_EQ(params.data->high_score, 10);
  params.game->removeParams();
  delete params.game;
}
