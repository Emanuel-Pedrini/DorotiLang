#include <string.h>
#include <stdio.h>
#include "StringUtility.h"

short int fBool_EndWith(const char* String, const char* End) {
    int SizeOfEnd = strlen(End);
    int SizeOfString = strlen(String);
    for (int x = SizeOfString - SizeOfEnd, y = 0; x < SizeOfString ; x++, y ++) {
        if (String[x] != End[y]){
            return 0;
        }
    }
    return 1;
}

short int fBool_StartsWith(const char* String, const char* Start) {
    int SizeOfStart = strlen(Start);
    int SizeOfString = strlen(String);
    for (int x = 0, y = 0; x < SizeOfStart ; x++, y ++) {
        if (String[x] != Start[y]){
            return 0;
        }
    }
    return 1;
}

void fPChar_SubstringOf(const char* String, char* Destiny, unsigned int Start, unsigned int End) {
    int SizeOfString = strlen(String);
    unsigned int y = 0;
    for (int x = Start + 1; x < End + 1 ; x++, y ++) {
        Destiny[y] = String[x];
    }
    Destiny[y] = '\0';
}

short int fBool_IsNumerical(const char Character) {
    if ('0' <= Character && Character <= '9') {
        return 1;
    }
    return 0;
}

short int fBool_IsAlphabetic(const char Character) {
    if ('a' <= Character && Character <= 'z' || 'A' <= Character && Character <= 'Z') {
        return 1;
    }
    return 0;
}

short int fBool_IsAlphaNumeric(const char Character) {
    if (('a' <= Character && Character <= 'z') || 
        ('A' <= Character && Character <= 'Z') || 
        ('0' <= Character && Character <= '9')) {
        return 1;
    }
    return 0;
}

short int fBool_IsIndentifierChar(const char Character) {
    if (('a' <= Character && Character <= 'z') || 
        ('A' <= Character && Character <= 'Z') || 
        ('0' <= Character && Character <= '9') ||
        (Character == '_' && Character != ' ')) {
        return 1;
    }
    return 0;
}

short int fBool_IsValidIndentifier(const char* String) {
    int SizeOfString = strlen(String);
    for (int x = 0 ; x < SizeOfString; x++) {
        if (!fBool_IsIndentifierChar(String[x])) {
            return 0;
        }
    }
    return 1;
}

