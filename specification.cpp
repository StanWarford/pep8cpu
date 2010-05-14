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

RegSpecification::RegSpecification(int registerAddress, int registerValue) {
    regAddress = registerAddress;
    regValue = registerValue;
}

void RegSpecification::setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane) {

}

void RegSpecification::testPostcondition() {

}

StatusBitSpecification::StatusBitSpecification(int statusBitAddress, bool statusBitValue) {
    nzvcAddress = statusBitAddress;
    nzvcValue = statusBitValue;
}

void StatusBitSpecification::setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane) {

}

void StatusBitSpecification::testPostcondition() {

}

