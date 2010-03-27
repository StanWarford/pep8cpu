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

bool Code::has(Enu::EMnemonic field) {
    switch (field) {
    case Enu::E_LoadCk: return cLoadCk != -1;
    case Enu::E_C: return cC != -1;
    case Enu::E_B: return cB != -1;
    case Enu::E_A: return cA != -1;
    case Enu::E_MARCk: return cMARCk != -1;
    case Enu::E_MDRCk: return cMDRCk != -1;
    case Enu::E_AMux: return cAMux != -1;
    case Enu::E_MDRMux: return cMDRMux != -1;
    case Enu::E_CMux: return cCMux != -1;
    case Enu::E_ALU: return cALU != -1;
    case Enu::E_CCk: return cCCk != -1;
    case Enu::E_VCk: return cVCk != -1;
    case Enu::E_ANDZ: return cANDZ != -1;
    case Enu::E_ZCk: return cZCk != -1;
    case Enu::E_NCk: return cNCk != -1;
    case Enu::E_MemWrite: return cMemWrite != -1;
    case Enu::E_MemRead: return cMemRead != -1;
    default: return true;
    }
}

void Code::set(Enu::EMnemonic field, int value) {
    switch (field) {
    case Enu::E_LoadCk: cLoadCk = value;
    case Enu::E_C: cC = value;
    case Enu::E_B: cB = value;
    case Enu::E_A: cA = value;
    case Enu::E_MARCk: cMARCk = value;
    case Enu::E_MDRCk: cMDRCk = value;
    case Enu::E_AMux: cAMux = value;
    case Enu::E_MDRMux: cMDRMux = value;
    case Enu::E_CMux: cCMux = value;
    case Enu::E_ALU: cALU = value;
    case Enu::E_CCk: cCCk = value;
    case Enu::E_VCk: cVCk = value;
    case Enu::E_ANDZ: cANDZ = value;
    case Enu::E_ZCk: cZCk = value;
    case Enu::E_NCk: cNCk = value;
    case Enu::E_MemWrite: cMemWrite = value;
    case Enu::E_MemRead: cMemRead = value;
    }
}

bool Code::inRange(Enu::EMnemonic field, int value) {
    switch (field) {
    case Enu::E_C: return 0 <= value && value <= 31;
    case Enu::E_B: return 0 <= value && value <= 31;
    case Enu::E_A: return 0 <= value && value <= 31;
    case Enu::E_AMux: return 0 <= value && value <= 1;
    case Enu::E_MDRMux: return 0 <= value && value <= 1;
    case Enu::E_CMux: return 0 <= value && value <= 1;
    case Enu::E_ALU: return 0 <= value && value <= 15;
    case Enu::E_ANDZ: return 0 <= value && value <= 1;
    default: return true;
    }
}
