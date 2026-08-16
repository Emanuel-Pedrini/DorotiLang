#ifndef _DOROTIPARSERH_ 
#define _DOROTIPARSERH_ 
#include "DorotiLexer.h"
typedef struct {
    char* Source;
    Doroti_Vector* Tokens;
    D_Uint Pointer;
    D_Uint Size;
    Doroti_Token ActualToken;
} Doroti_ParserState;
void fVoid_DorotiParser(Doroti_ParserState* DorotiState);
#endif