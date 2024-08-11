#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include "infofield.h"
#include "types.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QStateMachine>
#include <QLabel>
#include <QStackedWidget>
#include <QComboBox>
#include <QPushButton>

namespace s21 {
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *buttonBrick;
    QPushButton *buttonSnake;
    GameField *m_gameField;
    InfoField *m_infoField;
    QWidget *m_centralWidget;
    QGridLayout *m_gridLayout;

    void drawMainMenu();
    void drawGame(Game game);

private slots:
    void handleBrickButton();
    void handleSnakeButton();
};
} // namespace s21

#endif // MAINWINDOW_H
