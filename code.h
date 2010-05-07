#ifndef CODE_H
#define CODE_H

#include <QString>
#include <QTextEdit>

#include "pep.h"
#include "enu.h"
#include "cpupanegraphicsitems.h"
#include "precondition.h"
#include "postcondition.h"

// Abstract code class
class Code
{
    friend class Asm;
    friend class MicrocodePane;
    friend class CpuPane;
public:
    virtual ~Code() { }
    virtual void clear() { }
    virtual bool isMicrocode() { return false; }
    virtual void setCpuLabels(CpuPaneGraphicsItems *cpuPaneItems) { }
    virtual QString getObjectCode() { return ""; }
    virtual QString getSourceCode() { return ""; }
    virtual void setPrecondition() { }
    virtual void testPostcondition() { }
};

// Concrete code classes
class Microcode: public Code
{
    friend class Asm;
public:
    void clear();
    bool Microcode::isMicrocode();
    void Microcode::setCpuLabels(CpuPaneGraphicsItems *cpuPaneItems);
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

class CommentOnly: public Code
{
    friend class Asm;
public:
    void clear();
private:
    QString cComment;
};

class PreconditionCode: public Code
{
    friend class Asm;
public:
    void clear();
private:
    QList<Precondition> preconditionList;
};

class PostconditionCode: public Code
{
    friend class Asm;
public:
    void clear();
private:
    QList<Postcondition> postconditionList;
};

class BlankLine: public Code
{

};

#endif // CODE_H
