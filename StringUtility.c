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