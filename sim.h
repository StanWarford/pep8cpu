#ifndef SIM_H
#define SIM_H

#include <QVector>
#include <QSet>

#include "code.h"

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

    static bool memReadPrevStep;
    static bool memWritePrevStep;

    static QList<Code *> codeList;
    static int microProgramCounter;
    static int microCodeCurrentLine;

    static int readByte(int memAddr);
    static void writeByte(int memAddr, int value);
    // Pre: 0 <= value < 256
    // Post: Value is stored in Mem[memAddr]

    static bool advanceSimulation();

    static bool atEndOfSim();



};

#endif // SIM_H
