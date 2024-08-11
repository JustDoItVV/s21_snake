#include "infofield.h"

InfoField::InfoField()
{
    setFixedSize(200, 400);
    m_text = "счёт : 0\nпауза - ПРОБЕЛ";
}

void InfoField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter;
    painter.begin(this);
    painter.drawRect(0, 0, width() - 1, height() - 1);
    painter.setPen(QColor(250, 250, 250));
    painter.setFont(QFont("Roboto", 10, 700));
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, m_text);
    painter.end();
}

void InfoField::ChangeTextSlot(QString text)
{
    m_text = text;
    repaint();
}
