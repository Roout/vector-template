#include "vector_template.h"

#include <stdio.h>

DEFINE_VECTOR(int_vector, int)
DEFINE_VECTOR_INTERFACE(int_vector, int)

int main() {
    struct int_vector *v = int_vector_create(10);
    for (size_t i = 0; i < 10; i++) {
        int_vector_push_back(v, 5);
    }
    printf("%d\n", int_vector_at(v, 0));
    
    int_vector_destroy(&v);
    return 0;
}