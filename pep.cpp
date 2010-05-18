#include "pep.h"
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>

using namespace Enu;

// Fonts
const QString Pep::codeFont = getSystem() == "Windows" ? "Courier" : (getSystem() == "Mac" ? "Courier" : "Courier 10 Pitch");
const int Pep::codeFontSize = getSystem() == "Mac" ? 11 : 9;
const QString Pep::labelFont = getSystem() == "Mac" ? "Lucida Grande" : "Verdana";
const int Pep::labelFontSize = getSystem() == "Mac" ? 11 : 8;
const QString Pep::cpuFont = getSystem() == "Mac" ? "Lucida Grande" : "Verdana";
const int Pep::cpuFontSize = getSystem() == "Mac" ? 11 : 8;

QString Pep::getSystem() {
    #ifdef Q_WS_X11
    return QString("Linux");
    #endif

    #ifdef Q_WS_MAC
    return QString("Mac");
    #endif

    #ifdef Q_WS_QWS
    return QString("Embedded Linux");
    #endif

    #ifdef Q_WS_WIN
    return QString("Windows");
    #endif
}

QString Pep::resToString(QString fileName) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString inString = "";
    while (!in.atEnd()) {
        QString line = in.readLine();
        inString.append(line + "\n");
    }

    QStringList microcodeList;
    microcodeList = inString.split('\n');
    for (int i = 0; i < microcodeList.size(); i++) {
        microcodeList[i].remove(QRegExp("^[0-9]+\\.?\\s*"));
    }
    inString = microcodeList.join("\n");

    return inString;
}

QMap<Enu::EMnemonic, QString> Pep::decControlToMnemonMap;
QMap<Enu::EMnemonic, QString> Pep::memControlToMnemonMap;
QMap<Enu::EMnemonic, QString> Pep::clockControlToMnemonMap;
QMap<Enu::EMnemonic, QString> Pep::specificationToMnemonMap;
QMap<Enu::EMnemonic, QString> Pep::memSpecToMnemonMap;
QMap<Enu::EMnemonic, QString> Pep::regSpecToMnemonMap;
QMap<Enu::EMnemonic, QString> Pep::statusSpecToMnemonMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToDecControlMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToMemControlMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToClockControlMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToSpecificationMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToMemSpecMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToRegSpecMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToStatusSpecMap;

void Pep::initEnumMnemonMaps()
{
    decControlToMnemonMap.insert(E_C, "C"); mnemonToDecControlMap.insert("C", E_C);
    decControlToMnemonMap.insert(E_B, "B"); mnemonToDecControlMap.insert("B", E_B);
    decControlToMnemonMap.insert(E_A, "A"); mnemonToDecControlMap.insert("A", E_A);
    decControlToMnemonMap.insert(E_ANDZ, "ANDZ"); mnemonToDecControlMap.insert("ANDZ", E_ANDZ);
    decControlToMnemonMap.insert(E_MDRMux, "MDRMux"); mnemonToDecControlMap.insert("MDRMUX", E_MDRMux);
    decControlToMnemonMap.insert(E_AMux, "AMux"); mnemonToDecControlMap.insert("AMUX", E_AMux);
    decControlToMnemonMap.insert(E_CMux, "CMux"); mnemonToDecControlMap.insert("CMUX", E_CMux);
    decControlToMnemonMap.insert(E_ALU, "ALU"); mnemonToDecControlMap.insert("ALU", E_ALU);
    decControlToMnemonMap.insert(E_ANDZ, "ANDZ"); mnemonToDecControlMap.insert("ANDZ", E_ANDZ);
    memControlToMnemonMap.insert(E_MemWrite, "MemWrite"); mnemonToMemControlMap.insert("MEMWRITE", E_MemWrite);
    memControlToMnemonMap.insert(E_MemRead, "MemRead"); mnemonToMemControlMap.insert("MEMREAD", E_MemRead);
    clockControlToMnemonMap.insert(E_LoadCk, "LoadCk"); mnemonToClockControlMap.insert("LOADCK", E_LoadCk);
    clockControlToMnemonMap.insert(E_MARCk, "MARCk"); mnemonToClockControlMap.insert("MARCK", E_MARCk);
    clockControlToMnemonMap.insert(E_MDRCk, "MDRCk"); mnemonToClockControlMap.insert("MDRCK", E_MDRCk);
    clockControlToMnemonMap.insert(E_CCk, "CCk"); mnemonToClockControlMap.insert("CCK", E_CCk);
    clockControlToMnemonMap.insert(E_VCk, "VCk"); mnemonToClockControlMap.insert("VCK", E_VCk);
    clockControlToMnemonMap.insert(E_ZCk, "ZCk"); mnemonToClockControlMap.insert("ZCK", E_ZCk);
    clockControlToMnemonMap.insert(E_NCk, "NCk"); mnemonToClockControlMap.insert("NCK", E_NCk);
    specificationToMnemonMap.insert(E_Pre, "UnitPre:"); mnemonToSpecificationMap.insert("UNITPRE:", E_Pre);
    specificationToMnemonMap.insert(E_Post, "UnitPost:"); mnemonToSpecificationMap.insert("UNITPOST:", E_Post);
    memSpecToMnemonMap.insert(E_Mem, "Mem"); mnemonToMemSpecMap.insert("MEM", E_Mem);
    regSpecToMnemonMap.insert(E_A, "A"); mnemonToRegSpecMap.insert("A", E_A);
    regSpecToMnemonMap.insert(E_X, "X"); mnemonToRegSpecMap.insert("X", E_X);
    regSpecToMnemonMap.insert(E_SP, "SP"); mnemonToRegSpecMap.insert("SP", E_SP);
    regSpecToMnemonMap.insert(E_PC, "PC"); mnemonToRegSpecMap.insert("PC", E_PC);
    regSpecToMnemonMap.insert(E_IR, "IR"); mnemonToRegSpecMap.insert("IR", E_IR);
    regSpecToMnemonMap.insert(E_T1, "T1"); mnemonToRegSpecMap.insert("T1", E_T1);
    regSpecToMnemonMap.insert(E_T2, "T2"); mnemonToRegSpecMap.insert("T2", E_T2);
    regSpecToMnemonMap.insert(E_T3, "T3"); mnemonToRegSpecMap.insert("T3", E_T3);
    regSpecToMnemonMap.insert(E_T4, "T4"); mnemonToRegSpecMap.insert("T4", E_T4);
    regSpecToMnemonMap.insert(E_T5, "T5"); mnemonToRegSpecMap.insert("T5", E_T5);
    regSpecToMnemonMap.insert(E_T6, "T6"); mnemonToRegSpecMap.insert("T6", E_T6);
    statusSpecToMnemonMap.insert(E_N, "N"); mnemonToStatusSpecMap.insert("N", E_N);
    statusSpecToMnemonMap.insert(E_Z, "Z"); mnemonToStatusSpecMap.insert("Z", E_Z);
    statusSpecToMnemonMap.insert(E_V, "V"); mnemonToStatusSpecMap.insert("V", E_V);
    statusSpecToMnemonMap.insert(E_C, "C"); mnemonToStatusSpecMap.insert("C", E_C);
}
