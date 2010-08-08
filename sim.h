#ifndef SIM_H
#define SIM_H

#include <QVector>
#include <QSet>

#include "code.h"

class Sim
{
public:
    static QVector<quint8> Mem;
    static bool nBit, zBit, vBit, cBit;

    static QVector<quint8> regBank;

    static quint8 MARA;
    static quint8 MARB;
    static quint8 MDR;

    static Enu::MainBusState mainBusState;

    // Used for keeping track of which bytes have been modified since last memory update:
    static QSet<int> modifiedBytes;

    static bool memReadPrevStep;
    static bool memWritePrevStep;

    static QList<Code *> codeList;
    static int microProgramCounter;
    static int microCodeCurrentLine;

    static QStringList microcodeSourceList;
    static void setMicrocodeSourceList();

    static int readByte(int memAddr);
    static void writeByte(int memAddr, int value);
    // Pre: 0 <= value < 256
    // Post: Value is stored in Mem[memAddr]

    static int getAluMask(int fn);

    static bool aluFnIsUnary(int fn);

    static bool advanceSimulation();

    static bool atEndOfSim();

    static void initMRegs();

};

#endif // SIM_H
