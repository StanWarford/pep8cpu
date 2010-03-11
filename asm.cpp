#include<QStringList>

#include <QDebug>

#include "asm.h"
#include "code.h"

// Regular expressions for lexical analysis
QRegExp Asm::rxComment("^//.*");
QRegExp Asm::rxDigit("^[0-9]+");
QRegExp Asm::rxIdentifier("^((([A-Z|a-z]{1})(\\w*)))");

bool Asm::getToken(QString &sourceLine, ELexicalToken &token, QString &tokenString)
{
    sourceLine = sourceLine.trimmed();
    if (sourceLine.length() == 0) {
        token = LT_EMPTY;
        tokenString = "";
        return true;
    }
    QChar firstChar = sourceLine[0];
    if (firstChar == ',') {
        token = LT_COMMA;
        tokenString = ",";
        sourceLine.remove(0, tokenString.length());
        return true;
    }
    if (firstChar == '/') {
        if (rxComment.indexIn(sourceLine) == -1) {
            tokenString = "//ERROR: Malformed comment"; // Should occur with single "/".
            return false;
        }
        token = LT_COMMENT;
        tokenString = rxComment.capturedTexts()[0];
        sourceLine.remove(0, tokenString.length());
        return true;
    }
    if (firstChar.isDigit()) {
        if (rxDigit.indexIn(sourceLine) == -1) {
            tokenString = "//ERROR: Malformed integer"; // Should not occur.
            return false;
        }
        token = LT_DIGIT;
        tokenString = rxDigit.capturedTexts()[0];
        sourceLine.remove(0, tokenString.length());
        return true;
    }
    if (firstChar == '=') {
        token = LT_EQUALS;
        tokenString = "=";
        sourceLine.remove(0, tokenString.length());
        return true;
    }
    if (firstChar.isLetter()) {
        if (rxIdentifier.indexIn(sourceLine) == -1) {
            tokenString = "//ERROR: Malformed identifier"; // Should not occur
            return false;
        }
        token = LT_IDENTIFIER;
        tokenString = rxIdentifier.capturedTexts()[0];
        sourceLine.remove(0, tokenString.length());
        return true;
    }
    if (firstChar == ';') {
        token = LT_SEMICOLON;
        tokenString = ";";
        sourceLine.remove(0, tokenString.length());
        return true;
    }
    tokenString = "//ERROR: Syntax error.";
    return false;
}

bool Asm::processSourceLine(QString sourceLine, int lineNum, Code &code, QString &errorString)
{
    Asm::ELexicalToken token; // Passed to getToken.
    QString tokenString; // Passed to getToken.
    QString localSymbolDef = ""; // Saves symbol definition for processing in the following state.
    // Enu::EMnemonic localEnumMnemonic; // Key to Pep:: table lookups.

    Asm::ParseState state = Asm::PS_START;
    do {
        qDebug() << "state = " << state;
        if (!getToken(sourceLine, token, tokenString)) {
            errorString = tokenString;
            qDebug() << "Token error. Returning false from processSourceLine";
            return false;
        }
        qDebug() << "tokenString = " << tokenString;
        switch (state) {
        case Asm::PS_START:
            if (token == Asm::LT_COMMA) {
                qDebug() << "LT_COMMA = " << tokenString;
            }
            else if (token == Asm::LT_COMMENT) {
                qDebug() << "LT_COMMENT = " << tokenString;
            }
            else if (token == Asm::LT_DIGIT) {
                qDebug() << "LT_DIGIT = " << tokenString;
            }
            else if (token == Asm::LT_EQUALS) {
                qDebug() << "LT_EQUALS = " << tokenString;
            }
            else if (token == Asm::LT_EMPTY) {
                qDebug() << "LT_EMPTY = " << tokenString;
                state = Asm::PS_FINISH;
            }
            else if (token == Asm::LT_IDENTIFIER) {
                qDebug() << "LT_IDENTIFIER = " << tokenString;
            }
            else if (token == Asm::LT_SEMICOLON) {
                qDebug() << "LT_SEMICOLON = " << tokenString;
            }
            else {
                errorString = "//ERROR: Line must start with a control signal or comment.";
                return false;
            }
            break;

        case Asm::PS_CLOSE:
            break;

        case Asm::PS_COMMENT:
            if (token == Asm::LT_EMPTY) {
                state = Asm::PS_FINISH;
            }
            else {
                // This error should not occur, as all characters are allowed in comments.
                errorString = "//ERROR: Problem detected after comment.";
                return false;
            }
            break;

        default:
            break;
        }
    }
    while (state != Asm::PS_FINISH);
    qDebug() << "Returning true from processSourceLine";
    return true;
}
