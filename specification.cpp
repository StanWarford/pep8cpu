#include "specification.h"
#include <QDebug>

Specification::Specification()
{
}

MemSpecification::MemSpecification(int memoryAddress, int memoryValue, int numberBytes) {
    memAddress = memoryAddress;
    memValue = memoryValue;
    numBytes = numberBytes;
}

void MemSpecification::setUnitPre(MainMemory *mainMemory, CpuPane *) {
    if (numBytes == 1) {
        mainMemory->setMemPrecondition(memAddress, memValue);
    }
    else { // numBytes == 2
        mainMemory->setMemPrecondition(memAddress, memValue / 256);
        mainMemory->setMemPrecondition(memAddress + 1, memValue % 256);
    }
}

bool MemSpecification::testUnitPost(MainMemory *mainMemory, CpuPane *, QString &errorString) {
    if (numBytes == 1) {
        if (mainMemory->testMemPostcondition(memAddress, memValue)) {
            return true;
        }
        errorString = "// ERROR: Unit test failed for byte Mem[." + QString("0x%1").arg(memAddress, 4, 16, QLatin1Char('0')) + "].";
        return false;
    }
    else { // numBytes == 2
        if ((mainMemory->testMemPostcondition(memAddress, memValue) / 256) && (mainMemory->testMemPostcondition(memAddress + 1, memValue) % 256)) {
            return true;
        }
        errorString = "// ERROR: Unit test failed for word Mem[." + QString("0x%1").arg(memAddress, 4, 16, QLatin1Char('0')) + "].";
        return false;
    }
}

QString MemSpecification::getSourceCode() {
    return "Mem["
            + QString("0x%1").arg(memAddress, 4, 16, QLatin1Char('0'))
            + "]="
            + (numBytes == 1 ?
               QString("0x%1").arg(memValue, 2, 16, QLatin1Char('0')) :
               QString("0x%1").arg(memValue, 4, 16, QLatin1Char('0'))) ;
}

RegSpecification::RegSpecification(Enu::EMnemonic registerAddress, int registerValue) {
    regAddress = registerAddress;
    regValue = registerValue;
}

void RegSpecification::setUnitPre(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setRegPrecondition(regAddress, regValue);
}

bool RegSpecification::testUnitPost(MainMemory *, CpuPane *cpuPane, QString &errorString) {
    if (cpuPane->testRegPostcondition(regAddress, regValue)) {
        return true;
    }
    switch (regAddress) {
    case Enu::A: errorString = "// ERROR: Unit test failed for register A."; return false;
    case Enu::X: errorString = "// ERROR: Unit test failed for register X."; return false;
    case Enu::SP: errorString = "// ERROR: Unit test failed for register SP."; return false;
    case Enu::PC: errorString = "// ERROR: Unit test failed for register PC."; return false;
    case Enu::IR: errorString = "// ERROR: Unit test failed for register IR."; return false;
    case Enu::T1: errorString = "// ERROR: Unit test failed for register T1."; return false;
    case Enu::T2: errorString = "// ERROR: Unit test failed for register T2."; return false;
    case Enu::T3: errorString = "// ERROR: Unit test failed for register T3."; return false;
    case Enu::T4: errorString = "// ERROR: Unit test failed for register T4."; return false;
    case Enu::T5: errorString = "// ERROR: Unit test failed for register T5."; return false;
    case Enu::T6: errorString = "// ERROR: Unit test failed for register T6."; return false;
    case Enu::MARA: errorString = "// ERROR: Unit test failed for MARA."; return false;
    case Enu::MARB: errorString = "// ERROR: Unit test failed for MARB."; return false;
    case Enu::MDR: errorString = "// ERROR: Unit test failed for MDR."; return false;
    default: return false;
    }
}

QString RegSpecification::getSourceCode() {
    switch (regAddress) {
    case Enu::A: return "A=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::X: return "X=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::SP: return "SP=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::PC: return "PC=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::IR: return "IR=" + QString("0x%1").arg(regValue, 6, 16, QLatin1Char('0'));
    case Enu::T1: return "T1=" + QString("0x%1").arg(regValue, 2, 16, QLatin1Char('0'));
    case Enu::T2: return "T2=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::T3: return "T3=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::T4: return "T4=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::T5: return "T5=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::T6: return "T6=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::MARA: return "MARA=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::MARB: return "MARB=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::MDR: return "MDR=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    default: return "";
    }
}

StatusBitSpecification::StatusBitSpecification(Enu::EMnemonic statusBitAddress, bool statusBitValue) {
    nzvcAddress = statusBitAddress;
    nzvcValue = statusBitValue;
}

void StatusBitSpecification::setUnitPre(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setStatusPrecondition(nzvcAddress, nzvcValue);
}

bool StatusBitSpecification::testUnitPost(MainMemory *, CpuPane *cpuPane, QString &errorString) {
    if (cpuPane->testStatusPostcondition(nzvcAddress, nzvcValue)) {
        return true;
    }
    switch (nzvcAddress) {
    case Enu::N: errorString = "// ERROR: Unit test failed for status bit N."; return false;
    case Enu::Z: errorString = "// ERROR: Unit test failed for status bit Z."; return false;
    case Enu::V: errorString = "// ERROR: Unit test failed for status bit V."; return false;
    case Enu::C: errorString = "// ERROR: Unit test failed for status bit C."; return false;
    default: return false;
    }
}

QString StatusBitSpecification::getSourceCode() {
    switch (nzvcAddress) {
    case Enu::N: return "N=" + QString("%1").arg(nzvcValue);
    case Enu::Z: return "Z=" + QString("%1").arg(nzvcValue);
    case Enu::V: return "V=" + QString("%1").arg(nzvcValue);
    case Enu::C: return "C=" + QString("%1").arg(nzvcValue);
    default: return "";
    }
}
