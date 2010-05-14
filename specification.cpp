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

bool MemSpecification::testPostcondition(MainMemory *mainMemory, CpuPane *) {
    return mainMemory->testMemPostcondition(memAddress, memValue);
}

RegSpecification::RegSpecification(Enu::EMnemonic registerAddress, int registerValue) {
    regAddress = registerAddress;
    regValue = registerValue;
}

void RegSpecification::setPrecondition(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setRegPrecondition(regAddress, regValue);
}

bool RegSpecification::testPostcondition(MainMemory *, CpuPane *cpuPane) {
    return cpuPane->testRegPostcondition(regAddress, regValue);
}

StatusBitSpecification::StatusBitSpecification(Enu::EMnemonic statusBitAddress, bool statusBitValue) {
    nzvcAddress = statusBitAddress;
    nzvcValue = statusBitValue;
}

void StatusBitSpecification::setPrecondition(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setStatusPrecondition(nzvcAddress, nzvcValue);
}

bool StatusBitSpecification::testPostcondition(MainMemory *, CpuPane *cpuPane) {
    return cpuPane->testStatusPostcondition(nzvcAddress, nzvcValue);
}

