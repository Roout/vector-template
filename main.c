#include "vector_template.h"

#include <stdio.h>

DEFINE_VECTOR(int_vector, int)
DEFINE_VECTOR_INTERFACE(int_vector, int)

int main() {
    struct int_vector v;
    if (!int_vector_init(&v, 10)) {
        printf("Failed to init vector: not enough memory\n");
        return 0;
    }
    for (size_t i = 0; i < 10; i++) {
        if (!int_vector_push_back(&v, 5)) {
            printf("Failed to push back to vector: not enough memory\n");
            break;
        }
    }
    printf("%d\n", *int_vector_at(&v, 0));
    
    int_vector_destroy(&v);
    return 0;
}