#ifndef StringUtility
#define StringUtility
short int fBool_EndWith(const char* String, const char* End);
short int fBool_StartsWith(const char* String, const char* Start);
void fPChar_SubstringOf(const char* String, char* Destiny, unsigned int Start, unsigned int End);
short int fBool_IsNumerical(const char Character);
short int fBool_IsAlphabetic(const char Character);
short int fBool_IsAlphaNumeric(const char Character);
short int fBool_IsIndentifierChar(const char Character);
short int fBool_IsValidIndentifier(const char* String);
#endif