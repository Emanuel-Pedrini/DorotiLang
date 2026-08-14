#include "ExternalLibraries.h"
#include "StringUtility.h"
#include "DorotiLexer.h"

int fBool_IsSourceFile(const char* Path) {
    return (fBool_EndWith(Path, ".dt"));
}

/*
    Opens a file and read the content,
    A simple 4KB initial buffer that expands.
*/

char* fPChar_OpenFile(const char* Path) {
    int Capacity = 4096;
    int Size = 0;

    FILE* SourceCode = fopen(Path, "r");
    if (SourceCode == NULL) {
        return NULL;
    }

    char* DorotiTotalBuffer;

    DorotiTotalBuffer = (char*) malloc(Capacity * sizeof(char));
    if (DorotiTotalBuffer == NULL) {
        fclose(SourceCode);
        return NULL;
    }
    DorotiTotalBuffer[0] = '\0';
    char DorotiBuffer[2048];

    while (fgets(DorotiBuffer, sizeof(DorotiBuffer), SourceCode) != NULL) {
        int PretendedSize = strlen(DorotiBuffer);
        while (PretendedSize + Size >= Capacity) {
            Capacity = Capacity * 2;
            char *TemporaryBuffer = (char*) realloc(DorotiTotalBuffer, Capacity * sizeof(char));
            if (TemporaryBuffer == NULL) {
                free(DorotiTotalBuffer);
                fclose(SourceCode);
                return NULL;
            }
            DorotiTotalBuffer = TemporaryBuffer;
        }
        strcpy(&DorotiTotalBuffer[Size], DorotiBuffer);
        Size += strlen(DorotiBuffer);
    }
    fclose(SourceCode);
    return DorotiTotalBuffer;
}

int main(int argc, char* argv[]) {
    char* x;
    for (int i = 0; i < argc; i++) {
        if (fBool_IsSourceFile(argv[i])){
            x = fPChar_OpenFile(argv[i]);
        }
    }
    printf("\n");
    Doroti_LexerState D;
    D.SourceCode = (x);
    DorotiLexer(&D);
    free(x);
}

