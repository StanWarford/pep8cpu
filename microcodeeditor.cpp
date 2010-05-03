#include <QtGui>

#include "microcodeeditor.h"\

#include <QDebug>

MicrocodeEditor::MicrocodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    setFont(QFont("Courier"));

    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(textChanged()), this, SLOT(repaint()));
    connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));

    updateLineNumberAreaWidth(0);
}

int MicrocodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 4 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void MicrocodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void MicrocodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void MicrocodeEditor::highlightSimulatedLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(QColor(56, 117, 215)); // dark blue
        selection.format.setForeground(Qt::white);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        QTextCursor cursor = QTextCursor(document());
        cursor.setPosition(0);
        for (int i = 0; i < Sim::microProgramCounter; i++) {
            cursor.movePosition(QTextCursor::NextBlock);
        }
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

        selection.cursor = cursor;
//        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void MicrocodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void MicrocodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(232, 232, 232)); // light grey

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    int lineNumber = 1;
    QList<int> blockToLineNumber;
    QStringList sourceCodeList = toPlainText().split('\n');
    for (int i = 0; i < sourceCodeList.size(); i++) {
        if (QRegExp("^//|^\\s*$").indexIn(sourceCodeList[i]) == 0) {
            blockToLineNumber << -1;
        }
        else {
            blockToLineNumber << lineNumber++;
        }
    }

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = blockToLineNumber[blockNumber] == -1 ? QString("") : QString::number(blockToLineNumber[blockNumber]);
            painter.setPen(QColor(128, 128, 130)); // grey
            painter.drawText(-1, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
