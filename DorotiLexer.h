#ifndef _LEXERH_
#define _LEXERH_
#include "DorotiTypes.h"

typedef struct 
{
    char* SourceCode;
    D_Uint SourceSize;
    D_Uint Pointer;
    char ActualChar;

    D_Uint Line;
    D_Uint Column;

} Doroti_LexerState;

void fVoid_DorotiLexer(Doroti_LexerState* DorotiState);

typedef enum {
    TokenType_Illegal,
    TokenType_EndOfFile,
 
    TokenType_Ident,
    TokenType_Int,
    TokenType_String,

    TokenType_Logos,

    TokenType_Comma,
    TokenType_Colon,         
    TokenType_Semicolon,
    TokenType_LeftParenthesis,
    TokenType_RightParenthesis,
    TokenType_LeftBrace,
    TokenType_RightBrace,
    TokenType_LeftArrow,        
    TokenType_RightArrow,      
    TokenType_LeftKey,
    TokenType_RightKey,

    TokenType_Plus,
    TokenType_Minus,
    TokenType_Asterisk,         
    TokenType_Slash,             
    TokenType_DoubleAsterisk, 
 
    TokenType_Assign,            
    TokenType_Equal,             
    TokenType_NotEqual,          
    TokenType_LessEqual,        
    TokenType_GreaterEqual,      
    TokenType_FatArrow,         
    TokenType_Bang,
    
    TokenType_DoubleLeftArrow,
    TokenType_DoubleRightArrow,
 
    TokenType_DoubleAmpersand,   
    TokenType_DoublePipe,       

    TokenType_DoubleSlash,       
 
    TokenType_Function,
    TokenType_Let,
    TokenType_Field,
 
    TokenType_If,
    TokenType_Else,
    TokenType_Elif,
    TokenType_For,
    TokenType_Until,
    TokenType_Repeat,
    TokenType_Then,
    TokenType_Break,
 
    TokenType_And,
    TokenType_Or,
 
    TokenType_Go,
    TokenType_Make,
    TokenType_DoubleColon,
    TokenType_DoublePoint,
    TokenType_TriplePoint,

    TokenType_Expect

} Doroti_TokenType;

typedef struct {
    Doroti_TokenType Type;
    D_Uint Start;
    D_Uint Line;
    D_Uint Column;
    D_Uint TSize; 
} Doroti_Token;

static const char* const Doroti_ValidTokens[] = {
    "let",
    ">>",
    "<<",
    "field",
    "go",
    "make",
    "until",
    "for",
    "then",
    "break",
    "if",
    "else",
    "elif",
    "//",
    "&&",
    "||",
    "**",
    "==",
    "=>",
    "<=",
    "!=",
    "or",
    "and",
    "repeat",

    "var",
    "var!",
    "var?",
    "dyn",
    "stt",

    "int8",
    "int16",
    "int32",
    "int64",
    "int128",

    "uint8",
    "uint16",
    "uint32",
    "uint64",
    "uint128",

    "float8",
    "float6",
    "float32",
    "float64",
    "float128",

    "<eof>",
    "<number>",
    "<identifier>",
    "<string>",
    "..",
    "...",
    "::",
};

#endif