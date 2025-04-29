#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int *buffer;
    int allocated_size = 5;  // Виділяємо місце під 5 елементів

    // Виділення пам’яті під 5 цілих чисел
    buffer = (int *)malloc(allocated_size * sizeof(int));
    if (buffer == NULL) {
        printf("Помилка виділення пам’яті\n");
        return 1;
    }

    // Ініціалізація буфера
    for (i = 0; i < allocated_size; i++) {
        buffer[i] = i * 10;
    }

    printf("Читання %d елементів (в тому числі за межами буфера):\n", allocated_size + 3);
    
    // Читання поза межами виділеного масиву (buffer overflow при читанні)
    for (i = 0; i < allocated_size + 3; i++) {
        printf("buffer[%d] = %d\n", i, buffer[i]);
    }

    // Звільнення пам’яті
    free(buffer);
    return 0;
}
