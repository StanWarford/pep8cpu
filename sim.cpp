#include "sim.h"
#include "enu.h"

using namespace Enu;

QVector<int> Sim::Mem(65536);
QVector<int> Sim::Reg(32);
QVector<int> Sim::MARA(2);
QVector<int> Sim::MARB(2);
QVector<int> Sim::MDR(2);
bool Sim::nBit, Sim::zBit, Sim::vBit, Sim::cBit;

int aReg = 0;
int xReg = 0;
int spReg = 0;
int pcReg = 0;
int irReg = 0;
int t1Reg = 0;
int t2Reg = 0;
int t3Reg = 0;
int t4Reg = 0;
int t5Reg = 0;
int t6Reg = 0;

QSet<int> Sim::modifiedBytes;

bool Sim::memReadPrevStep = false;
bool Sim::memWritePrevStep = false;

QList<Code *> Sim::codeList;
int Sim::microProgramCounter;
int Sim::microCodeCurrentLine;

QStringList Sim::microcodeSourceList;
void Sim::setMicrocodeSourceList() {
    Sim::microcodeSourceList.clear();
    for (int i = 0; i < Sim::codeList.length(); i++) {
        Sim::microcodeSourceList.append(Sim::codeList.at(i)->getSourceCode());
    }
}

int Sim::readByte(int memAddr)
{
    return Mem[memAddr & 0xffff];
}

void Sim::writeByte(int memAddr, int value)
{
    Mem[memAddr & 0xffff] = value;
    modifiedBytes.insert(memAddr & 0xffff);
}

bool Sim::advanceSimulation()
{

    return true;
}

bool Sim::atEndOfSim()
{
    return microCodeCurrentLine >= codeList.size() - 1;
}
