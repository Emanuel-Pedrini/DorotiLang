#include "DorotiParser.h"
#include "ExternalLibraries.h"
#include "ParserStructures.h"
#include "StringUtility.h"

int fInt_Clamp(int Value, int Min, int Max) {
    if (Value < Min) {
        return Min;
    } if (Value > Max) {
        return Max;
    } else {
        return Value;
    }
}

Doroti_Token* fToken_GetToken(Doroti_ParserState* DorotiState, int Offset) {    
    int EffectiveOffset = fInt_Clamp(DorotiState -> Pointer + Offset, 0, DorotiState -> Tokens -> Size - 1);
    Doroti_Token* T = (Doroti_Token*)fVoid_Get(DorotiState -> Tokens, EffectiveOffset);
    return T;
}

D_Bool fBool_Expect(Doroti_ParserState* DorotiState, Doroti_TokenType Expected, int Offset) {
    return fToken_GetToken(DorotiState, Offset) -> Type == Expected;
}

Doroti_TokenType fTokenType_PeekToken(Doroti_ParserState* DorotiState) {
    return fToken_GetToken(DorotiState, 1) -> Type;
}

void fVoid_ParserAdvance(Doroti_ParserState* DorotiState) {
    DorotiState -> Pointer++;
}

void fVoid_SetParserPointer(Doroti_ParserState* DorotiState, D_Uint SetValue) {
    DorotiState -> Pointer = SetValue;
}

Doroti_Node* fNode_ParseExpression(Doroti_ParserState* DorotiState) {

}

Doroti_Vector* fVecParameters_ParserFunctionArguments(Doroti_ParserState* DorotiState) {
    Doroti_Vector* Arguments = malloc(sizeof(Doroti_Vector));
    fVoid_NewVector(Arguments, sizeof(Doroti_FunctionParameter));
    if (fBool_Expect(DorotiState, TokenType_RightParenthesis, 0)) {
        return Arguments;
    }
    while (!fBool_Expect(DorotiState, TokenType_RightParenthesis, 0)) {
        printf("Test, Probably a argument.\n");
    }
}

Doroti_Node* f_ParserFunctionDeclaration(Doroti_ParserState* DorotiState) {
    /* @ Name ( Arguments : ArgumentType ) >> ReturnType : */
    Doroti_Node* Node = malloc(sizeof(Doroti_Node));
    if (Node == NULL) {
        free(Node);
        return NULL;
    }

    Node -> Type = NodeType_FunctionDecl;
    fVoid_ParserAdvance(DorotiState);

    Doroti_Token* NameToken = fToken_GetToken(DorotiState, 0);

    if (NameToken -> Type != TokenType_Indentifier) {
        free(Node);
        return NULL;
    }

    Node -> Data.NodeType_FunctionDecl.Name = fPChar_SubstringOf(DorotiState -> Source, NameToken -> Start, NameToken -> Start + NameToken -> TSize);
    printf("New Function : %s\n", fPChar_SubstringOf(DorotiState -> Source, NameToken -> Start, NameToken -> Start + NameToken -> TSize));
    
    if (!fBool_Expect(DorotiState, TokenType_LeftParenthesis, 0)) {
        free(Node);
        return NULL;
    }

    fVoid_ParserAdvance(DorotiState);
    fVecParameters_ParserFunctionArguments(DorotiState);
}
void fVoid_DorotiParser(Doroti_ParserState* DorotiState) {
    fVoid_SetParserPointer(DorotiState, 0);
    while (1) {
        if (fToken_GetToken(DorotiState, 0) -> Type == TokenType_EndOfFile){
            printf("Token End! \n");
            break;
        } else {
            if (fToken_GetToken(DorotiState, 0) -> Type == TokenType_Logos) {
                f_ParserFunctionDeclaration(DorotiState);
            }
        }
        fVoid_ParserAdvance(DorotiState);
    }
   printf("%lu", DorotiState -> Size);
}