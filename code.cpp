#include "code.h"

MicroCode::MicroCode()
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

bool MicroCode::isMicrocode() { return true; }

void MicroCode::setCpuLabels(CpuPaneGraphicsItems *cpuPaneItems)
{
    cpuPaneItems->loadCk->setChecked(cLoadCk != -1);
    cpuPaneItems->cLineEdit->setText(cC == -1 ? "" : QString("%1").arg(cC));
    cpuPaneItems->bLineEdit->setText(cB == -1 ? "" : QString("%1").arg(cB));
    cpuPaneItems->aLineEdit->setText(cA == -1 ? "" : QString("%1").arg(cA));
    cpuPaneItems->MARCk->setChecked(cMARCk != -1);
    cpuPaneItems->MDRCk->setChecked(cMDRCk != -1);
    cpuPaneItems->aMuxTristateLabel->setState(cAMux);
    cpuPaneItems->MDRMuxTristateLabel->setState(cMDRMux);
    cpuPaneItems->cMuxTristateLabel->setState(cCMux);
    cpuPaneItems->ALULineEdit->setText(cALU == -1 ? "" : QString("%1").arg(cALU));
    cpuPaneItems->CCkCheckBox->setChecked(cCCk != -1);
    cpuPaneItems->VCkCheckBox->setChecked(cVCk != -1);
    cpuPaneItems->ANDZTristateLabel->setState(cANDZ);
    cpuPaneItems->ZCkCheckBox->setChecked(cZCk != -1);
    cpuPaneItems->NCkCheckBox->setChecked(cNCk != -1);
    cpuPaneItems->MemReadTristateLabel->setState(cMemRead);
    cpuPaneItems->MemWriteTristateLabel->setState(cMemWrite);
}

QString MicroCode::getObjectCode()
{
    QString str = "";
    str.append(cLoadCk == -1 ? "  " : QString("%1").arg(cLoadCk, -2));
    str.append(cC == -1 ? "   " : QString("%1").arg(cC, -3));
    str.append(cB == -1 ? "   " : QString("%1").arg(cB, -3));
    str.append(cA == -1 ? "   " : QString("%1").arg(cA, -3));
    str.append(cMARCk == -1 ? "  " : QString("%1").arg(cMARCk, -2));
    str.append(cMDRCk == -1 ? "  " : QString("%1").arg(cMDRCk, -2));
    str.append(cAMux == -1 ? "  " : QString("%1").arg(cAMux, -2));
    str.append(cMDRMux == -1 ? "  " : QString("%1").arg(cMDRMux, -2));
    str.append(cCMux == -1 ? "  " : QString("%1").arg(cCMux, -2));
    str.append(cALU == -1 ? "   " : QString("%1").arg(cALU, -3));
    str.append(cCCk == -1 ? "  " : QString("%1").arg(cCCk, -2));
    str.append(cVCk == -1 ? "  " : QString("%1").arg(cVCk, -2));
    str.append(cANDZ == -1 ? "  " : QString("%1").arg(cANDZ, -2));
    str.append(cZCk == -1 ? "  " : QString("%1").arg(cZCk, -2));
    str.append(cNCk == -1 ? "  " : QString("%1").arg(cNCk, -2));
    str.append(cMemWrite == -1 ? "  " : QString("%1").arg(cMemWrite, -2));
    str.append(cMemRead == -1 ? "  " : QString("%1").arg(cMemRead, -2));
    str.append("\n");
    return str;
}

bool MicroCode::has(Enu::EMnemonic field) {
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

void MicroCode::set(Enu::EMnemonic field, int value) {
    switch (field) {
    case Enu::E_LoadCk: cLoadCk = value; break;
    case Enu::E_C: cC = value; break;
    case Enu::E_B: cB = value; break;
    case Enu::E_A: cA = value; break;
    case Enu::E_MARCk: cMARCk = value; break;
    case Enu::E_MDRCk: cMDRCk = value; break;
    case Enu::E_AMux: cAMux = value; break;
    case Enu::E_MDRMux: cMDRMux = value; break;
    case Enu::E_CMux: cCMux = value; break;
    case Enu::E_ALU: cALU = value; break;
    case Enu::E_CCk: cCCk = value; break;
    case Enu::E_VCk: cVCk = value; break;
    case Enu::E_ANDZ: cANDZ = value; break;
    case Enu::E_ZCk: cZCk = value; break;
    case Enu::E_NCk: cNCk = value; break;
    case Enu::E_MemWrite: cMemWrite = value; break;
    case Enu::E_MemRead: cMemRead = value; break;
    }
}

bool MicroCode::inRange(Enu::EMnemonic field, int value) {
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

CommentOnlyCode::CommentOnlyCode(QString comment)
{
    cComment = comment;
}
