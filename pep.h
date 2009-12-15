#ifndef PEP_H
#define PEP_H

#include <QString>

class Pep
{
public:
    // Function to read text from a resource file
    static QString resToString(QString fileName);
};

#endif // PEP_H
