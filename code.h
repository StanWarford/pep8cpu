#ifndef CODE_H
#define CODE_H

#include <QString>
#include <QTextEdit>

#include "enu.h"
#include "specification.h"
#include "mainmemory.h"
#include "cpupane.h"

// Abstract code class
class Code
{
public:
    virtual ~Code() { }
    virtual bool isMicrocode() { return false; }
    virtual void setCpuLabels(CpuPaneGraphicsItems *) { }
    virtual QString getObjectCode() { return ""; }
    virtual QString getSourceCode() { return ""; }
    virtual bool hasUnitPre() { return false; }
    virtual void setUnitPre(MainMemory *, CpuPane *) { }
    virtual bool testPostcondition(MainMemory *, CpuPane *, QString &) { return true; }
};

// Concrete code classes
class MicroCode: public Code
{
    friend class Asm;
public:
    MicroCode();
    bool isMicrocode();
    void setCpuLabels(CpuPaneGraphicsItems *cpuPaneItems);
    QString getObjectCode();
    QString getSourceCode();
    bool has(Enu::EMnemonic field);
    void set(Enu::EMnemonic field, int value);
    bool inRange(Enu::EMnemonic field, int value);
private:
    int cLoadCk;
    int cC;
    int cB;
    int cA;
    int cMARCk;
    int cMDRCk;
    int cAMux;
    int cMDRMux;
    int cCMux;
    int cALU;
    int cCCk;
    int cVCk;
    int cANDZ;
    int cZCk;
    int cNCk;
    int cMemWrite;
    int cMemRead;
    QString cComment;
};

class CommentOnlyCode: public Code
{
public:
    CommentOnlyCode(QString comment);
    QString getSourceCode();
private:
    QString cComment;
};

class UnitPreCode: public Code
{
public:
    ~UnitPreCode();
    QString getSourceCode();
    bool hasUnitPre();
    void setUnitPre(MainMemory *mainMemory, CpuPane *cpuPane);
    void appendSpecification(Specification *specification);
    void setComment(QString comment);
private:
    QList<Specification *> unitPreList;
    QString cComment;
};

class UnitPostCode: public Code
{
public:
    ~UnitPostCode();
    QString getSourceCode();
    bool testPostcondition(MainMemory *mainMemory, CpuPane *cpuPane, QString &errorString);
    void appendSpecification(Specification *specification);
    void setComment(QString comment);
private:
    QList<Specification *> unitPostList;
    QString cComment;
};

class BlankLineCode: public Code
{
};

#endif // CODE_H
