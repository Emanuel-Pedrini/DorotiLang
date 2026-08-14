#include "StringUtility.h"
#include "DorotiLexer.h"
#include <stdio.h>

void DorotiLexer(Doroti_LexerState* DorotiState) {
    DorotiState -> Pointer = 0;
    while (1) {
        DorotiState -> ActualChar = DorotiState -> SourceCode[DorotiState -> Pointer];
        if (DorotiState -> ActualChar == '\0') {
            break;
        }
        printf("%c \n", DorotiState -> ActualChar);
        DorotiState -> Pointer++;
    }
}