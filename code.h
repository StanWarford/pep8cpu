#ifndef CODE_H
#define CODE_H

#include <QString>
#include <QTextEdit>

#include "pep.h"
#include "enu.h"
#include "cpupanegraphicsitems.h"
#include "specification.h"

// Abstract code class
class Code
{
    friend class MicrocodePane;
    friend class CpuPane;
public:
    virtual ~Code() { }
    virtual bool isMicrocode() { return false; }
    virtual void setCpuLabels(CpuPaneGraphicsItems *) { }
    virtual QString getObjectCode() { return ""; }
    virtual QString getSourceCode() { return ""; }
    virtual void setPrecondition() { }
    virtual void testPostcondition() { }
};

// Concrete code classes
class MicroCode: public Code
{
    friend class Asm;
public:
    MicroCode();
    bool MicroCode::isMicrocode();
    void MicroCode::setCpuLabels(CpuPaneGraphicsItems *cpuPaneItems);
    QString getObjectCode();
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
private:
    QString cComment;
};

class PreconditionCode: public Code
{
public:
    ~PreconditionCode();
    void setPrecondition();
private:
    QList<Specification *> preconditionList;
};

class PostconditionCode: public Code
{
public:
    ~PostconditionCode();
    void testPostcondition();
private:
    QList<Specification *> postconditionList;
};

class BlankLineCode: public Code
{

};

#endif // CODE_H
