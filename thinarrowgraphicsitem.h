#ifndef THINARROWGRAPHICSITEM_H
#define THINARROWGRAPHICSITEM_H

#include <QGraphicsItem>

class ThinArrowGraphicsItem : public QGraphicsItem
{
public:
    ThinArrowGraphicsItem(int x1, int y1, int x2, int y2, QColor color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateColor(QColor color);

    QRectF boundingRect() const;

private:
    int x1;
    int y1;
    int x2;
    int y2;
    QColor color;
};

#endif // THINARROWGRAPHICSITEM_H
