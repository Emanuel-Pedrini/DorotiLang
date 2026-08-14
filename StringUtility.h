#ifndef StringUtility
#define StringUtility
typedef unsigned long int D_Uint;
typedef unsigned short int D_Bool;

D_Bool fBool_EndWith(const char* String, const char* End);
D_Bool fBool_StartsWith(const char* String, const char* Start);
void fVoid_SubstringOf(const char* String, char* Destiny, unsigned int Start, unsigned int End);
D_Bool fBool_IsNumerical(const char Character);
D_Bool fBool_IsAlphabetic(const char Character);
D_Bool fBool_IsAlphaNumeric(const char Character);
D_Bool fBool_IsIndentifierChar(const char Character);
D_Bool fBool_IsValidIndentifier(const char* String);
void fVoid_ReadWord(const char* String, char* Destiny, unsigned int Start);

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

    "<eof>",
    "<number>",
    "<identifier>",
    "<string>"
};

#endif