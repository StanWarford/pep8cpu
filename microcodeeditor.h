#ifndef MICROCODEEDITOR_H
#define MICROCODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

class MicrocodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    MicrocodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;

    int getMicrocodeBlockNumbers();
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(MicrocodeEditor *editor) : QWidget(editor) {
        microcodeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(microcodeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        microcodeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    MicrocodeEditor *microcodeEditor;
};

#endif // MICROCODEEDITOR_H
