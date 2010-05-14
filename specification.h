#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include "mainmemory.h"
#include "cpupane.h"

class Specification
{
public:
    virtual ~Specification() { }
    Specification();
    virtual void setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane) { }
    virtual void testPostcondition() { }
protected:
    int specValue;
};

class MemSpecification: public Specification {    
public:
    MemSpecification(int memoryAddress, int specificationValue);
    void setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane);
    void testPostcondition();
private:
    int memAddress;
};

class RegSpecification: public Specification {
public:
    RegSpecification(int registerAddress, int specificationValue);
    void setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane);
    void testPostcondition();
private:
    int regAddress;
};

class StatusBitSpecification: public Specification {
public:
    StatusBitSpecification(int statusBitAddress, int specificationValue);
    void setPrecondition(MainMemory *mainMemory, CpuPane *cpuPane);
    void testPostcondition();
private:
    int nzvcAddress;
};


#endif // SPECIFICATION_H
