#include "sim.h"
#include "enu.h"

using namespace Enu;

QVector<quint8> Sim::Mem(65536);
bool Sim::nBit, Sim::zBit, Sim::vBit, Sim::cBit;

QVector<quint8> Sim::regBank(32);

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

int Sim::getAluMask(int fn) {
    switch (fn) {
    case 0: return Enu::NMask | Enu::ZMask;
    case 1: return Enu::NMask | Enu::ZMask | Enu::VMask | Enu::CMask;
    case 2: return Enu::NMask | Enu::ZMask | Enu::VMask | Enu::CMask;
    case 3: return Enu::NMask | Enu::ZMask | Enu::VMask | Enu::CMask;
    case 4: return Enu::NMask | Enu::ZMask | Enu::VMask | Enu::CMask;
    case 5: return Enu::NMask | Enu::ZMask;
    case 6: return Enu::NMask | Enu::ZMask;
    case 7: return Enu::NMask | Enu::ZMask;
    case 8: return Enu::NMask | Enu::ZMask;
    case 9: return Enu::NMask | Enu::ZMask;
    case 10: return Enu::NMask | Enu::ZMask;
    case 11: return Enu::NMask | Enu::ZMask | Enu::VMask | Enu::CMask;
    case 12: return Enu::NMask | Enu::ZMask | Enu::CMask;
    case 13: return Enu::NMask | Enu::ZMask | Enu::CMask;
    case 14: return Enu::NMask | Enu::ZMask | Enu::CMask;
    case 15: break;
    default: break;
    }
    return 0;
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

void Sim::initMRegs()
{
    regBank[22] = 0x00;
    regBank[23] = 0x01;
    regBank[24] = 0x02;
    regBank[25] = 0x03;
    regBank[26] = 0x04;
    regBank[27] = 0x08;
    regBank[28] = 0xFA;
    regBank[29] = 0xFC;
    regBank[30] = 0xFE;
    regBank[31] = 0xFF;
}




