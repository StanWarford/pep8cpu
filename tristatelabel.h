#ifndef TRISTATELABEL_H
#define TRISTATELABEL_H

#include <QLabel>

class TristateLabel : public QLabel
{
Q_OBJECT
public:
    enum ToggleMode {Tristate, OneUndefined, ZeroOne};

    explicit TristateLabel(QWidget *parent = 0, ToggleMode mode = Tristate);

private:
    int toggleMode;

signals:
    void clicked();

public slots:
    void toggle();

protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // TRISTATELABEL_H
