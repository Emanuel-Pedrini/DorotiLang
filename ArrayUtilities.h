#ifndef _ARRAYUTILITIESH_
#define _ARRAYUTILITIESH_
#include "DorotiTypes.h"

typedef struct{
    void* Elements;
    D_Uint ElementSize;
    D_Uint Capacity;
    D_Uint Size;
} Doroti_Vector;

void fVoid_NewVector(Doroti_Vector* Vector, D_Uint ElementSize);
void fVoid_Append(Doroti_Vector* Vector, const void* Element);
void* fVoid_Get(Doroti_Vector* Vector, long int Index);
void fVoid_FreeVector(Doroti_Vector* Vector);

#endif