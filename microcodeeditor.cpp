#include <QtGui>

#include "microcodeeditor.h"\

#include <QDebug>

MicrocodeEditor::MicrocodeEditor(QWidget *parent, bool highlightCurrentLine, bool isReadOnly) : QPlainTextEdit(parent)
{
    setFont(QFont("Courier"));

    highlightCurLine = highlightCurrentLine;

    lineNumberArea = new LineNumberArea(this);

    setReadOnly(isReadOnly);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(textChanged()), this, SLOT(repaint()));
    connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
    //    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

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
        for (int i = 0; i < Sim::microCodeCurrentLine; i++) {
            cursor.movePosition(QTextCursor::NextBlock);
        }
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor); // select to end of line

        selection.cursor = cursor;
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void MicrocodeEditor::highlightCurrentLine()
{
    int curLine = document()->findBlockByNumber(textCursor().position()).blockNumber();

}

void MicrocodeEditor::clearSimulationView()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
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
    QTextBlock block;
    int blockNumber;
    int top;
    int bottom;

    // Highlight the current line containing the cursor
    if (highlightCurLine && textCursor().block().isVisible()) {
        block = firstVisibleBlock();
        blockNumber = block.blockNumber();
        top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        bottom = top + (int) blockBoundingRect(block).height();
        while (blockNumber != textCursor().block().blockNumber() && block.isValid()) {
            block = block.next();
            top = bottom;
            bottom = top + (int) blockBoundingRect(block).height();
            ++blockNumber;
        }
        if (block.isValid()) {
            painter.setPen(QColor(232, 232, 232));
            painter.setBrush(QBrush(QColor(Qt::red).lighter(170)));
            painter.drawRect(-1, top, lineNumberArea->width(), fontMetrics().height());
        }
    }

    // Display the cycle numbers
    block = firstVisibleBlock();
    blockNumber = block.blockNumber();
    top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    bottom = top + (int) blockBoundingRect(block).height();
    int cycleNumber = 1;
    QList<int> blockToCycleNumber;
    QStringList sourceCodeList = toPlainText().split('\n');
    for (int i = 0; i < sourceCodeList.size(); i++) {
        if (QRegExp("^//|^\\s*$|^unitpre|^unitpost", Qt::CaseInsensitive).indexIn(sourceCodeList.at(i)) == 0) {
            blockToCycleNumber << -1;
        }
        else {
            blockToCycleNumber << cycleNumber++;
        }
    }
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = blockToCycleNumber.at(blockNumber) == -1 ? QString("") : QString::number(blockToCycleNumber.at(blockNumber));
            painter.setPen(QColor(128, 128, 130)); // grey
            painter.drawText(-1, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
    lineNumberArea->update();
}
