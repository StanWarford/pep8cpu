#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include "mainmemory.h"
#include "cpupane.h"

class Specification
{
public:
    virtual ~Specification() { }
    Specification();
    virtual void setPrecondition(MainMemory *, CpuPane *) { }
    virtual void testPostcondition() { }
};

class MemSpecification: public Specification {    
public:
    MemSpecification(int memoryAddress, int memoryValue);
    void setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane);
    void testPostcondition();
private:
    int memAddress;
    int memValue;
};

class RegSpecification: public Specification {
public:
    RegSpecification(int registerAddress, int registerValue);
    void setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane);
    void testPostcondition();
private:
    int regAddress;
    int regValue;
};

class StatusBitSpecification: public Specification {
public:
    StatusBitSpecification(int statusBitAddress, bool statusBitValue);
    void setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane);
    void testPostcondition();
private:
    int nzvcAddress;
    bool nzvcValue;
};

#endif // SPECIFICATION_H
