#ifndef _LEXERH_
#define _LEXERH_
#include "DorotiTypes.h"
#include "ArrayUtilities.h"

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
 
    TokenType_DoubleAmpersand, // 32  
    TokenType_DoublePipe, // 33

    TokenType_DoubleSlash, // 34  
 
    TokenType_Function, // 35
    TokenType_Let, // 36
    TokenType_Field, // 37

    TokenType_Infer, // 38

    TokenType_If, // 39
    TokenType_Else, // 40
    TokenType_Elif, // 41 
    TokenType_For, // 42
    TokenType_Until, // 43
    TokenType_Repeat, // 44
    TokenType_Then, // 45
    TokenType_Break, // 46
 
    TokenType_And, // 47
    TokenType_Or, // 48
 
    TokenType_Go, // 49
    TokenType_Make, // 50
    TokenType_DoubleColon, // 51
    TokenType_DoublePoint, // 52
    TokenType_TriplePoint, // 53

    TokenType_Expect, // 54
    TokenType_EqualLiteral, // 55

    TokenType_UpArrow, // 56

    TokenType_LeftPlus, // 57
    TokenType_LeftSign, // 58
    TokenType_RightPlus, // 59
    TokenType_RightSign, // 60
    TokenType_CommercialE, // 61
    TokenType_Interrogation, // 62
    TokenType_Hashtag, // 63
    TokenType_Array, // 64
    TokenType_NewLine, // 65
    TokenType_Dedent, // 66
    TokenType_PlusPlus, // 67
    TokenType_MinusMinus, // 68
    TokenType_Variable, // 69
    TokenType_Return, // 70
    TokenType_Number, // 71
    TokenType_Indentifier, // 72
    TokenType_Point, // 73

    TokenType_Int8,
    TokenType_Int16,
    TokenType_Int32,
    TokenType_Int64,
    TokenType_Int128,
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
    D_Uint IndentStack[64];
    D_Uint IndentTop;
} Doroti_LexerState;

Doroti_Token* fToken_NewToken(
    Doroti_TokenType Type,
    D_Uint Start,
    D_Uint Line,
    D_Uint Column,
    D_Uint TSize);

char GetChar(Doroti_LexerState* DorotiState);
char PeekChar(Doroti_LexerState* DorotiState);

Doroti_Vector* fVecToken_DorotiLexer(Doroti_LexerState* DorotiState);
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
    "or",
    "and",
    "repeat",

    "var",
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

    "string",
    "array",
    "**$Bimbo$**"
};

#endif