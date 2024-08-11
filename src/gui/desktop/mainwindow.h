#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <QWidget>

#include "../../controller/controller.h"

namespace s21 {

class GameField;
class InfoField;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  GameField *gameField;
  InfoField *infoField;
  QWidget *centralWidget;
  QGridLayout *gridLayout;
};

class GameField : public QWidget {
  Q_OBJECT
 public:
  GameField();
  GameParams_t *params;
  GameInfo_t *data;
  UserAction_t action;
  static const int cellSize = 20;

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  static const int startSpeed = 550;
  static const int speedDecrement = 50;
  QTimer *gameTickTimer;
  int fieldSizeX;
  int fieldSizeY;

 private slots:
  void tickGame();

 signals:
  void updateInfoText(GameParams_t *params);
};

class InfoField : public QWidget {
  Q_OBJECT
 public:
  InfoField(GameParams_t *gameParams);

 protected:
  void paintEvent(QPaintEvent *e) override;

 private:
  GameParams_t *params;

 public slots:
  void updateInfoTextSlot(GameParams_t *params);
};
}  // namespace s21

#endif  // MAINWINDOW_H
