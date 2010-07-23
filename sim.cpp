#include "sim.h"
#include "enu.h"

using namespace Enu;

QVector<int> Sim::Mem(65536);
bool Sim::nBit, Sim::zBit, Sim::vBit, Sim::cBit;

QVector<quint8> Sim::regBank;

quint8 Sim::MARA = 0;
quint8 Sim::MARB = 0;
quint8 Sim::MDR = 0;

Enu::MainBusState Sim::mainBusState;

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

bool Sim::aluFnIsUnary(int fn)
{
    switch (fn) {
    case 0:
        return true;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        return false;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        return true;
    default:
        break;
    }
    return false;
}

bool Sim::advanceSimulation()
{

    return true;
}

bool Sim::atEndOfSim()
{
    return microCodeCurrentLine >= codeList.size() - 1;
}






