#ifndef _LEXERH_
#define _LEXERH_
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

} TokenType;

typedef struct {
    TokenType Type;
    char* Literal;
    
} Token;

#endif