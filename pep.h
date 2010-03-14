#ifndef PEP_H
#define PEP_H

#include <QString>
#include <QMap>

#include "enu.h"

class Pep
{
public:
    // Function to read text from a resource file
    static QString resToString(QString fileName);

    // Maps between mnemonic enums and strings
    static QMap<Enu::EMnemonic, QString> decControlToMnemonMap;
    static QMap<QString, Enu::EMnemonic> mnemonToDecControlMap;
    static QMap<Enu::EMnemonic, QString> memControlToMnemonMap;
    static QMap<QString, Enu::EMnemonic> mnemonToMemControlMap;
    static QMap<Enu::EMnemonic, QString> clockControlToMnemonMap;
    static QMap<QString, Enu::EMnemonic> mnemonToClockControlMap;
    static void initEnumMnemonMaps();
};

#endif // PEP_H
