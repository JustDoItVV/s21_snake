#ifndef MAINMENU_H
#define MAINMENU_H

#include "types.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QWidget>
#include <QPainter>

namespace s21 {
class MainMenu : public QWidget
{
public:
    MainMenu(Game *currentGame);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void setCurrentGame();
};
}

#endif // MAINMENU_H
