#ifndef SPECIFICATION_H
#define SPECIFICATION_H

class Specification
{
public:
    virtual ~Specification() { }
    Specification();
    virtual void setPrecondition() { }
    virtual void testPostcondition() { }
protected:
    int specValue;
};

class MemSpecification: public Specification {
public:
    MemSpecification(int memoryAddress, int specificationValue);
    void setPrecondition();
    void testPostcondition();
private:
    int memAddress;
};

class RegSpecification: public Specification {
public:
    RegSpecification(int registerAddress, int specificationValue);
    void setPrecondition();
    void testPostcondition();
private:
    int regAddress;
};

class StatusBitSpecification: public Specification {
public:
    StatusBitSpecification(int statusBitAddress, int specificationValue);
    void setPrecondition();
    void testPostcondition();
private:
    int nzvcAddress;
};


#endif // SPECIFICATION_H
