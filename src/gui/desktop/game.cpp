#include "game.h"

/************************************************************
 * @brief Finite state machine table
 *
 * Finite state machine table
 ************************************************************/
//funcPointer fsmTable[STATES_COUNT][SIGNALS_COUNT] = {
//    {startGame, NULL, removeParams, NULL, NULL, NULL, NULL, NULL},  // Start
//    {NULL, pauseGame, removeParams, moveLeft, moveRight, NULL, moveDown,
//     rotate},                                                       // Game
//    {startGame, NULL, removeParams, NULL, NULL, NULL, NULL, NULL},  // Gameover
//};

/************************************************************
 * @brief Figures realtive coordinates
 *
 * Figures realtive coordinates
 ************************************************************/
int figures[FIGURES_COUNT][8] = {
    {0, -1, 0, 0, 0, 1, 0, 2},   {-1, -1, 0, -1, 0, 0, 0, 1},
    {0, -1, 0, 0, 0, 1, -1, 1},  {-1, 0, -1, 1, 0, 0, 0, 1},
    {0, -1, 0, 0, -1, 0, -1, 1}, {0, -1, 0, 0, -1, 0, 0, 1},
    {-1, -1, -1, 0, 0, 0, 0, 1},
    };

void userInput(UserAction_t action, bool hold) {
    if (hold) printf(" ");
    GameParams_t *params = updateParams(NULL);
    GameState_t state = params->state;
    funcPointer func = fsmTable[state][action];
    if (func) func(params);
}

GameInfo_t updateCurrentState(void) {
    GameParams_t *params = updateParams(NULL);
    shift(params);
    return *params->data;
}

GameParams_t *updateParams(GameParams_t *params) {
    static GameParams_t *data;
    if (params != NULL) data = params;
    return data;
}

GameField::GameField()
{
    setFixedSize(200, 400);
    setFocusPolicy(Qt::StrongFocus);

    m_snakeItemSize = 20;
    m_fieldSizeX = width() / m_snakeItemSize;
    m_fieldSizeY = height() / m_snakeItemSize;

    StartNewGame();
}

void GameField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QBrush gameFieldBrush(QColor(139, 144, 163), Qt::SolidPattern);
    QBrush snakeBrush(QColor(140, 206, 147), Qt::SolidPattern);
    QBrush foodBrush(QColor(247, 103, 123), Qt::SolidPattern);

    QPainter painter;
    painter.begin(this);

    if (m_isGameOver) {
        painter.setPen(QColor(250, 250, 250));
        painter.setFont(QFont("Roboto", 15, 700));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "GAME OVER\nscore : " + QString::number(m_score));
        return;
    }

    painter.setBrush(gameFieldBrush);
    painter.setPen(QColor(50, 50, 50));
    painter.drawRect(0, 0, width() - 1, height() - 1);
    painter.setBrush(snakeBrush);
    painter.setPen(QColor(0, 0, 0));

    for (int i = 0; i < m_snake->m_snakeBody.size(); ++i) {
        painter.drawRect(
            m_snake->m_snakeBody[i]->m_x * m_snakeItemSize,
            m_snake->m_snakeBody[i]->m_y * m_snakeItemSize,
            m_snakeItemSize,
            m_snakeItemSize
        );
    }

    painter.setBrush(foodBrush);
    painter.drawEllipse(m_food->m_x * m_snakeItemSize, m_food->m_y * m_snakeItemSize, m_snakeItemSize, m_snakeItemSize);

    painter.end();
    m_isMoveBlocked = false;
}

void GameField::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (m_isGameOver) {
            StartNewGame();
            return;
        }

        m_isPause = !m_isPause;
        SetGameStatus();
    }

    if (m_isMoveBlocked) {
        return;
    }

    if (event->key() == Qt::Key_Left && m_snake->m_snakeDirection != Snake::SnakeDirection::right) {
        m_snake->m_snakeDirection = Snake::SnakeDirection::left;
    }

    if (event->key() == Qt::Key_Right && m_snake->m_snakeDirection != Snake::SnakeDirection::left) {
        m_snake->m_snakeDirection = Snake::SnakeDirection::right;
    }

    if (event->key() == Qt::Key_Up && m_snake->m_snakeDirection != Snake::SnakeDirection::down) {
        m_snake->m_snakeDirection = Snake::SnakeDirection::up;
    }

    if (event->key() == Qt::Key_Down && m_snake->m_snakeDirection != Snake::SnakeDirection::up) {
        m_snake->m_snakeDirection = Snake::SnakeDirection::down;
    }

    m_isMoveBlocked = true;
}


void GameField::SetGameStatus()
{
    QString text;

    if (m_isPause) {
        m_moveSnakeTimer->stop();
        text = "счёт : " + QString::number(m_score) + "\nпродолжить - ПРОБЕЛ";
    } else {
        m_moveSnakeTimer->start(m_gameSpeed);
        text = "счёт : " + QString::number(m_score) + "\nпауза - ПРОБЕЛ";
    }

    emit ChangeTextSignal(text);
}

void GameField::GameOver()
{
    m_isGameOver = true;
    QString text = "начать заново - ПРОБЕЛ";
    emit ChangeTextSignal(text);
    m_moveSnakeTimer->stop();
    delete m_snake;
    delete m_food;
    delete m_moveSnakeTimer;
}

void GameField::StartNewGame()
{
    m_isPause = false;
    m_isMoveBlocked = false;
    m_score = 0;
    m_gameSpeed = 300;
    m_isGameOver = false;

    m_snake = new Snake();
    m_food = new SnakeItem(m_fieldSizeX / 2, m_fieldSizeY / 2);
    m_moveSnakeTimer = new QTimer();
    connect(m_moveSnakeTimer, &QTimer::timeout, this, &GameField::MoveSnakeSlot);
    m_moveSnakeTimer->start(m_gameSpeed);

    QString text = "счёт : " + QString::number(m_score) + "\nпауза - ПРОБЕЛ";
    emit ChangeTextSignal(text);
}

void GameField::CreateFood()
{
    m_food->m_x = QRandomGenerator::global()->bounded(0, m_fieldSizeX - 1);
    m_food->m_y = QRandomGenerator::global()->bounded(0, m_fieldSizeY - 1);

    for (int i = 0; i < m_snake->m_snakeBody.size(); ++i) {
        if (m_food->m_x == m_snake->m_snakeBody[i]->m_x && m_food->m_y == m_snake->m_snakeBody[i]->m_y) {
            return CreateFood();
        }
    }
}

void GameField::MoveSnakeSlot()
{
    SnakeItem *newSnakeItem;

    if (m_snake->m_snakeDirection == Snake::SnakeDirection::right) {
        newSnakeItem = new SnakeItem(m_snake->m_snakeBody[0]->m_x + 1, m_snake->m_snakeBody[0]->m_y);
    } else if (m_snake->m_snakeDirection == Snake::SnakeDirection::left) {
        newSnakeItem = new SnakeItem(m_snake->m_snakeBody[0]->m_x - 1, m_snake->m_snakeBody[0]->m_y);
    } else if (m_snake->m_snakeDirection == Snake::SnakeDirection::up) {
        newSnakeItem = new SnakeItem(m_snake->m_snakeBody[0]->m_x, m_snake->m_snakeBody[0]->m_y - 1);
    } else {
        newSnakeItem = new SnakeItem(m_snake->m_snakeBody[0]->m_x, m_snake->m_snakeBody[0]->m_y + 1);
    }

    if (newSnakeItem->m_x >= m_fieldSizeX) {
        newSnakeItem->m_x = 0;
    } else if (newSnakeItem->m_x < 0) {
        newSnakeItem->m_x = m_fieldSizeX - 1;
    } else if (newSnakeItem->m_y >= m_fieldSizeY) {
        newSnakeItem->m_y = 0;
    } else if (newSnakeItem->m_y < 0) {
        newSnakeItem->m_y = m_fieldSizeY - 1;
    }

    for (int i = 0; i < m_snake->m_snakeBody.size(); ++i) {
        // m_snake->m_snakeBody[0]->m_x == m_snake->m_snakeBody[i]->m_x -- why crashes?
        if (newSnakeItem->m_x == m_snake->m_snakeBody[i]->m_x && newSnakeItem->m_y == m_snake->m_snakeBody[i]->m_y) {
            GameOver();
        }
    }

    if (newSnakeItem->m_x == m_food->m_x && newSnakeItem->m_y == m_food->m_y) {
        m_score++;
        m_gameSpeed -= 20;
        m_moveSnakeTimer->setInterval(m_gameSpeed);
        CreateFood();
        QString text = "счёт : " + QString::number(m_score) + "\nпауза - ПРОБЕЛ";
        emit ChangeTextSignal(text);
    } else {
        m_snake->m_snakeBody.removeLast();
    }

    m_snake->m_snakeBody.insert(0, newSnakeItem);
    repaint();
}

SnakeItem::SnakeItem(int x, int y)
{
    m_x = x;
    m_y = y;
}

Snake::Snake()
{
    m_snakeBeginSize = 4;

    for (int i = 0; i < m_snakeBeginSize; ++i) {
        m_snakeBody.insert(0, new SnakeItem(i, 0));
    }

    m_snakeDirection = SnakeDirection::right;
}
