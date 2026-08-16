#include "ExternalLibraries.h"
#include "StringUtility.h"
#include "DorotiLexer.h"
#include "DorotiParser.h"

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
    char* x = NULL;
    for (int i = 0; i < argc; i++) {
        if (fBool_IsSourceFile(argv[i])){
            x = fPChar_OpenFile(argv[i]);
        }
    }
    printf("\n");
    char y[100];
    Doroti_LexerState Lexer;
    Lexer.SourceCode = (x);
    Doroti_Vector* Tokens = fVecToken_DorotiLexer(&Lexer);
    Doroti_ParserState Parser;
    Parser.Tokens = Tokens;
    Parser.Size = Tokens -> Size;
    Parser.Source = (x);
    fVoid_DorotiParser(&Parser);

    fVoid_FreeVector(Tokens);
    free(Tokens);
    free(x);
}

