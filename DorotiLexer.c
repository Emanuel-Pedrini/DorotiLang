#include "StringUtility.h"
#include "DorotiLexer.h"
#include "ExternalLibraries.h"
#include "ArrayUtilities.h"
#include "LexerIndentifier.h"

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

char GetChar(Doroti_LexerState* DorotiState) {
    return DorotiState -> ActualChar;
}

char PeekChar(Doroti_LexerState* DorotiState) {
    return DorotiState -> SourceCode[(DorotiState -> Pointer ) + 1];
}

void fVoid_SkipIgnorable(Doroti_LexerState* DorotiState) {
    while(1) 
    {
        if (isspace((unsigned char)DorotiState -> ActualChar)) 
        {
            fVoid_Advance(DorotiState);
            continue;
        }
        if (GetChar(DorotiState) == '#' && PeekChar(DorotiState) == '#') 
        {
            while (GetChar(DorotiState) != '\n' && GetChar(DorotiState) != '\0') 
            {
                fVoid_Advance(DorotiState);
            }
            continue;
        }
        break;
    }
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

D_Uint fUint_Indentifier(Doroti_LexerState* DorotiState) {
    D_Uint Start = DorotiState -> Pointer;
    D_Uint End = fUint_ReadIndentifierEnd(DorotiState -> SourceCode, Start);
    fVoid_SetPointer(DorotiState, End);
    return End;
}

D_Uint fUint_Number(Doroti_LexerState* DorotiState) {
    D_Uint Start = DorotiState -> Pointer;
    D_Uint End = fUint_ReadNumberEnd(DorotiState -> SourceCode, Start);
    fVoid_SetPointer(DorotiState, End);
    return End;
}

D_Bool fBool_MatchesKeyword(const char* Source, D_Uint Start, D_Uint TSize, const char* Keyword) {
    D_Uint KeywordLen = strlen(Keyword);
    if (KeywordLen != TSize) {
        return 0;
    }
    return strncmp(&Source[Start], Keyword, TSize) == 0;
}

D_Bool fBool_MatchesAnyKeyword(const char* Source, D_Uint Start, D_Uint TSize) {
    for (int x = 0; strcmp(Doroti_ValidTokens[x] ,"**$Bimbo$**") != 0; x++) {
        if (fBool_MatchesKeyword(Source, Start, TSize, Doroti_ValidTokens[x])) {
            return 1;
        };
    }
    return 0;
}

Doroti_TokenType fTokenType_MatchesWhichKeyword(const char* Source, D_Uint Start, D_Uint TSize) {
    if (fBool_MatchesKeyword(Source, Start, TSize, "int32")) {
        return TokenType_Int32;
    }
    if (fBool_MatchesKeyword(Source, Start, TSize, "array")) {
        return TokenType_Array;
    }
    if (fBool_MatchesKeyword(Source, Start, TSize, "string")) {
        return TokenType_String;
    }
    if (fBool_MatchesKeyword(Source, Start, TSize, "return")) {
        return TokenType_Return;
    }
    if (fBool_MatchesKeyword(Source, Start, TSize, "var")) {
        return TokenType_Variable;
    }
    return TokenType_Indentifier;
}

D_Uint fUint_MeasureIndent(Doroti_LexerState* DorotiState) {
    D_Uint Count = 0;
    D_Uint Offset = DorotiState -> Pointer;
    while (DorotiState -> SourceCode[Offset] == ' ') {
        Count++;
        Offset++;
    }
    return Count;
}

void fVoid_HandleIndentation(Doroti_LexerState* DorotiState, Doroti_Vector* Tokens) {
    D_Uint NewIndent = fUint_MeasureIndent(DorotiState);
    D_Uint CurrentTop = DorotiState -> IndentStack[DorotiState -> IndentTop];
    if (NewIndent > CurrentTop) {
        DorotiState -> IndentTop++;
        DorotiState -> IndentStack[DorotiState -> IndentTop] = NewIndent;
        Doroti_Token* T = fToken_NewToken(
            TokenType_Ident, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            0);
            fVoid_Append(Tokens, T);
            free(T);
    } else {
        while (NewIndent < DorotiState -> IndentStack[DorotiState -> IndentTop]) { 
            DorotiState -> IndentTop--;
            Doroti_Token* T = fToken_NewToken(
            TokenType_Dedent, 
            DorotiState -> Pointer, 
            DorotiState -> Line, 
            DorotiState -> Column, 
            0);
            fVoid_Append(Tokens, T);
            free(T);
        }
    }
}

Doroti_Vector* fVecToken_DorotiLexer(Doroti_LexerState* DorotiState) {
    Doroti_Vector* Tokens = malloc(sizeof(Doroti_Vector));
    if (Tokens == NULL) {
        return NULL;
    }
    fVoid_NewVector(Tokens, sizeof(Doroti_Token));

    fVoid_SetPointer(DorotiState, 0);
    
    DorotiState->IndentTop = 0;
    DorotiState->IndentStack[0] = 0;

    DorotiState -> ActualChar = DorotiState -> SourceCode[DorotiState -> Pointer];
    Doroti_Token* X;
    while (1) {
        if (GetChar(DorotiState) == '\0') {break;}
         if (GetChar(DorotiState) == '\n') {
            fVoid_Advance(DorotiState);
            D_Uint Peek = fUint_MeasureIndent(DorotiState);
            char AfterSpaces = DorotiState -> SourceCode[DorotiState -> Pointer + Peek];
            if (AfterSpaces == '\n' || AfterSpaces == '\0') {
                continue;
            }
            if (AfterSpaces == '#' && DorotiState -> SourceCode[DorotiState -> Pointer + Peek + 1] == '#') {
                continue;
            }
            fVoid_HandleIndentation(DorotiState, Tokens);
            printf("Indentation : %d \n", DorotiState -> IndentTop);
        }

        fVoid_SkipIgnorable(DorotiState);
        if (GetChar(DorotiState) == '\0') {
            break;
        }
        if (!fBool_IsIndentifierChar(GetChar(DorotiState))) {
            Doroti_Token* X = fToken_SpecialChar(DorotiState); 
            fVoid_Append(Tokens, X);
            printf("%c | %d \n", GetChar(DorotiState), X -> Type);
            if (X -> TSize > 0) {
                for (D_Uint x = 0; x < X -> TSize; x++) {
                    fVoid_Advance(DorotiState);
                }
            }
            free(X);  
        } 
        else if (fBool_IsNumerical(GetChar(DorotiState))) {
                D_Uint Start = DorotiState -> Pointer;
                D_Uint End = fUint_Number(DorotiState);
                D_Uint Size = End - Start;
                printf("Number \n");
                Doroti_Token* X = fToken_NewToken(
                    TokenType_Number,
                    Start,
                    DorotiState -> Line,
                    DorotiState -> Column,
                    Size);
                    fVoid_Append(Tokens, X);
                    free(X); 
        }
        else {
            D_Uint Start = DorotiState -> Pointer;
            D_Uint End = fUint_Indentifier(DorotiState);
            D_Uint Size = End - Start;
            Doroti_Token* X = fToken_NewToken(fTokenType_MatchesWhichKeyword(
                DorotiState -> SourceCode, Start, Size),
                Start,
                DorotiState -> Line,
                DorotiState -> Column,
                Size);
                if (X -> Type == TokenType_Indentifier) {
                    printf("Indentifier \n");
                } else {
                    printf("Keyword \n");
                }
                fVoid_Append(Tokens, X);
                free(X);
        }
    }
    while (DorotiState -> IndentTop > 0) {
        DorotiState -> IndentTop--;
        Doroti_Token* T = fToken_NewToken(
        TokenType_Dedent, 
        DorotiState -> Pointer, 
        DorotiState -> Line, 
        DorotiState -> Column, 
        0);
        fVoid_Append(Tokens, T);
        free(T);
    }
    Doroti_Token* T = fToken_NewToken(
    TokenType_EndOfFile, 
    DorotiState -> Pointer, 
    DorotiState -> Line, 
    DorotiState -> Column, 
    0);
    fVoid_Append(Tokens, T);
    free(T);
    return Tokens;
}