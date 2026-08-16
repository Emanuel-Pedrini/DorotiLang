#include "DorotiTypes.h"
#include "DorotiLexer.h"
Doroti_Token* fToken_SpecialChar(Doroti_LexerState* DorotiState) {
    Doroti_TokenType TokenType;
    D_Uint TokenStart = DorotiState -> Pointer;
    D_Uint TokenSize;
    switch (GetChar(DorotiState))
    {
    case '@':
        TokenType = TokenType_Logos;
        TokenSize = 1;
        break;
    case '(':
        TokenType = TokenType_LeftParenthesis;
        TokenSize = 1;
        break;
    case ')':
        TokenType = TokenType_RightParenthesis;
        TokenSize = 1;
        break;
    case '{':
        TokenType = TokenType_LeftKey;
        TokenSize = 1;
        break;
    case '}':
        TokenType = TokenType_RightKey;
        TokenSize = 1;
        break;
    case '[':
        TokenType = TokenType_LeftBrace;
        TokenSize = 1;
        break;
    case ']':
        TokenType = TokenType_RightBrace;
        TokenSize = 1;
        break;
    case ':':
        switch (PeekChar(DorotiState)) {
            case ':':
                TokenType = TokenType_DoubleColon;
                TokenSize = 2;
                break;
            case '=':
                TokenType = TokenType_Infer;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_Colon;
                TokenSize = 1;
                break;
        }
        break;
    case '#':
        TokenType = TokenType_Hashtag;
        TokenSize = 1;
        break;
    case '>':
        switch (PeekChar(DorotiState)) {
            case '>':
                TokenType = TokenType_DoubleRightArrow;
                TokenSize = 2;
                break;
            case '=':
                TokenType = TokenType_GreaterEqual;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_RightArrow;
                TokenSize = 1;
                break;
        }
        break;
    case '<':
        switch (PeekChar(DorotiState)) {
            case '<':
                TokenType = TokenType_DoubleLeftArrow;
                TokenSize = 2;
                break;
            case '=':
                TokenType = TokenType_LessEqual;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_Colon;
                TokenSize = 1;
                break;
        }
        break;
    case '=':
        switch (PeekChar(DorotiState)) {
            case '=':
                TokenType = TokenType_Equal;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_EqualLiteral;
                TokenSize = 1;
                break;
        }
        break;
    case '.':
        switch (PeekChar(DorotiState)) {
            case '.':
                TokenType = TokenType_DoublePoint;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_Point;
                TokenSize = 1;
                break;
        }
        break;
    case ',':
        TokenType = TokenType_Comma;
        TokenSize = 1;
        break;

    case '+':
        switch (PeekChar(DorotiState)) {
            case '+':
                TokenType = TokenType_PlusPlus;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_Plus;
                TokenSize = 1;
                break;
        }
        break;

    case '*':
        switch (PeekChar(DorotiState)) {
            case '*':
                TokenType = TokenType_DoubleAsterisk;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_Asterisk;
                TokenSize = 1;
                break;
        }
        break;
        
    case '&':
        TokenType = TokenType_CommercialE;
        TokenSize = 1;

    case '-':
        switch (PeekChar(DorotiState)) {
            case '-':
                TokenType = TokenType_MinusMinus;
                TokenSize = 2;
                break;
            default:
                TokenType = TokenType_Minus;
                TokenSize = 1;
                break;
        }
        break;

    default:
        TokenType = TokenType_Illegal;
        TokenSize = 1;
        break;
    }
    return fToken_NewToken(
    TokenType, 
    TokenStart, 
    DorotiState -> Line, 
    DorotiState -> Column, 
    TokenSize);
}
Doroti_Token* fToken_KeyWord(Doroti_LexerState* DorotiState) {
}