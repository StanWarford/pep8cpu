#include "specification.h"

Specification::Specification()
{
}

MemSpecification::MemSpecification(int memoryAddress, int specificationValue) {
    memAddress = memoryAddress;
    specValue = specificationValue;
}

void MemSpecification::setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane) {
    
}

void MemSpecification::testPostcondition() {
    
}

RegSpecification::RegSpecification(int registerAddress, int specificationValue) {
    regAddress = registerAddress;
    specValue = specificationValue;
}

void RegSpecification::setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane) {

}

void RegSpecification::testPostcondition() {

}

StatusBitSpecification::StatusBitSpecification(int statusBitAddress, int specificationValue) {
    nzvcAddress = statusBitAddress;
    specValue = specificationValue;
}

void StatusBitSpecification::setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane) {

}

void StatusBitSpecification::testPostcondition() {

}

