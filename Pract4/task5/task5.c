#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // для SIZE_MAX

int main() {
    // Спочатку виділимо невелику пам'ять
    void *ptr = malloc(10);
    if (ptr == NULL) {
        perror("malloc");
        return 1;
    }

    printf("Початковий вказівник: %p\n", ptr);

    // Намагатимемося перепризначити дуже велику пам'ять
    void *new_ptr = realloc(ptr, SIZE_MAX);

    if (new_ptr == NULL) {
        printf("realloc не зміг виділити пам'ять! ptr залишається валідним: %p\n", ptr);
        free(ptr);  // Треба вручну звільнити стару пам'ять
    } else {
        printf("realloc успішний, новий вказівник: %p\n", new_ptr);
        free(new_ptr);
    }

    return 0;
}
