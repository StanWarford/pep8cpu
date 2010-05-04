#include "code.h"

void Microcode::setCPULabels(CpuPaneGraphicsItems *cpuGraphicsItems)
{
    cpuGraphicsItems->loadCk->setChecked(code.cLoadCk != -1);
    cpuGraphicsItems->cLineEdit->setText(code.cC == -1 ? "" : QString("%1").arg(code.cC));
    cpuGraphicsItems->bLineEdit->setText(code.cB == -1 ? "" : QString("%1").arg(code.cB));
    cpuGraphicsItems->aLineEdit->setText(code.cA == -1 ? "" : QString("%1").arg(code.cA));
    cpuGraphicsItems->MARCk->setChecked(code.cMARCk != -1);
    cpuGraphicsItems->MDRCk->setChecked(code.cMDRCk != -1);
    cpuGraphicsItems->aMuxTristateLabel->setState(code.cAMux);
    cpuGraphicsItems->MDRMuxTristateLabel->setState(code.cMDRMux);
    cpuGraphicsItems->cMuxTristateLabel->setState(code.cCMux);
    cpuGraphicsItems->ALULineEdit->setText(code.cALU == -1 ? "" : QString("%1").arg(code.cALU));
    cpuGraphicsItems->CCkCheckBox->setChecked(code.cCCk != -1);
    cpuGraphicsItems->VCkCheckBox->setChecked(code.cVCk != -1);
    cpuGraphicsItems->ANDZTristateLabel->setState(code.cANDZ);
    cpuGraphicsItems->ZCkCheckBox->setChecked(code.cZCk != -1);
    cpuGraphicsItems->NCkCheckBox->setChecked(code.cNCk != -1);
    cpuGraphicsItems->MemReadTristateLabel->setState(code.cMemRead);
    cpuGraphicsItems->MemWriteTristateLabel->setState(code.cMemWrite);
}

void Microcode::appendObjectCode(QTextEdit *textEdit)
{
    cpuGraphicsItems->loadCk->setChecked(code.cLoadCk != -1);
    cpuGraphicsItems->cLineEdit->setText(code.cC == -1 ? "" : QString("%1").arg(code.cC));
    cpuGraphicsItems->bLineEdit->setText(code.cB == -1 ? "" : QString("%1").arg(code.cB));
    cpuGraphicsItems->aLineEdit->setText(code.cA == -1 ? "" : QString("%1").arg(code.cA));
    cpuGraphicsItems->MARCk->setChecked(code.cMARCk != -1);
    cpuGraphicsItems->MDRCk->setChecked(code.cMDRCk != -1);
    cpuGraphicsItems->aMuxTristateLabel->setState(code.cAMux);
    cpuGraphicsItems->MDRMuxTristateLabel->setState(code.cMDRMux);
    cpuGraphicsItems->cMuxTristateLabel->setState(code.cCMux);
    cpuGraphicsItems->ALULineEdit->setText(code.cALU == -1 ? "" : QString("%1").arg(code.cALU));
    cpuGraphicsItems->CCkCheckBox->setChecked(code.cCCk != -1);
    cpuGraphicsItems->VCkCheckBox->setChecked(code.cVCk != -1);
    cpuGraphicsItems->ANDZTristateLabel->setState(code.cANDZ);
    cpuGraphicsItems->ZCkCheckBox->setChecked(code.cZCk != -1);
    cpuGraphicsItems->NCkCheckBox->setChecked(code.cNCk != -1);
    cpuGraphicsItems->MemReadTristateLabel->setState(code.cMemRead);
    cpuGraphicsItems->MemWriteTristateLabel->setState(code.cMemWrite);
}

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
