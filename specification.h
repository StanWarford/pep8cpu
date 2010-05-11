#ifndef SPECIFICATION_H
#define SPECIFICATION_H

class Specification
{
public:
    virtual ~Specification() { }
    Specification();
    virtual void setPrecondition() { }
    virtual void testPostcondition() { }
private:
    int specValue;
};

class MemSpecification: public Specification {
public:
    void setPrecondition();
    void testPostcondition();
private:
    int memAddress;
};

class RegSpecification: public Specification {
private:
    int regAddress;
};

class StatusBitSpecification: public Specification {
private:
    int nzvcAddress;
};


#endif // SPECIFICATION_H
