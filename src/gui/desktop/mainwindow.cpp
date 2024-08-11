#include "mainwindow.h"

#include <iostream>

using namespace s21;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setMinimumSize(420, 420);
  setStyleSheet("background: rgb(90, 100, 112);");

  centralWidget = new QWidget();
  gridLayout = new QGridLayout();
  gameField = new GameField();
  infoField = new InfoField(gameField->params);
  connect(gameField, &GameField::updateInfoText, infoField,
          &InfoField::updateInfoTextSlot);

  gridLayout->addWidget(gameField, 0, 0);
  gridLayout->addWidget(infoField, 0, 1);

  centralWidget->setLayout(gridLayout);
  setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

GameField::GameField() {
  setFixedSize(200, 400);
  setFocusPolicy(Qt::StrongFocus);

  fieldSizeX = width() / cellSize;
  fieldSizeY = height() / cellSize;

  params = new GameParams_t();
  data = new GameInfo_t();
  params->data = data;

  initializeParams(params);
  updateParams(params);

  gameTickTimer = new QTimer();
  connect(gameTickTimer, &QTimer::timeout, this, &GameField::tickGame);
  gameTickTimer->start(startSpeed - speedDecrement * params->data->speed);
}

void GameField::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QBrush gameFieldBrush(QColor(139, 144, 163), Qt::SolidPattern);
  QBrush infoBrush(QColor(200, 200, 200), Qt::SolidPattern);
  QBrush color1CyanBrush(QColor(0, 255, 255), Qt::SolidPattern);
  QBrush color2BlueBrush(QColor(255, 100, 255), Qt::SolidPattern);
  QBrush color3OrangeBrush(QColor(255, 165, 0), Qt::SolidPattern);
  QBrush color4YellowBrush(QColor(255, 255, 0), Qt::SolidPattern);
  QBrush color5GreenBrush(QColor(0, 128, 0), Qt::SolidPattern);
  QBrush color6MagentaBrush(QColor(255, 0, 255), Qt::SolidPattern);
  QBrush color7RedBrush(QColor(255, 0, 0), Qt::SolidPattern);

  QPainter painter;
  painter.begin(this);

  painter.setBrush(gameFieldBrush);
  painter.setPen(QColor(50, 50, 50));
  painter.drawRect(0, 0, width(), height());
  painter.setPen(QColor(0, 0, 0));

  for (size_t row = BORDER_SIZE; row < FIELD_HEIGHT - BORDER_SIZE; ++row) {
    for (size_t col = BORDER_SIZE; col < FIELD_WIDTH - BORDER_SIZE; ++col) {
      if (params->data->field[row][col]) {
        switch (params->data->field[row][col]) {
          case 1:
            painter.setBrush(color1CyanBrush);
            break;
          case 2:
            painter.setBrush(color2BlueBrush);
            break;
          case 3:
            painter.setBrush(color3OrangeBrush);
            break;
          case 4:
            painter.setBrush(color4YellowBrush);
            break;
          case 5:
            painter.setBrush(color5GreenBrush);
            break;
          case 6:
            painter.setBrush(color6MagentaBrush);
            break;
          case 7:
            painter.setBrush(color7RedBrush);
            break;
          default:
            painter.setBrush(gameFieldBrush);
            break;
        }
        painter.drawRect((col - BORDER_SIZE) * cellSize,
                         (row - BORDER_SIZE) * cellSize, cellSize, cellSize);
      }
    }
  }

  if (params->state == GameState_t::START) {
    painter.setBrush(infoBrush);
    painter.setPen(QColor(50, 50, 50));
    painter.drawRect(5, height() / 2 - 16, width() - 10, 32);
    painter.setFont(QFont("Roboto", 13, 700));
    painter.drawText(QRect(5, height() / 2 - 16, width() - 10, 32),
                     Qt::AlignCenter, "Press ENTER to start");
  }

  if (params->state == GameState_t::GAMEOVER) {
    painter.setBrush(infoBrush);
    painter.setPen(QColor(50, 50, 50));
    painter.drawRect(5, height() / 2 - 32, width() - 10, 64);
    painter.setFont(QFont("Roboto", 13, 700));
    painter.drawText(QRect(5, height() / 2 - 32, width() - 10, 64),
                     Qt::AlignCenter, "GAMEOVE\nPress ENTER\nto start again");
  }

  painter.end();
}

void GameField::keyPressEvent(QKeyEvent *event) {
  UserAction_t action = UserAction_t::Up;

  if (event->key() == Qt::Key_Return) {
    action = UserAction_t::Start;
  }
  if (event->key() == Qt::Key_Space) {
    action = UserAction_t::Pause;
  }
  if (event->key() == Qt::Key_Escape) {
    action = UserAction_t::Terminate;
  }
  if (event->key() == Qt::Key_Left) {
    action = UserAction_t::Left;
  }
  if (event->key() == Qt::Key_Right) {
    action = UserAction_t::Right;
  }
  if (event->key() == Qt::Key_Up) {
    action = UserAction_t::Up;
  }
  if (event->key() == Qt::Key_Down) {
    action = UserAction_t::Down;
  }
  if (event->key() == Qt::Key_R) {
    action = UserAction_t::Action;
  }

  userInput(action, false);
}

void GameField::tickGame() {
  if (params->state == GAME && !params->data->pause) {
    updateCurrentState();
    emit updateInfoText(params);
    gameTickTimer->setInterval(startSpeed -
                               speedDecrement * params->data->speed);
  }

  repaint();
}

InfoField::InfoField(GameParams_t *gameParams) {
  setFixedSize(200, 400);
  params = gameParams;
}

void InfoField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QBrush gameFieldBrush(QColor(139, 144, 163), Qt::SolidPattern);
  QBrush infoBrush(QColor(200, 200, 200), Qt::SolidPattern);
  QBrush color1CyanBrush(QColor(0, 255, 255), Qt::SolidPattern);
  QBrush color2BlueBrush(QColor(255, 100, 255), Qt::SolidPattern);
  QBrush color3OrangeBrush(QColor(255, 165, 0), Qt::SolidPattern);
  QBrush color4YellowBrush(QColor(255, 255, 0), Qt::SolidPattern);
  QBrush color5GreenBrush(QColor(0, 128, 0), Qt::SolidPattern);
  QBrush color6MagentaBrush(QColor(255, 0, 255), Qt::SolidPattern);
  QBrush color7RedBrush(QColor(255, 0, 0), Qt::SolidPattern);
  QPainter painter;

  painter.begin(this);
  painter.drawRect(0, 0, width() - 1, height() - 1);
  painter.drawRect(0, 250, width() - 1, height() - 1);
  painter.setPen(QColor(250, 250, 250));
  painter.setFont(QFont("Roboto", 12, 700));

  painter.drawText(QRect(10, 10, width() - 10, 20), Qt::AlignLeft,
                   "HIGH SCORE: " + QString::number(params->data->high_score));
  painter.drawText(QRect(10, 50, width() - 10, 20), Qt::AlignLeft,
                   "SCORE: " + QString::number(params->data->score));
  painter.drawText(QRect(10, 90, width() - 10, 20), Qt::AlignLeft,
                   "LEVEL: " + QString::number(params->data->level));
  painter.drawText(QRect(10, 130, width() - 10, 20), Qt::AlignLeft,
                   "SPEED: " + QString::number(params->data->speed));
  if (params->messages.secondaryField) {
    painter.drawText(QRect(10, 170, width() - 10, 20), Qt::AlignLeft,
                     params->messages.secondaryField);
    for (size_t row = 0; row < FIGURE_HEIGHT; ++row) {
      for (size_t col = 0; col < FIGURE_WIDTH; ++col) {
        switch (params->data->next[row][col]) {
          case 1:
            painter.setBrush(color1CyanBrush);
            break;
          case 2:
            painter.setBrush(color2BlueBrush);
            break;
          case 3:
            painter.setBrush(color3OrangeBrush);
            break;
          case 4:
            painter.setBrush(color4YellowBrush);
            break;
          case 5:
            painter.setBrush(color5GreenBrush);
            break;
          case 6:
            painter.setBrush(color6MagentaBrush);
            break;
          case 7:
            painter.setBrush(color7RedBrush);
            break;
          default:
            painter.setBrush(gameFieldBrush);
            break;
        }
        painter.drawRect(60 + col * GameField::cellSize,
                         200 + row * GameField::cellSize, GameField::cellSize,
                         GameField::cellSize);
      }
    }
  }

  int hintsCoordY = 252;
  painter.drawText(QRect(17, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                   "SPACE - Pause game");
  hintsCoordY += 25;
  if (params->messages.showLeftKey) {
    painter.drawText(QRect(44, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                     QString::fromWCharArray(params->messages.leftKey));
    hintsCoordY += 25;
  }
  if (params->messages.showRightKey) {
    painter.drawText(QRect(44, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                     QString::fromWCharArray(params->messages.rightKey));
    hintsCoordY += 25;
  }
  if (params->messages.showDownKey) {
    painter.drawText(QRect(44, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                     QString::fromWCharArray(params->messages.downKey));
    hintsCoordY += 25;
  }
  if (params->messages.showActionKey) {
    painter.drawText(QRect(46, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                     QString::fromWCharArray(params->messages.actionKey));
    hintsCoordY += 25;
  }
  painter.drawText(QRect(31, hintsCoordY, width() - 10, 20), Qt::AlignLeft,
                   "ESC  - Exit game");

  painter.end();
}

void InfoField::updateInfoTextSlot(GameParams_t *gameParams) {
  params = gameParams;
  repaint();
}
