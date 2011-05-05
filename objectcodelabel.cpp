// File: objectcodelabel.cpp
/*
    Pep8CPU is a CPU simulator for executing microcode sequences to
    implement instructions in the instruction set of the Pep/8 computer.

    Copyright (C) 2010  J. Stanley Warford, Pepperdine University

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

