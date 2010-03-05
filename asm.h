#ifndef ASM_H
#define ASM_H

#include <QRegExp>

class Code; // Forward declaration for argument of processSourceLine.

class Asm
{
public:
    // Lexical tokens
    enum ELexicalToken
    {
        LT_COMMA, LT_COMMENT, LT_DIGIT, LT_EQUALS, LT_EMPTY, LT_IDENTIFIER, LT_SEMICOLON
    };

    enum ParseState
    {
        PS_ADDRESSING_MODE, PS_CLOSE, PS_COMMENT, PS_DOT_ADDRSS, PS_DOT_ASCII, PS_DOT_BLOCK,
        PS_DOT_BURN, PS_DOT_BYTE, PS_DOT_END, PS_DOT_EQUATE, PS_DOT_WORD, PS_FINISH,
        PS_INSTRUCTION, PS_START, PS_STRING, PS_SYMBOL_DEF
    };

    // Regular expressions for lexical analysis
    static QRegExp rxComment;
    static QRegExp rxDigit;
    static QRegExp rxIdentifier;

    static bool getToken(QString &sourceLine, ELexicalToken &token, QString &tokenString);
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
