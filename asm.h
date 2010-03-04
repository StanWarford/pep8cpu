#ifndef ASM_H
#define ASM_H

#include <QString>

class Code; // Forward declaration for argument of processSourceLine.

class Asm
{
public:
    Asm();

//    static bool getToken(QString &sourceLine, ELexicalToken &token, QString &tokenString);
    // Pre: sourceLine has one line of source code.
    // Post: If the next token is valid, the string of characters representing the next token are deleted from the
    // beginning of sourceLine and returned in tokenString, true is returned, and token is set to the token type.
    // Post: If false is returned, then tokenString is set to the lexical error message.

    static bool processSourceLine(QString sourceLine, int lineNum, Code &code, QString &errorString);
    // Pre: sourceLine has one line of source code.
    // Pre: lineNum is the line number of the source code.
    // Post: If the source line is valid, true is returned and code is set to the source code for the line.
    // Post: If the source line is not valid, false is returned and errorString is set to the error message.

};

#endif // ASM_H
