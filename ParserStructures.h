#ifndef _PARSERSTRUCTURESH_
#define _PARSERSTRUCTURESH_
#include "DorotiTypes.h"
#include "DorotiLexer.h"
typedef struct Doroti_Node Doroti_Node;
typedef enum {
    NodeType_,
    NodeType_Illegal,
    NodeType_VariableDecl,
    NodeType_FunctionDecl,
    NodeType_Return,
    NodeType_NumberLiteral,
    NodeType_FunctionCall
} Doroti_NodeType;

typedef struct {
    Doroti_TokenType Type;
    char* Name;
    Doroti_Node* DefaultValue;
    D_Bool HasDefaultValue;
} Doroti_FunctionParameter;

typedef struct Doroti_Node {
    Doroti_NodeType Type;
    D_Uint Line;
    D_Uint Column;
    union
    {
        // Function Declararion
        struct { 
            char* Name; 
            Doroti_FunctionParameter* Parameters;
            D_Uint ParameterCount;
            Doroti_TokenType ReturnType; 
            struct Doroti_Node* FunctionBody; 
        } NodeType_FunctionDecl;

        // Varaible Declaration
        struct { 
            char* Name; 
            Doroti_TokenType Mutability; 
            Doroti_TokenType Type; } NodeType_VariableDecl;

        struct { 
            long Value; } NodeType_NumberLiteral;

        struct { 
            struct Doroti_Node* Expression; } NodeType_Return;

        struct {
            char* Name;
            Doroti_Vector Arguments;
        } NodeType_FunctionCall;

    } Data;
} Doroti_Node;

#endif