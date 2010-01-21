#ifndef SIM_H
#define SIM_H

#include <QVector>

class Sim
{
public:
    static QVector<int> Mem;
    static QVector<int> Reg;
    static QVector<int> MARA;
    static QVector<int> MARB;
    static QVector<int> MDR;
    static bool nBit, zBit, vBit, cBit;
};

#endif // SIM_H
