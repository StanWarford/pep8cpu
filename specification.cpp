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
    return mainMemory->testMemPostcondition(memAddress, memValue);
}

RegSpecification::RegSpecification(Enu::EMnemonic registerAddress, int registerValue) {
    regAddress = registerAddress;
    regValue = registerValue;
}

void RegSpecification::setPrecondition(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setRegPrecondition(regAddress, regValue);
}

bool RegSpecification::testPostcondition(MainMemory *, CpuPane *cpuPane, QString &errorString) {
//    if (cpuPane->testStatusPostcondition(nzvcAddress, nzvcValue)) {
//        return true;
//    }
//    switch (nzvcValue) {
//    case Enu::N: errorString = "// Error: Unit test failed for status bit N."; return false;
//    case Enu::Z: errorString = "// Error: Unit test failed for status bit Z."; return false;
//    case Enu::V: errorString = "// Error: Unit test failed for status bit V."; return false;
//    case Enu::C: errorString = "// Error: Unit test failed for status bit C."; return false;
//    default: return false;
//    }
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
    case Enu::N: errorString = "// Error: Unit test failed for status bit N."; return false;
    case Enu::Z: errorString = "// Error: Unit test failed for status bit Z."; return false;
    case Enu::V: errorString = "// Error: Unit test failed for status bit V."; return false;
    case Enu::C: errorString = "// Error: Unit test failed for status bit C."; return false;
    default: return false;
    }
}

