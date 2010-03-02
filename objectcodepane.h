#ifndef OBJECTCODEPANE_H
#define OBJECTCODEPANE_H

#include <QWidget>

namespace Ui {
    class ObjectCodePane;
}

class ObjectCodePane : public QWidget {
    Q_OBJECT
public:
    ObjectCodePane(QWidget *parent = 0);
    ~ObjectCodePane();

    void highlightOnFocus();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ObjectCodePane *ui;
};

#endif // OBJECTCODEPANE_H
