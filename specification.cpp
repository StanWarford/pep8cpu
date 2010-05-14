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

void MemSpecification::testPostcondition() {
    
}

RegSpecification::RegSpecification(Enu::EMnemonic registerAddress, int registerValue) {
    regAddress = registerAddress;
    regValue = registerValue;
}

void RegSpecification::setPrecondition(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setRegPrecondition(regAddress, regValue);
}

void RegSpecification::testPostcondition() {

}

StatusBitSpecification::StatusBitSpecification(Enu::EMnemonic statusBitAddress, bool statusBitValue) {
    nzvcAddress = statusBitAddress;
    nzvcValue = statusBitValue;
}

void StatusBitSpecification::setPrecondition(MainMemory *, CpuPane *cpuPane) {
    cpuPane->setStatusPrecondition(nzvcAddress, nzvcValue);
}

void StatusBitSpecification::testPostcondition() {

}

