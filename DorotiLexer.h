#ifndef _LEXERH_
#define _LEXERH_

typedef unsigned long int D_Uint;
typedef unsigned short int D_Bool;

typedef enum {
    TokenType_Illegal,
    TokenType_Indentifier,
    TokenType_EndOfFile,
    TokenType_Ident,
    TokenType_Int,
    TokenType_Plus,
    TokenType_Minus,
    TokenType_Comma,
    TokenType_LeftParenthesis,
    TokenType_RightParenthesis,
    TokenType_Semicolon,
    TokenType_LeftBrace,
    TokenType_RightBrace,
    TokenType_LeftArrow,
    TokenType_RightArrow,
    TokenType_Function,
    TokenType_Let,

} Doroti_TokenType;

typedef struct {
    Doroti_TokenType Type;
    char* Literal;
} Doroti_Token;

typedef struct 
{
    char* SourceCode;
    D_Uint SourceSize;
    D_Uint Pointer;
    char ActualChar;

} Doroti_LexerState;

void DorotiLexer(Doroti_LexerState* DorotiState);

#endif