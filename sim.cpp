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

int Sim::readRegByte(int reg)
{
    switch (reg) {
    case 0:
        return aReg & 65280; // Returns the left two bytes of 0x____
    case 1:
        return aReg & 255; // Returns the right two bytes of 0x____
    case 2:
        return xReg & 65280;
    case 3:
        return xReg & 255;
    case 4:
        return spReg & 65280;
    case 5:
        return spReg & 255;
    case 6:
        return pcReg & 65280;
    case 7:
        return pcReg & 255;
    case 8:
        return irReg & 16711680;
    case 9:
        return irReg & 65280;
    case 10:
        return irReg & 255;
    case 11:
        return t1Reg & 255;
    case 12:
        return t2Reg & 65280;
    case 13:
        return t2Reg & 255;
    case 14:
        return t3Reg & 65280;
    case 15:
        return t3Reg & 255;
    case 16:
        return t4Reg & 65280;
    case 17:
        return t4Reg & 255;
    case 18:
        return t5Reg & 65280;
    case 19:
        return t5Reg & 255;
    case 20:
        return t6Reg & 65280;
    case 21:
        return t6Reg & 255;
    case 22:
        return m1Reg & 65280;
    case 23:
        return m1Reg & 255;
    case 24:
        return m2Reg & 65280;
    case 25:
        return m2Reg & 255;
    case 26:
        return m3Reg & 65280;
    case 27:
        return m3Reg & 255;
    case 28:
        return m4Reg & 65280;
    case 29:
        return m4Reg & 255;
    case 30:
        return m5Reg & 65280;
    case 31:
        return m5Reg & 255;
    default:
        break;
    }
    return 0;
}

void Sim::putRegByte(int reg, int value)
{
    switch (reg) {
    case 0:
        aReg &= 0x00FF;
        aReg |= (value % 256) * 256;
    case 1:
        aReg &= 0xFF00;
        aReg |= value % 256;
    case 2:
        xReg &= 0x00FF;
        xReg |= (value % 256) * 256;
    case 3:
        xReg &= 0xFF00;
        xReg |= value % 256;
    case 4:
        spReg &= 0x00FF;
        spReg |= (value % 256) * 256;
    case 5:
        spReg &= 0xFF00;
        spReg |= value % 256;
    case 6:
        pcReg &= 0x00FF;
        pcReg |= (value % 256) * 256;
    case 7:
        pcReg &= 0xFF00;
        pcReg |= value % 256;
    case 8:
        irReg &= 0x00FFFF;
        irReg |= (value % 256) * 65536;
    case 9:
        irReg &= 0xFF00FF;
        irReg |= (value % 256) * 256;
    case 10:
        irReg &= 0xFFFF00;
        irReg |= value % 256;
    case 11:
        t1Reg = value % 256;
    case 12:
        t2Reg &= 0x00FF;
        t2Reg |= (value % 256) * 256;
    case 13:
        t2Reg &= 0xFF00;
        t2Reg |= value % 256;
    case 14:
        t3Reg &= 0x00FF;
        t3Reg |= (value % 256) * 256;
    case 15:
        t3Reg &= 0xFF00;
        t3Reg |= value % 256;
    case 16:
        t4Reg &= 0x00FF;
        t4Reg |= (value % 256) * 256;
    case 17:
        t4Reg &= 0xFF00;
        t4Reg |= value % 256;
    case 18:
        t5Reg &= 0x00FF;
        t5Reg |= (value % 256) * 256;
    case 19:
        t5Reg &= 0xFF00;
        t5Reg |= value % 256;
    case 20:
        t6Reg &= 0x00FF;
        t6Reg |= (value % 256) * 256;
    case 21:
        t6Reg &= 0xFF00;
        t6Reg |= value % 256;
    default:
        // cannot store to ROM in M1 through M6, so do nothing
        break;
    }

}

bool Sim::advanceSimulation()
{

    return true;
}

bool Sim::atEndOfSim()
{
    return microCodeCurrentLine >= codeList.size() - 1;
}
