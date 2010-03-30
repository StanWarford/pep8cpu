#ifndef OBJECTCODELABEL_H
#define OBJECTCODELABEL_H

#include <QLabel>

class ObjectCodeLabel : public QLabel
{
Q_OBJECT
public:
    explicit ObjectCodeLabel(QWidget *parent = 0);

private:
    void drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // OBJECTCODELABEL_H
