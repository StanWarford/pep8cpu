#include "sim.h"
#include "enu.h"

using namespace Enu;

QVector<int> Sim::Mem(65536);
bool Sim::nBit, Sim::zBit, Sim::vBit, Sim::cBit;

int Sim::aReg = 0;
int Sim::xReg = 0;
int Sim::spReg = 0;
int Sim::pcReg = 0;
int Sim::irReg = 0;
int Sim::t1Reg = 0;
int Sim::t2Reg = 0;
int Sim::t3Reg = 0;
int Sim::t4Reg = 0;
int Sim::t5Reg = 0;
int Sim::t6Reg = 0;

int Sim::MARA = 0;
int Sim::MARB = 0;
int Sim::MDR = 0;

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
