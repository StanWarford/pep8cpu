#include "pep.h"
#include <QFile>
#include <QDebug>

//int pep::GetValue(int address)
//{
////    Q_ASSERT(0x0000 <= address && address <= 0xffff);
//
////    QDebug() << "Get Value: Mem[0x" << address << ".4x]=0x" << m_chMem[address] << ".2x";
//
////    return(m_chMem[address] & 0xff);
//}
//
//void pep::ClearMemory()
//{
//#if 0
//    for (int i = 0; i <= 0xffff; i++)
//    {
//        SetValue(i, 0);
//    }
//#endif
//}
//
//void pep::PopulateMemory()
//{
//#if 0
//    srand (time(NULL));
//    for (int i = 0; i <= 0xffff; i++)
//    {
//        SetValue(i, rand() & 0xff);
//    }
//#endif
//}

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
