#include "objectcodelabel.h"

#include <QPainter>

ObjectCodeLabel::ObjectCodeLabel(QWidget *parent) :
    QLabel(parent)
{

}

void ObjectCodeLabel::drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text)
{
        painter->save();
        painter->translate(x, y);
        painter->rotate(degrees);
        painter->drawText(0, 0, text);
        painter->restore();
}

void ObjectCodeLabel::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QFontMetrics fm(this->font());
    int height = fm.averageCharWidth();

    // Draw the rotated text. Magic numbers are the offsets from the labels
    // to spread them out to correspond to the correct object code numbers.
    drawRotatedText(&p, 270, height * 2, this->height() - 2, "LoadCk");
    drawRotatedText(&p, 270, height * 4, this->height() - 2, "C");
    drawRotatedText(&p, 270, height * 7, this->height() - 2, "B");
    drawRotatedText(&p, 270, height * 10, this->height() - 2, "A");
    drawRotatedText(&p, 270, height * 13, this->height() - 2, "MARCk");
    drawRotatedText(&p, 270, height * 15, this->height() - 2, "MDRCk");
    drawRotatedText(&p, 270, height * 17, this->height() - 2, "AMux");
    drawRotatedText(&p, 270, height * 19, this->height() - 2, "MDRMux");
    drawRotatedText(&p, 270, height * 21, this->height() - 2, "CMux");
    drawRotatedText(&p, 270, height * 23, this->height() - 2, "ALU");
    drawRotatedText(&p, 270, height * 26, this->height() - 2, "CCk");
    drawRotatedText(&p, 270, height * 28, this->height() - 2, "VCk");
    drawRotatedText(&p, 270, height * 30, this->height() - 2, "ANDZ");
    drawRotatedText(&p, 270, height * 32, this->height() - 2, "ZCk");
    drawRotatedText(&p, 270, height * 34, this->height() - 2, "NCk");
    drawRotatedText(&p, 270, height * 36, this->height() - 2, "MemWrite");
    drawRotatedText(&p, 270, height * 38, this->height() - 2, "MemRead");
}

