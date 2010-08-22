#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
    class MainMemory;
}

class MainMemory : public QWidget {
    Q_OBJECT
public:
    MainMemory(QWidget *parent = 0);
    ~MainMemory();

    // Populate memory items in the table
    void populateMemoryItems();

    // Refresh the memory to reflect the Sim::Mem object
    void refreshMemory();

    void setMemAddress(int memAddress, int value);

    void setMemPrecondition(int memAddress, int value);
    bool testMemPostcondition(int memAddress, int value);

    void clearMemory();
    // Post: sets all memory to 0x00;

    void showMemEdited(int address);

public slots:
    // Highlights the label based on the label window color saved in the UI file
    void highlightOnFocus();

    // Returns if the table has focus
    bool hasFocus();

private slots:
    // Slot called when the vertical scroll bar changes.
    // Will cause the table to scroll through memory.
    void sliderMoved(int pos);

    // Fires when the data in an item changes, used to store the value into Sim::Mem[]
    void cellDataChanged(QTableWidgetItem* item);

    void scrollToAddress(QString string);

protected:
    void changeEvent(QEvent *e);
    void resizeEvent(QResizeEvent *);

private:
    Ui::MainMemory *ui;

    // List of all the rows currently in the table
    QStringList rows;


    int	highlightedIndex;
    int	currentMemoryOffset;
    char mem[0x10000];

    enum { CELL_COUNT = 30};

    int oldRowCount;

};

#endif // MAINMEMORY_H
