#ifndef StringUtility
#define StringUtility
#include "DorotiTypes.h"

D_Bool fBool_EndWith(const char* String, const char* End);
D_Bool fBool_StartsWith(const char* String, const char* Start);
char* fPChar_SubstringOf(const char* String, unsigned int Start, unsigned int End);
D_Bool fBool_IsNumerical(const char Character);
D_Bool fBool_IsAlphabetic(const char Character);
D_Bool fBool_IsAlphaNumeric(const char Character);
D_Bool fBool_IsIndentifierChar(const char Character);
D_Bool fBool_IsValidIndentifier(const char* String);
void fVoid_ReadWord(const char* String, char* Destiny, unsigned int Start);
void fVoid_ReadString(const char* String, char* Destiny, unsigned int Start);
void fVoid_ReadNumerical(const char* String, char* Destiny, unsigned int Start);
#endif