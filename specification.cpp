#include "specification.h"

Specification::Specification()
{
}

MemSpecification::MemSpecification(int memoryAddress, int memoryValue) {
    memAddress = memoryAddress;
    memValue = memoryValue;
}

void MemSpecification::setPrecondition(MainMemory *mainMemory, CpuPane *) {
    mainMemory->setMemPrecondition(memAddress, memValue);
}

bool MemSpecification::testPostcondition(MainMemory *mainMemory, CpuPane *, QString &errorString) {
    if (mainMemory->testMemPostcondition(memAddress, memValue)) {
        return true;
    }
    errorString = "// Error: Unit test failed for Mem[." + QString("0x%1").arg(memAddress, 4, 16, QLatin1Char('0')) + "].";
    return false;
}

QString MemSpecification::getSourceCode() {
    QString retVal = "Mem["
                     + QString("0x%1").arg(memAddress, 4, 16, QLatin1Char('0'))
                     + "]="
                     + QString("0x%1").arg(memValue, 4, 16, QLatin1Char('0'));
    return retVal;
}

RegSpecification::RegSpecification(Enu::EMnemonic registerAddress, int registerValue) {
    regAddress = registerAddress;
    regValue = registerValue;
}

void RegSpecification::setPrecondition(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setRegPrecondition(regAddress, regValue);
}

bool RegSpecification::testPostcondition(MainMemory *, CpuPane *cpuPane, QString &errorString) {
    if (cpuPane->testRegPostcondition(regAddress, regValue)) {
        return true;
    }
    switch (regAddress) {
    case Enu::E_A: errorString = "// Error: Unit test failed for register A."; return false;
    case Enu::E_X: errorString = "// Error: Unit test failed for register X."; return false;
    case Enu::E_SP: errorString = "// Error: Unit test failed for register SP."; return false;
    case Enu::E_PC: errorString = "// Error: Unit test failed for register PC."; return false;
    case Enu::E_IR: errorString = "// Error: Unit test failed for register IR."; return false;
    case Enu::E_T1: errorString = "// Error: Unit test failed for register T1."; return false;
    case Enu::E_T2: errorString = "// Error: Unit test failed for register T2."; return false;
    case Enu::E_T3: errorString = "// Error: Unit test failed for register T3."; return false;
    case Enu::E_T4: errorString = "// Error: Unit test failed for register T4."; return false;
    case Enu::E_T5: errorString = "// Error: Unit test failed for register T5."; return false;
    case Enu::E_T6: errorString = "// Error: Unit test failed for register T6."; return false;
    default: return false;
    }
}

QString RegSpecification::getSourceCode() {
    switch (regAddress) {
    case Enu::E_A: return "A=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_X: return "X=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_SP: return "SP=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_PC: return "PC=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_IR: return "IR=" + QString("0x%1").arg(regValue, 6, 16, QLatin1Char('0'));
    case Enu::E_T1: return "T1=" + QString("0x%1").arg(regValue, 2, 16, QLatin1Char('0'));
    case Enu::E_T2: return "T2=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_T3: return "T3=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_T4: return "T4=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_T5: return "T5=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    case Enu::E_T6: return "T6=" + QString("0x%1").arg(regValue, 4, 16, QLatin1Char('0'));
    default: return "";
    }
}

StatusBitSpecification::StatusBitSpecification(Enu::EMnemonic statusBitAddress, bool statusBitValue) {
    nzvcAddress = statusBitAddress;
    nzvcValue = statusBitValue;
}

void StatusBitSpecification::setPrecondition(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setStatusPrecondition(nzvcAddress, nzvcValue);
}

bool StatusBitSpecification::testPostcondition(MainMemory *, CpuPane *cpuPane, QString &errorString) {
    if (cpuPane->testStatusPostcondition(nzvcAddress, nzvcValue)) {
        return true;
    }
    switch (nzvcValue) {
    case Enu::E_N: errorString = "// Error: Unit test failed for status bit N."; return false;
    case Enu::E_Z: errorString = "// Error: Unit test failed for status bit Z."; return false;
    case Enu::E_V: errorString = "// Error: Unit test failed for status bit V."; return false;
    case Enu::E_C: errorString = "// Error: Unit test failed for status bit C."; return false;
    default: return false;
    }
}

QString StatusBitSpecification::getSourceCode() {
    switch (nzvcAddress) {
    case Enu::E_N: return "N=" + QString("%1").arg(nzvcValue);
    case Enu::E_Z: return "Z=" + QString("%1").arg(nzvcValue);
    case Enu::E_V: return "V=" + QString("%1").arg(nzvcValue);
    case Enu::E_C: return "C=" + QString("%1").arg(nzvcValue);
    default: return "";
    }
}
