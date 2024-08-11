#ifndef INFOFIELD_H
#define INFOFIELD_H

#include <QWidget>
#include <QPainter>

class InfoField : public QWidget
{
public:
    InfoField();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QString m_text;

public slots:
    void ChangeTextSlot(QString text);
};

#endif // INFOFIELD_H
