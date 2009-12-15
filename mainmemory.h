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

    // Ensure that the specified memory address
    // is visible.
    // @param nAddress Address of memory to display.
    void ShowAddress(int nAddress);

    // Return the value of a byte of memory.
    // @param nAddress The address to read.
    // @return int
    int GetValue(int nAddress);

    // Set the value of a byte of memory.
    // @param nAddress The address to of memory to set.
    // @param nValue The byte value to set.
    void SetValue(int nAddress, int nValue);

    // Reset all memory to zero.
    void ClearMemory();

    // Randomize the contents of main memory.
    void PopulateMemory();

    // Load the contents of main memory.
    // @param ppchValues Array of bytes to load into memory.
    void LoadMemory(const unsigned char **ppchValues);

    static QString fillHexValue( int, int, int base = 16 );

    // Clear the current address highlight
    void ResetHighlight();

    // Highlight the specified address.
    void SetHighlight(int nAddress);

    // Reposition the table to display the specified address of main memory.
    void RepositionTable(int nAddress);

public slots:
    // Slot called when an item in the table changes.  This is used
    // to sync the hex / dec values.
    void SlotItemChanged(QTableWidgetItem *pxItem);

    // Slot called when the vertical scroll bar changes.
    // Will cause the table to scroll through memory.
    void SlotSliderChanged(int nValue);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainMemory *ui;

    int	m_nHighlightedIndex;
    int	m_nCurrentMemoryOffset;
    char m_chMem[0x10000];

    enum { CELL_COUNT = 30};

};

#endif // MAINMEMORY_H
