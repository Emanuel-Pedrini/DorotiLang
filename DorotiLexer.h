#ifndef _LEXERH_
#define _LEXERH_
#include "DorotiTypes.h"

typedef enum {
    TokenType_Illegal, // 0
    TokenType_EndOfFile, // 1
 
    TokenType_Ident,  // 2
    TokenType_Int,  // 3
    TokenType_String,  // 4

    TokenType_Logos,  // 5

    TokenType_Comma,  // 6
    TokenType_Colon, // 7   
    TokenType_Semicolon,  // 8
    TokenType_LeftParenthesis,  // 9
    TokenType_RightParenthesis,  // 10
    TokenType_LeftBrace,  // 11
    TokenType_RightBrace,  // 12
    TokenType_LeftArrow,  // 13
    TokenType_RightArrow, // 14
    TokenType_LeftKey, // 15
    TokenType_RightKey,  // 16

    TokenType_Plus, // 17
    TokenType_Minus, // 18
    TokenType_Asterisk, // 19      
    TokenType_Slash, // 20    
    TokenType_DoubleAsterisk, // 21 

    TokenType_Sqrt, // 22

    TokenType_Assign, // 23        
    TokenType_Equal, // 24      
    TokenType_NotEqual,   // 25       
    TokenType_LessEqual, // 26 
    TokenType_GreaterEqual, // 27   
    TokenType_FatArrow, // 28
    TokenType_Bang, // 29
    
    TokenType_DoubleLeftArrow, // 30
    TokenType_DoubleRightArrow, // 31
 
    TokenType_DoubleAmpersand,   
    TokenType_DoublePipe,       

    TokenType_DoubleSlash,       
 
    TokenType_Function,
    TokenType_Let,
    TokenType_Field,

    TokenType_Infer,

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

    TokenType_Expect,
    TokenType_EqualLiteral,

    TokenType_UpArrow,

    TokenType_LeftPlus,
    TokenType_LeftSign,
    TokenType_RightPlus,
    TokenType_RightSign,
    TokenType_CommercialE,
    TokenType_Interrogation,
    TokenType_Hashtag,
    TokenType_,

} Doroti_TokenType;

typedef struct {
    Doroti_TokenType Type;
    D_Uint Start;
    D_Uint Line;
    D_Uint Column;
    D_Uint TSize; 
} Doroti_Token;

typedef struct 
{
    char* SourceCode;
    D_Uint SourceSize;
    D_Uint Pointer;
    char ActualChar;

    D_Uint Line;
    D_Uint Column;

} Doroti_LexerState;

Doroti_Token* fToken_NewToken(
    Doroti_TokenType Type,
    D_Uint Start,
    D_Uint Line,
    D_Uint Column,
    D_Uint TSize);

char GetChar(Doroti_LexerState* DorotiState);
char PeekChar(Doroti_LexerState* DorotiState);

void fVoid_DorotiLexer(Doroti_LexerState* DorotiState);
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