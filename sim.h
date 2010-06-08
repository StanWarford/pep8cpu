#ifndef SIM_H
#define SIM_H

#include <QVector>
#include <QSet>

#include "code.h"

class Sim
{
public:
    static QVector<int> Mem;
    static bool nBit, zBit, vBit, cBit;

    static int aReg;
    static int xReg;
    static int spReg;
    static int pcReg;
    static int irReg;
    static int t1Reg;
    static int t2Reg;
    static int t3Reg;
    static int t4Reg;
    static int t5Reg;
    static int t6Reg;
    static const int m1Reg = 0x0001;
    static const int m2Reg = 0x0203;
    static const int m3Reg = 0x0408;
    static const int m4Reg = 0xFAFC;
    static const int m5Reg = 0xFEFF;

    static int MARA;
    static int MARB;
    static int MDR;

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
    static int readRegByte(int reg);
    static void putRegByte(int reg, int value);

    static bool aluFnIsUnary(int fn);

    static bool advanceSimulation();

    static bool atEndOfSim();



};

#endif // SIM_H
