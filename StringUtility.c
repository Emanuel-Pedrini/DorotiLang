#include "ExternalLibraries.h"
#include "StringUtility.h"

D_Bool fBool_EndWith(const char* String, const char* End) {
    int SizeOfEnd = strlen(End);
    int SizeOfString = strlen(String);
    for (int x = SizeOfString - SizeOfEnd, y = 0; x < SizeOfString ; x++, y ++) {
        if (String[x] != End[y]){
            return 0;
        }
    }
    return 1;
}

D_Bool fBool_StartsWith(const char* String, const char* Start) {
    int SizeOfStart = strlen(Start);
    int SizeOfString = strlen(String);
    for (int x = 0, y = 0; x < SizeOfStart ; x++, y ++) {
        if (String[x] != Start[y]){
            return 0;
        }
    }
    return 1;
}
/*
    OWNERSHIP!
    Please, free the freaking memory after using this.
    I'll try to change this after.
*/
char* fPChar_SubstringOf(const char* String, unsigned int Start, unsigned int End) {
    int SizeOfString = strlen(String);
    if (End > (unsigned int)SizeOfString) {
        End = SizeOfString;
    }
    
    if (End <= Start) {
        return NULL;
    }

    char* TemporaryBuffer = malloc((End - Start + 1) * sizeof(unsigned char));
    
    if (TemporaryBuffer == NULL) {
        return NULL;
    }

    unsigned int y = 0;
    for (int x = Start; x < End; x++, y ++) {
        TemporaryBuffer[y] = String[x];
    }
    TemporaryBuffer[y] = '\0';
    return TemporaryBuffer;
}

D_Bool fBool_IsNumerical(const char Character) {
    if ('0' <= Character && Character <= '9') {
        return 1;
    }
    return 0;
}

D_Bool fBool_IsAlphabetic(const char Character) {
    if ('a' <= Character && Character <= 'z' || 'A' <= Character && Character <= 'Z') {
        return 1;
    }
    return 0;
}

D_Bool fBool_IsAlphaNumeric(const char Character) {
    if (('a' <= Character && Character <= 'z') || 
        ('A' <= Character && Character <= 'Z') || 
        ('0' <= Character && Character <= '9')) {
        return 1;
    }
    return 0;
}

D_Bool fBool_IsIndentifierChar(const char Character) {
    if (('a' <= Character && Character <= 'z') || 
        ('A' <= Character && Character <= 'Z') || 
        ('0' <= Character && Character <= '9') ||
        (Character == '_' && Character != ' ')) {
        return 1;
    }
    return 0;
}

D_Bool fBool_IsValidIndentifier(const char* String) {
    int SizeOfString = strlen(String);
    for (int x = 0 ; x < SizeOfString; x++) {
        if (!fBool_IsIndentifierChar(String[x])) {
            return 0;
        }
    }
    return 1;
}

void fVoid_ReadWord(const char* String, char* Destiny, unsigned int Start) {
    unsigned int y = 0;
    for (int x = Start;
         String[x] != '\0' &&
         fBool_IsIndentifierChar(String[x]); 
         x++, y++) {
        Destiny[y] = String[x];
    }
    Destiny[y] = '\0';
}

D_Uint fUint_ReadIndentifierEnd(const char* String, unsigned int Start) {
    unsigned int y = 0;
    for (int x = Start;
         String[x] != '\0' &&
         fBool_IsIndentifierChar(String[x]); 
         x++, y++) {
    }
    return Start + y;
}

D_Uint fUint_ReadNumberEnd(const char* String, unsigned int Start) {
    unsigned int y = 0;
    for (int x = Start;
         String[x] != '\0' &&
         (fBool_IsNumerical(String[x]) || String[x] == '.'); 
         x++, y++) {
    }
    return Start + y;
}

D_Uint fVoid_WordEnd(const char* String, unsigned int Start) {
    unsigned int y = 0;
    for (int x = Start;
         String[x] != '\0' &&
         fBool_IsAlphabetic(String[x]); 
         x++, y++) {
    }
    return Start + y;
}

void fVoid_ReadNumerical(const char* String, char* Destiny, unsigned int Start) {
    unsigned int y = 0;
    for (int x = Start;
         String[x] != '\0' &&
         !isspace((unsigned char)String[x]) &&
         (fBool_IsNumerical(String[x]) || String[x] == '.');
         x++, y++) {
        Destiny[y] = String[x];
    }
    Destiny[y] = '\0';
}

void fVoid_ReadString(const char* String, char* Destiny, unsigned int Start) {
    unsigned int y = 0;
    for (int x = Start; String[x] != '\''; x++, y ++) {
        Destiny[y] = String[x];
    }
    Destiny[y] = '\0';
}
