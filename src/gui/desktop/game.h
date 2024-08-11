#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>

/************************************************************
 * @file game.h
 * @brief Snake game logic library header
 ************************************************************/

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

#define DATAFILE_PATH "./data"

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
    GameInfo_t *data;
    GameState_t state;
    bool isActive;
    Figure_t *figure;
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
GameParams_t *updateParams(GameParams_t *params);



class SnakeItem;
class Snake;
class GameField;

class SnakeItem
{
    friend Snake;
    friend GameField;

public:
    SnakeItem(int x, int y);

private:
    int m_x;
    int m_y;
};

class Snake
{
    friend GameField;

public:
    Snake();

private:
    QList<SnakeItem*> m_snakeBody;
    int m_snakeBeginSize;
    enum SnakeDirection { up, left, down, right };
    SnakeDirection m_snakeDirection;
};

class GameField : public QWidget
{
    Q_OBJECT
public:
    GameField();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Snake *m_snake;
    SnakeItem *m_food;
    int m_snakeItemSize;
    QTimer *m_moveSnakeTimer;
    int m_fieldSizeX;
    int m_fieldSizeY;
    int m_score;
    int m_gameSpeed;
    bool m_isPause;
    bool m_isMoveBlocked;
    bool m_isGameOver;
    void SetGameStatus();
    void GameOver();
    void StartNewGame();
    void CreateFood();

private slots:
    void MoveSnakeSlot();

signals:
    void ChangeTextSignal(QString text);
};

#endif // GAME_H
