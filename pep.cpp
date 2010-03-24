#include "pep.h"
#include <QFile>
#include <QDebug>
#include <QString>

using namespace Enu;

// Fonts
const QString Pep::codeFont = getSystem() == "Windows" ? "Courier" : (getSystem() == "Mac" ? "Monaco" : "Courier 10 Pitch");
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
    return inString;
}

QMap<Enu::EMnemonic, QString> Pep::decControlToMnemonMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToDecControlMap;
QMap<Enu::EMnemonic, QString> Pep::memControlToMnemonMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToMemControlMap;
QMap<Enu::EMnemonic, QString> Pep::clockControlToMnemonMap;
QMap<QString, Enu::EMnemonic> Pep::mnemonToClockControlMap;

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
}
