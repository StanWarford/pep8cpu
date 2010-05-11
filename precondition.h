#ifndef PRECONDITION_H
#define PRECONDITION_H

class Precondition
{
public:
    Precondition();
};

class MemPrecondition: Precondition
{
private:
    int memAddress;
};

class RegPrecondition: Precondition
{
private:
    int regAddress;
};

class StatusBitPrecondition: Precondition
{
private:
    int statusBitAddress;
};

#endif // PRECONDITION_H
