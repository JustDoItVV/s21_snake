#include "mainmenu.h"

using namespace s21;

MainMenu::MainMenu(Game *currentGame)
{

}

void MainMenu::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        QCoreApplication::quit();
    }

//    if (event->key() == Qt::Key_1) {
//        MainWindow::m_currentGame = MainWindow::Cu
//    }
}
