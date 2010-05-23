#ifndef REGLINEEDIT_H
#define REGLINEEDIT_H

#include <QLineEdit>

class RegLineEdit : public QLineEdit
{
Q_OBJECT
public:
    explicit RegLineEdit(QWidget *parent = 0);

private:
    void keyPressEvent(QKeyEvent *e);

signals:

public slots:

};

#endif // REGLINEEDIT_H
