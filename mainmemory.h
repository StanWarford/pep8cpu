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

    // Ensure that the specified memory address is visible.
    void showAddress(int address);

    // Return the value of a byte of memory.
    int getValue(int address);

    // Set the value of a byte of memory.
    void setValue(int address, int value);

    // Reset all memory to zero.
    void clearMemory();

    // Randomize the contents of main memory.
    void populateMemory();

    // Load the contents of main memory.
    // @param values Array of bytes to load into memory.
    void loadMemory(const unsigned char **values);

    static QString fillHexValue(int, int, int base = 16);

    // Clear the current address highlight
    void resetHighlight();

    // Highlight the specified address.
    void setHighlight(int address);

    // Reposition the table to display the specified address of main memory.
    void repositionTable(int address);

public slots:
    // Slot called when an item in the table changes.  This is used
    // to sync the hex / dec values.
    void slotItemChanged(QTableWidgetItem *item);

    // Slot called when the vertical scroll bar changes.
    // Will cause the table to scroll through memory.
    void slotSliderChanged(int value);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainMemory *ui;

    int	highlightedIndex;
    int	currentMemoryOffset;
    char mem[0x10000];

    enum { CELL_COUNT = 30};

};

#endif // MAINMEMORY_H
