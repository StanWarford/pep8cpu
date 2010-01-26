#ifndef SIM_H
#define SIM_H

#include <QVector>
#include <QSet>

class Sim
{
public:
    static QVector<int> Mem;
    static QVector<int> Reg;
    static QVector<int> MARA;
    static QVector<int> MARB;
    static QVector<int> MDR;
    static bool nBit, zBit, vBit, cBit;

    // Used for keeping track of which bytes have been modified since last memory update:
    static QSet<int> modifiedBytes;

    static int readByte(int memAddr);
    static void writeByte(int memAddr, int value);
    // Pre: 0 <= value < 256
    // Post: Value is stored in Mem[memAddr]

};

#endif // SIM_H
