#include "ArrayUtilities.h"
#include "ExternalLibraries.h"
void fVoid_NewVector(Doroti_Vector* Vector, D_Uint ElementSize) {
    Vector -> Elements = NULL;
    Vector -> Capacity = 0;
    Vector -> Size = 0;
    Vector -> ElementSize = ElementSize;
}

void fVoid_Append(Doroti_Vector* Vector, const void* Element) {
    if (Vector -> Size > Vector -> Capacity) {
        
        D_Uint NewCapacity = Vector -> Capacity == 0 ? 8 : (Vector -> Capacity * 2);
        void* NewElements = realloc(Vector -> Elements, NewCapacity * Vector -> ElementSize);
        
        if (NewElements == NULL) {
            return;
        }
        Vector -> Elements = NewElements;
        Vector -> Capacity = NewCapacity;
    }
    char* Destination = (char*)Vector -> Elements + Vector -> Size * Vector -> ElementSize;
    memcpy(
        Destination,
        Element,
        Vector -> ElementSize
    );
    Vector -> Size++;
} 

void* fVoid_Get(Doroti_Vector* Vector, long int Index) {
    if (Index > Vector -> Size) {
        return NULL;
    }
    return (char*)Vector -> Elements + Index * Vector -> ElementSize;
}

void fVoid_FreeVector(Doroti_Vector* Vector) {
    free(Vector -> Elements);
    Vector -> Elements = NULL;
    Vector -> Capacity = 0;
    Vector -> Size = 0;
}