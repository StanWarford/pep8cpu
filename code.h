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
    virtual void setCPULabels(CpuPaneGraphicsItems *cpuGraphicsItems) { }
    virtual void appendObjectCode(QTextEdit *textEdit) { }
    virtual void setPrecondition() { }
    virtual void setPostcondition() { }
    virtual bool isMicrocode() = 0;
    bool has(Enu::EMnemonic field);
    void set(Enu::EMnemonic field, int value);
    bool inRange(Enu::EMnemonic field, int value);

private:
};

// Concrete code classes
class Microcode: public Code
{
    friend class Asm;
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
public:
    void appendObjectCode(QTextEdit *textEdit) { }
    bool isMicrocode() {return true;}
};

class CommentOnly: public Code
{
    friend class Asm;
private:
    QString cComment;
public:
    void setCPULabels(CpuPaneGraphicsItems *cpuGraphicsItems) { }
    void appendObjectCode(QTextEdit *textEdit) { }
    bool isMicrocode() {return false;}
};

class PreconditionCode: public Code
{
    friend class Asm;
private:
    QList<Precondition> preconditionList;
public:
    void setCPULabels(CpuPaneGraphicsItems *cpuGraphicsItems) { }
    void appendObjectCode(QTextEdit *textEdit) { }
    bool isMicrocode() {return false;}
};

class PostconditionCode: public Code
{
    friend class Asm;
private:
    QList<Postcondition> postconditionList;
public:
    void setCPULabels(CpuPaneGraphicsItems *cpuGraphicsItems) { }
    void appendObjectCode(QTextEdit *textEdit) { }
    bool isMicrocode() {return false;}
};

class BlankLine: public Code
{
    friend class Asm;
public:
    void setCPULabels(CpuPaneGraphicsItems *cpuGraphicsItems) { }
    void appendObjectCode(QTextEdit *textEdit) { }
    bool isMicrocode() {return false;}
};

#endif // CODE_H
