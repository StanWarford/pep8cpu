#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include "mainmemory.h"
#include "cpupane.h"

class Specification
{
public:
    virtual ~Specification() { }
    Specification();
    virtual void setUnitPre(MainMemory *, CpuPane *) { }
    virtual bool testUnitPost(MainMemory *, CpuPane *, QString &) { return true; }
    virtual QString getSourceCode() = 0;
};

class MemSpecification: public Specification {    
public:
    MemSpecification(int memoryAddress, int memoryValue);
    void setUnitPre(MainMemory *mainMemory, CpuPane *cpuPane);
    bool testUnitPost(MainMemory *mainMemory, CpuPane *cpuPane, QString &errorString);
    QString getSourceCode();
private:
    int memAddress;
    int memValue;
};

class RegSpecification: public Specification {
public:
    RegSpecification(Enu::EMnemonic registerAddress, int registerValue);
    void setUnitPre(MainMemory *mainMemory, CpuPane *cpuPane);
    bool testUnitPost(MainMemory *mainMemory, CpuPane *cpuPane, QString &errorString);
    QString getSourceCode();
private:
    Enu::EMnemonic regAddress;
    int regValue;
};

class StatusBitSpecification: public Specification {
public:
    StatusBitSpecification(Enu::EMnemonic statusBitAddress, bool statusBitValue);
    void setUnitPre(MainMemory *mainMemory, CpuPane *cpuPane);
    bool testUnitPost(MainMemory *mainMemory, CpuPane *cpuPane, QString &errorString);
    QString getSourceCode();
private:
    Enu::EMnemonic nzvcAddress;
    bool nzvcValue;
};

#endif // SPECIFICATION_H
