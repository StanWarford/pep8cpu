#include "thinarrowgraphicsitem.h"

#include <QPainter>

ThinArrowGraphicsItem::ThinArrowGraphicsItem(int xStart, int yStart, int xEnd, int yEnd, QColor arrowColor)
{
    x1 = xStart;
    x2 = xEnd;
    y1 = yStart;
    y2 = yEnd;

    color = arrowColor;
}

void ThinArrowGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(color);
    QBrush brush(color);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);

    QPolygon poly;
    // magic numbers 'till I code in a better way to do this - very inflexible right now
    poly << QPoint(x2, y2) << QPoint(x2 + (x1 > x2 ? 8 : -8), y2 - 3) << QPoint(x2 + 8, y2 + 3);

    poly.size();
    painter->drawPolygon(poly);
    // magic numbers 'till I code in a way to do direction
    painter->setRenderHint(QPainter::NonCosmeticDefaultPen);
    painter->drawLine(x1, y1, x2 + 2, y2);
}

void ThinArrowGraphicsItem::updateColor(QColor newColor)
{
    color = newColor;
}

QRectF ThinArrowGraphicsItem::boundingRect() const
{
    const int Margin = 2;
    QPoint topLeft(x1 > x2 ? x1 : x2, y1 > y2 ? y1 : y2);
    QPoint bottomRight(x1 < x2 ? x1 : x2, y1 < y2 ? y1 : y2);
    return QRectF(topLeft, bottomRight);
}
