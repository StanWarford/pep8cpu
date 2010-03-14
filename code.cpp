#include "code.h"

Code::Code()
{
    clear();
}

void Code::clear()
{
    cLoadCk = -1;
    cC = -1;
    cB = -1;
    cA = -1;
    cMARCk = -1;
    cMDRCk = -1;
    cAMux = -1;
    cMDRMux = -1;
    cCMux = -1;
    cALU = -1;
    cCCk = -1;
    cVCk = -1;
    cANDZ = -1;
    cZCk = -1;
    cNCk = -1;
    cMemWrite = -1;
    cMemRead = -1;
    cComment = "";
}

bool Code::isEmpty()
{
    return cLoadCk == -1 &&
    cC == -1 &&
    cB == -1 &&
    cA == -1 &&
    cMARCk == -1 &&
    cMDRCk == -1 &&
    cAMux == -1 &&
    cMDRMux == -1 &&
    cCMux == -1 &&
    cALU == -1 &&
    cCCk == -1 &&
    cVCk == -1 &&
    cANDZ == -1 &&
    cZCk == -1 &&
    cNCk == -1 &&
    cMemWrite == -1 &&
    cMemRead == -1 &&
    cComment == "";
}

bool Code::isCommentOnly()
{
    return cLoadCk == -1 &&
    cC == -1 &&
    cB == -1 &&
    cA == -1 &&
    cMARCk == -1 &&
    cMDRCk == -1 &&
    cAMux == -1 &&
    cMDRMux == -1 &&
    cCMux == -1 &&
    cALU == -1 &&
    cCCk == -1 &&
    cVCk == -1 &&
    cANDZ == -1 &&
    cZCk == -1 &&
    cNCk == -1 &&
    cMemWrite == -1 &&
    cMemRead == -1 &&
    cComment != "";
}
