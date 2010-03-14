#ifndef CODE_H
#define CODE_H

#include <QString>

#include "pep.h"

class Code
{
    friend class Asm;
public:
    virtual ~Code() { }
    Code();
    void clear();
    bool isEmpty();
    bool isCommentOnly();

protected:
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

#endif // CODE_H
