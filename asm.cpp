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
    tokenString = "//ERROR: Syntax error starting with " + QString(firstChar);
    return false;
}

bool Asm::processSourceLine(QString sourceLine, Code *&code, QString &errorString)
{
    Asm::ELexicalToken token; // Passed to getToken.
    QString tokenString; // Passed to getToken.
    QString localIdentifier = ""; // Saves identifier for processing in the following state.
    Enu::EMnemonic localEnumMnemonic; // Key to Pep:: table lookups.

    code.clear();
    Asm::ParseState state = Asm::PS_START;
    do {
        if (!getToken(sourceLine, token, tokenString)) {
            errorString = tokenString;
            return false;
        }
        switch (state) {
        case Asm::PS_START:
            if (token == Asm::LT_IDENTIFIER) {
                if (Pep::mnemonToDecControlMap.contains(tokenString.toUpper())) {
                    localEnumMnemonic = Pep::mnemonToDecControlMap.value(tokenString.toUpper());
                    localIdentifier = tokenString;
                    state = Asm::PS_EQUAL_DEC;
                }
                else if (Pep::mnemonToMemControlMap.contains(tokenString.toUpper())) {
                    localEnumMnemonic = Pep::mnemonToMemControlMap.value(tokenString.toUpper());
                    if (code.has(localEnumMnemonic)) {
                        errorString = "//ERROR: Duplicate control signal, " + tokenString;
                        return false;
                    }
                    code.set(localEnumMnemonic, 1);
                    state = Asm::PS_CONTINUE_PRE_SEMICOLON;
                }
                else if (Pep::mnemonToClockControlMap.contains(tokenString.toUpper())) {
                    errorString = "//ERROR: Clock signal (" + tokenString + ") must appear after semicolon";
                    return false;
                }
                else {
                    errorString = "//ERROR: Unrecognized control signal: " + tokenString;
                    return false;
                }
            }
            else if (token == Asm::LT_SEMICOLON) {
                state = Asm::PS_CONTINUE_POST_SEMICOLON;
            }
            else if (token == Asm::LT_COMMENT) {
                code.cComment = tokenString;
                state = Asm::PS_COMMENT;
            }
            else if (token == Asm::LT_EMPTY) {
                state = Asm::PS_FINISH;
            }
            else {
                errorString = "//ERROR: Syntax error where control signal or comment expected";
                return false;
            }
            break;

        case Asm::PS_EQUAL_DEC:
            if (token == Asm::LT_EQUALS) {
                state = Asm::PS_DEC_CONTROL;
            }
            else {
                errorString = "//ERROR: Expected = after " + localIdentifier;
                return false;
            }
            break;

        case Asm::PS_DEC_CONTROL:
            if (token == Asm::LT_DIGIT) {
                if (code.has(localEnumMnemonic)) {
                    errorString = "//ERROR: Duplicate control signal, " + localIdentifier;
                    return false;
                }
                bool ok;
                int value = tokenString.toInt(&ok);
                if (!code.inRange(localEnumMnemonic, value)) {
                    errorString = "//ERROR: Value " + QString("%1").arg(value) + " is out of range for " + localIdentifier;
                    return false;
                }
                code.set(localEnumMnemonic, value);
                state = Asm::PS_CONTINUE_PRE_SEMICOLON;
            }
            else {
                errorString = "//ERROR: Expected decimal number after " + localIdentifier + "=";
                return false;
            }
            break;

        case Asm::PS_CONTINUE_PRE_SEMICOLON:
            if (token == Asm::LT_COMMA) {
                state = Asm::PS_START;
            }
            else if (token == Asm::LT_SEMICOLON) {
                state = Asm::PS_START_POST_SEMICOLON;
            }
            else if (token == Asm::LT_COMMENT) {
                code.cComment = tokenString;
                state = Asm::PS_COMMENT;
            }
            else if (token == Asm::LT_EMPTY) {
                state = Asm::PS_FINISH;
            }
            else {
                errorString = "//ERROR: Expected ',' or ';' after control signal";
                return false;
            }
            break;

        case Asm::PS_START_POST_SEMICOLON:
            if (token == Asm::LT_IDENTIFIER) {
                if (Pep::mnemonToClockControlMap.contains(tokenString.toUpper())) {
                    localEnumMnemonic = Pep::mnemonToClockControlMap.value(tokenString.toUpper());
                    if (code.has(localEnumMnemonic)) {
                        errorString = "//ERROR: Duplicate clock signal, " + tokenString;
                        return false;
                    }
                    code.set(localEnumMnemonic, 1);
                    state = Asm::PS_CONTINUE_POST_SEMICOLON;
                }
                else if (Pep::mnemonToDecControlMap.contains(tokenString.toUpper())) {
                    errorString = "//ERROR: Control signal " + tokenString + " after ';'";
                    return false;
                }
                else if (Pep::mnemonToMemControlMap.contains(tokenString.toUpper())) {
                    errorString = "//ERROR: Memory control signal " + tokenString + " after ';'";
                    return false;
                }
                else {
                    errorString = "//ERROR: Unrecognized clock signal: " + tokenString;
                    return false;
                }
            }
            else if (token == Asm::LT_COMMENT) {
                code.cComment = tokenString;
                state = Asm::PS_COMMENT;
            }
            else if (token == Asm::LT_SEMICOLON) {
                state = Asm::PS_CONTINUE_POST_SEMICOLON;
            }
            else if (token == Asm::LT_EMPTY) {
                state = Asm::PS_FINISH;
            }
            else {
                errorString = "//ERROR: Syntax error where clock signal or comment expected.";
                return false;
            }
            break;

        case Asm::PS_CONTINUE_POST_SEMICOLON:
            if (token == Asm::LT_COMMA) {
                state = Asm::PS_START_POST_SEMICOLON;
            }
            else if (token == Asm::LT_SEMICOLON) {
                errorString = "//ERROR: Multiple semcolons ';'";
                return false;
            }
            else if (token == Asm::LT_COMMENT) {
                code.cComment = tokenString;
                state = Asm::PS_COMMENT;
            }
            else if (token == Asm::LT_EMPTY) {
                state = Asm::PS_FINISH;
            }
            else {
                errorString = "//ERROR: Expected ',' after clock signal";
                return false;
            }
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
    return true;
}
