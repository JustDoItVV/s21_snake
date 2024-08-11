#include "mainwindow.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(420, 420);
    m_centralWidget = new QWidget();
    m_gridLayout = new QGridLayout();
    drawMainMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::drawMainMenu()
{
    buttonBrick = new QPushButton();
    buttonBrick->setVisible(true);
    buttonBrick->setText("Brick Game");
    buttonBrick->setObjectName("buttonBrick");
    //    buttonBrick->setStyleSheet(...);
    connect(buttonBrick, &QPushButton::clicked, this, &MainWindow::handleBrickButton);

    buttonSnake = new QPushButton();
    buttonSnake->setVisible(true);
    buttonSnake->setText("Snake");
    buttonSnake->setObjectName("buttonSnake");
//    buttonSnake->setStyleSheet(...);
    connect(buttonSnake, &QPushButton::clicked, this, &MainWindow::handleSnakeButton);

    m_gridLayout->addWidget(buttonBrick, 0, 0);
    m_gridLayout->addWidget(buttonSnake, 1, 0);
    m_centralWidget->setLayout(m_gridLayout);
    setCentralWidget(m_centralWidget);

    setStyleSheet("background: rgb(90, 100, 112);");
}

void MainWindow::drawGame(Game game)
{
    m_gameField = new GameField();
    m_infoField = new InfoField();
    connect(m_gameField, &GameField::ChangeTextSignal, m_infoField, &InfoField::ChangeTextSlot);

    m_gridLayout->addWidget(m_gameField, 0, 0);
    m_gridLayout->addWidget(m_infoField, 0, 1);

    setStyleSheet("background: rgb(90, 100, 112);");
}

void MainWindow::handleBrickButton()
{
    drawGame(Game::snake);
}

void MainWindow::handleSnakeButton()
{
    drawGame(Game::snake);
}

