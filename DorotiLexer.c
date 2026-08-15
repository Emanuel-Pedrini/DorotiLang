#include "StringUtility.h"
#include "DorotiLexer.h"
#include "ExternalLibraries.h"
#include "ArrayUtilities.h"

void fVoid_IncreasePointer(Doroti_LexerState* DorotiState) {
    DorotiState -> Pointer++;
    DorotiState -> ActualChar = DorotiState -> SourceCode[DorotiState -> Pointer];
}

void fVoid_DecreasePointer(Doroti_LexerState* DorotiState) {
    if (DorotiState -> Pointer > 0) {
        DorotiState -> Pointer--;
    }
    DorotiState -> ActualChar = DorotiState -> SourceCode[DorotiState -> Pointer];
}

void fVoid_SetPointer(Doroti_LexerState* DorotiState, D_Uint SetValue) {
    DorotiState -> Pointer = SetValue;
    DorotiState -> ActualChar = DorotiState -> SourceCode[DorotiState -> Pointer];
}

void fVoid_Advance(Doroti_LexerState* DorotiState) {
    fVoid_IncreasePointer(DorotiState);
}

void fVoid_SkipWhitespace(Doroti_LexerState* DorotiState) {
    while (isspace((unsigned char)DorotiState -> ActualChar)) {
        fVoid_Advance(DorotiState);
    }
}

char GetChar(Doroti_LexerState* DorotiState) {
    return DorotiState -> ActualChar;
}

char PeekChar(Doroti_LexerState* DorotiState) {
    return DorotiState -> SourceCode[(DorotiState -> Pointer )+ 1];
}

void fVoid_DorotiLexer(Doroti_LexerState* DorotiState) {
    
    Doroti_Vector* Tokens;
    fVoid_NewVector(Tokens, sizeof(Doroti_Token));

    fVoid_SetPointer(DorotiState, 0);
    DorotiState -> ActualChar = DorotiState -> SourceCode[DorotiState -> Pointer];
    while (1) {
        if (GetChar(DorotiState) == '\0') {
            break;
        }

        fVoid_SkipWhitespace(DorotiState);
        if (!fBool_IsAlphaNumeric(GetChar(DorotiState))) {
            printf("%c \n", GetChar(DorotiState));
        }

        fVoid_Advance(DorotiState);
    }
    fVoid_FreeVector(Tokens);
}

Doroti_Token* fToken_NewToken(
    Doroti_TokenType Type,
    D_Uint Start,
    D_Uint Line,
    D_Uint Column,
    D_Uint TSize) {
    Doroti_Token* TemporaryToken = malloc(sizeof(Doroti_Token));
    
    if (TemporaryToken == NULL) {
        free(TemporaryToken);
        return NULL;
    }
    TemporaryToken -> Type = Type;
    TemporaryToken -> Start = Start;
    TemporaryToken -> TSize = TSize;
    TemporaryToken -> Line = Line;
    TemporaryToken -> Column = Column;
    return TemporaryToken;
}

Doroti_Token* fToken_SpecialChar(Doroti_LexerState* DorotiState) {
    switch (GetChar(DorotiState))
    {
    case '@':
        return fToken_NewToken(
            TokenType_Logos, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);
    case '(':
        return fToken_NewToken(
            TokenType_LeftParenthesis, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);
    case ')':
        return fToken_NewToken(
            TokenType_RightParenthesis, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);
    case '{':
        return fToken_NewToken(
            TokenType_LeftKey, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);
    case '}':
        return fToken_NewToken(
            TokenType_RightKey, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);

    case '[':
        return fToken_NewToken(
            TokenType_LeftBrace, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);
    case ']':
        return fToken_NewToken(
            TokenType_RightBrace, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);

    case ':':
        return fToken_NewToken(
            TokenType_Colon, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            1);

    case '>':
        Doroti_TokenType Type;
        D_Uint Start = DorotiState -> Pointer;
        D_Uint Size;

        if (PeekChar(DorotiState) == '>') {
            Type = TokenType_DoubleRightArrow;
            Size = 2;
            fVoid_Advance(DorotiState);
        } 
        else {
            Type = TokenType_RightArrow;
            Size = 1;
        }

        return fToken_NewToken(
            Type, 
            Start, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            Size);
    default:
        break;
    } 
}