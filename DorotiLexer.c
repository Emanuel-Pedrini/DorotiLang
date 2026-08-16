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
    return DorotiState -> SourceCode[(DorotiState -> Pointer )+ 1];
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

D_Bool fBool_MatchesKeyword(const char* Source, D_Uint Start, D_Uint TSize, const char* Keyword) {
    D_Uint KeywordLen = strlen(Keyword);
    if (KeywordLen != TSize) {
        return 0;
    }
    return strncmp(&Source[Start], Keyword, TSize) == 0;
}

D_Bool fBool_MatchesAnyKeyword(const char* Source, D_Uint Start, D_Uint TSize) {
    D_Uint Count = sizeof(Doroti_ValidTokens) / sizeof(Doroti_ValidTokens[0]);
    for (int x = 0; x < Count; x++) {
        if (fBool_MatchesKeyword(Source, Start, TSize, Doroti_ValidTokens[x])) {
            return 1;
        };
    }
    return 0;
}

void fVoid_DorotiLexer(Doroti_LexerState* DorotiState) {
    
    Doroti_Vector Tokens;
    fVoid_NewVector(&Tokens, sizeof(Doroti_Token));

    fVoid_SetPointer(DorotiState, 0);
    DorotiState -> ActualChar = DorotiState -> SourceCode[DorotiState -> Pointer];
    Doroti_Token* X;
    while (1) {
        if (GetChar(DorotiState) == '\0') {break;}
        fVoid_SkipIgnorable(DorotiState);
        if (GetChar(DorotiState) == '\0') {break;}

        if (!fBool_IsIndentifierChar(GetChar(DorotiState))) {
            Doroti_Token* X = fToken_SpecialChar(DorotiState); 
            fVoid_Append(&Tokens, X);
            printf("%c | %d \n", GetChar(DorotiState), X -> Type);
            if (X -> TSize > 0) {
                for (D_Uint x = 0; x < X -> TSize; x++) {
                    fVoid_Advance(DorotiState);
                }
            }
            free(X);  
        } else {
            D_Uint Start = DorotiState -> Pointer;
            D_Uint End = fUint_Indentifier(DorotiState);
            D_Uint Size = End - Start;
            if (fBool_MatchesAnyKeyword(DorotiState -> SourceCode, Start, Size)) {
                printf("keyword! \n");
            }
        }
    }
    fVoid_FreeVector(&Tokens);
}